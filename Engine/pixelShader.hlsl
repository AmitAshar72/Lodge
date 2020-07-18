//////////////////////////////////////////////////////////////////////////////////
//// Filename: light.ps
//////////////////////////////////////////////////////////////////////////////////
//
//
///////////////
//// GLOBALS //
///////////////
//Texture2D shaderTexture;
//SamplerState SampleType;
//
//
//cbuffer LightBuffer
//{
//	float4 ambientLight;
//    float4 diffuseColor;
//    float3 lightDirection;
//	float padding;
//};
//
//
////////////////
//// TYPEDEFS //
////////////////
//struct PixelInputType
//{
//    float4 position : SV_POSITION;
//    float2 tex : TEXCOORD0;
//	float3 normal : NORMAL;
//};
//
//
//////////////////////////////////////////////////////////////////////////////////
//// Pixel Shader
//////////////////////////////////////////////////////////////////////////////////
//float4 LightPixelShader(PixelInputType input) : SV_TARGET
//{
//
//	float3 lightDir;
//	float lightIntensity;
//	float4 color;
//	float4 textureColor;
//
//
//	// Invert the light direction for calculations.
//	color = ambientLight;
//	lightDir = -lightDirection;
//	// Calculate the amount of light on this pixel.
//	textureColor = shaderTexture.Sample(SampleType, input.tex);
//    lightIntensity = saturate(dot(input.normal, lightDir));
//	if (lightIntensity > 0.0f)
//	{
//		color += (diffuseColor * lightIntensity);
//	}
//    // Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
//    color = color * textureColor;
//
//    return color;
//}


////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.ps
////////////////////////////////////////////////////////////////////////////////


/////////////
// DEFINES //
/////////////
#define NUM_LIGHTS 2

#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2


/////////////
// GLOBALS //
/////////////
SamplerState SampleType;
Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D emmisiveTexture : register(t2);

struct Light
{
	float4      Position;
	float4      Direction;
	float4      Color;
	float       SpotAngle;
	float       ConstantAttenuation;
	float       LinearAttenuation;
	float       QuadraticAttenuation;
	float		Range;
	bool        Enabled;
	int			Type;
	int         Padding;
};

struct Material
{
	float4   Emissive;
	float4   Ambient;
	float4   Diffuse;
	float4   Specular;
	float    SpecularPower;
	int      UseTexture;
	float2    Padding;
};

cbuffer LightColorBuffer
{
	Light Lights[NUM_LIGHTS];
	float4 CameraPosition;
	float4 GlobalAmbient;
	Material material;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 depthPosition : TEXCOORD1;
	float3 light_zero : TEXCOORD2;
	float3 worldPosition : TEXCOORD3;
	float3 viewDirection : TEXCOORD4;
};




/////////////////////////////////////////////////////////////////////////////////
// Light Functions
/////////////////////////////////////////////////////////////////////////////////

struct LightingResult
{
	float4 Diffuse;
	float4 Specular;
};

float4 DoSpecular(Light light, float3 viewDirection, float3 LightVector, float3 Normal, float specularPower)
{
	// Phong lighting.
	//float3 R = normalize(reflect(-LightVector, Normal));
	//float RdotV = max(0, dot(R, viewDirection));


	// Blinn-Phong lighting
	float3 H = normalize(LightVector + viewDirection);
	float NdotH = max(0, dot(Normal, H));

	return light.Color * pow(NdotH, specularPower);
}

float4 DoDiffuse(Light light, float3 LightVector, float3 Normal)
{
	/*float3 lightDir;
	float lightIntensity;
	float4 color;
	lightDir = -light.Direction;
	lightIntensity = saturate(dot(Normal, lightDir));
	color = (light.Color * lightIntensity);
	return color;*/
	float NdotL = saturate(max(0, dot(Normal, LightVector)));
	return light.Color * NdotL;
}

float DoAttenuation(Light light, float distance)
{

	return 1.0f / (light.ConstantAttenuation + light.LinearAttenuation * distance + light.QuadraticAttenuation * distance * distance);

}

float DoSpotCone(Light light, float3 LightVector)
{
	float minCos = cos(light.SpotAngle);
	float maxCos = (minCos + 1.0f) / 2.0f;
	float cosAngle = dot(light.Direction.xyz, -LightVector);
	return smoothstep(minCos, maxCos, cosAngle);
}


