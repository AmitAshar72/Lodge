//////////////////////////////////////////////////////////////////////////////////
//// Filename: light.vs
//////////////////////////////////////////////////////////////////////////////////
//
//
///////////////
//// GLOBALS //
///////////////
//cbuffer MatrixBuffer
//{
//	matrix worldMatrix;
//	matrix viewMatrix;
//	matrix projectionMatrix;
//};
//
//cbuffer VariableBuffer
//{
//    float delta;
//	float3 padding;
//};
//
////////////////
//// TYPEDEFS //
////////////////
//struct VertexInputType
//{
//    float4 position : POSITION;
//    float2 tex : TEXCOORD0;
//	float3 normal : NORMAL;
//};
//
//struct PixelInputType
//{
//    float4 position : SV_POSITION;
//    float2 tex : TEXCOORD0;
//	float3 normal : NORMAL;
//};
//
//
//////////////////////////////////////////////////////////////////////////////////
//// Vertex Shader
//////////////////////////////////////////////////////////////////////////////////
//PixelInputType LightVertexShader(VertexInputType input)
//{
//    PixelInputType output;
//    
//
//	// Change the position vector to be 4 units for proper matrix calculations.
//    input.position.w = 1.0f;
//
//	// Calculate the position of the vertex against the world, view, and projection matrices.
//    output.position = mul(input.position, worldMatrix);
//    output.position = mul(output.position, viewMatrix);
//    output.position = mul(output.position, projectionMatrix);
//    
//	// Store the texture coordinates for the pixel shader.
//	output.tex = input.tex;
//    
//	// Calculate the normal vector against the world matrix only.
//    output.normal = mul(input.normal, (float3x3)worldMatrix);
//	
//    // Normalize the normal vector.
//    output.normal = normalize(output.normal);
//
//    return output;
//}

////////////////////////////////////////////////////////////////////////////////
// Filename: terrain.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float4 depthPosition : TEXCOORD1;
	float3 light_zero : TEXCOORD2;
	float4 worldPosition : TEXCOORD3;
	float3 viewDirection : TEXCOORD4;
};

cbuffer CameraBuffer
{
	float3 cameraPosition;
	float padding;
};



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType LightVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;

	float3 position_zero = { 0.0f,0.0f,0.0f };
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the position value in a second input value for depth value calculations.
	output.depthPosition = output.position;

	// Calculate the normal vector against the world matrix only and then normalize the final value.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	// Calculate the tangent vector against the world matrix only and then normalize the final value.
	output.tangent = mul(input.tangent, (float3x3)worldMatrix);
	output.tangent = normalize(output.tangent);

	// Calculate the binormal vector against the world matrix only and then normalize the final value.
	output.binormal = mul(input.binormal, (float3x3)worldMatrix);
	output.binormal = normalize(output.binormal);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(input.position, worldMatrix);
	output.worldPosition.xyz = worldPosition;
	output.worldPosition.w = 1.0f;

	output.light_zero = position_zero - worldPosition.xyz;

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection = normalize(output.viewDirection);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	return output;
}