LightingResult DoSpotLight(Light light, float3 LightVector, float3 viewDirection, float3 bumpNormal, float SpecularPower, float distance)
{
	LightingResult result = { {0, 0, 0, 0}, {0, 0, 0, 0} };
	float attenuation, spotIntensity;
	attenuation = DoAttenuation(light, distance);
	spotIntensity = DoSpotCone(light, LightVector);
	result.Diffuse += DoDiffuse(light, LightVector, bumpNormal)*attenuation*spotIntensity;
	result.Specular += DoSpecular(light, viewDirection, LightVector, bumpNormal, SpecularPower)*attenuation;

	return result;
}

LightingResult DoDirectionalLight(Light light, float3 viewDirection, float3 bumpNormal, float SpecularPower)
{
	LightingResult result = { {0, 0, 0, 0}, {0, 0, 0, 0} };

	float3 L = -light.Direction.xyz;

	result.Diffuse = DoDiffuse(light, L, bumpNormal);
	result.Specular = DoSpecular(light, viewDirection, L, bumpNormal, SpecularPower);

	return result;
}

LightingResult DoPointLight(Light light, float3 LightVector, float3 viewDirection, float3 bumpNormal, float SpecularPower, float distance)
{
	LightingResult result = { {0, 0, 0, 0}, {0, 0, 0, 0} };
	float attenuation;
	attenuation = DoAttenuation(light, distance);
	result.Diffuse += DoDiffuse(light, LightVector, bumpNormal)*attenuation;
	result.Specular += DoSpecular(light, viewDirection, LightVector, bumpNormal, SpecularPower)*attenuation;

	return result;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 textureColor,emmisiveColor,totalColor;
	float3 temp = { 1.0f, 0.0f, 0.0f };
	float4 finalColor = { 1, 1, 1, 1 };
	float3 LightVector;
	float distance, attenuation, spotIntensity;
	float depthValue;
	float4 bumpMap;
	float3 bumpNormal;

	LightingResult totalresult = { { 0, 0, 0, 0 },{ 0, 0, 0, 0 } };

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = colorTexture.Sample(SampleType, input.tex);
	emmisiveColor = emmisiveTexture.Sample(SampleType, input.tex);
	// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
	depthValue = input.depthPosition.z / input.depthPosition.w;

	if (depthValue < 500.0f)
	{
		// Sample the pixel in the bump map.
		bumpMap = normalTexture.Sample(SampleType, input.tex);

		// Expand the range of the normal value from (0, +1) to (-1, +1).
		bumpMap = (bumpMap * 2.0f) - 1.0f;

		// Calculate the normal from the data in the bump map.
		bumpNormal = input.normal + bumpMap.x * input.tangent + bumpMap.y * input.binormal;

		// Normalize the resulting bump normal.
		bumpNormal = normalize(bumpNormal);
	}
	else
	{
		bumpNormal = input.normal;
	}


	[unroll]
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		if (Lights[i].Enabled)
		{

			LightVector = (input.light_zero + Lights[i].Position - input.worldPosition).xyz;
			distance = length(LightVector);
			LightVector = normalize(LightVector);

			if (distance < Lights[i].Range)
			{
				LightingResult temp_result = { {0, 0, 0, 0}, {0, 0, 0, 0} };
				switch (Lights[i].Type)
				{
				case DIRECTIONAL_LIGHT:
				{
					temp_result = DoDirectionalLight(Lights[i], input.viewDirection,  bumpNormal, material.SpecularPower);
				}
				break;
				case POINT_LIGHT:
				{
					temp_result = DoPointLight(Lights[i], LightVector, input.viewDirection, bumpNormal, material.SpecularPower,  distance);
				}
				break;
				case SPOT_LIGHT:
				{
					temp_result = DoSpotLight(Lights[i], LightVector, input.viewDirection, bumpNormal, material.SpecularPower, distance);
				}
				break;
				}
				totalresult.Diffuse += temp_result.Diffuse;
				totalresult.Specular += temp_result.Specular;

			}

		}
	}

	float4 ambient = GlobalAmbient * material.Ambient;

	totalresult.Diffuse = saturate(totalresult.Diffuse);
	totalresult.Specular = saturate(totalresult.Specular);

	finalColor = (ambient + totalresult.Diffuse + totalresult.Specular + material.Emissive)* textureColor + emmisiveColor;
	return finalColor;
}