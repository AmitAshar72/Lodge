
#ifndef _LIGHTSHADERCLASS_H_
#define _LIGHTSHADERCLASS_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include "lightclass.h"
#include "Materialclass.h"
using namespace std;
class LightShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct Light
	{
		Light()
			: Position(0.0f, 0.0f, 0.0f, 1.0f)
			, Direction(0.0f, 0.0f, 1.0f, 0.0f)
			, Color(1.0f, 1.0f, 1.0f, 1.0f)
			, SpotAngle(1.57079632679f)
			, ConstantAttenuation(1.0f)
			, LinearAttenuation(0.0f)
			, QuadraticAttenuation(0.0f)
			, Range(0.0f)
			, Enabled(0)
			, Type(0)
		{}
		D3DXVECTOR4    Position;
		D3DXVECTOR4    Direction;
		D3DXVECTOR4    Color;
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
		Material()
			: Emissive(0.0f, 0.0f, 0.0f, 1.0f)
			, Ambient(0.1f, 0.1f, 0.1f, 1.0f)
			, Diffuse(1.0f, 1.0f, 1.0f, 1.0f)
			, Specular(1.0f, 1.0f, 1.0f, 1.0f)
			, SpecularPower(128.0f)
			, UseTexture(false)
		{}
		D3DXVECTOR4   Emissive;
		D3DXVECTOR4   Ambient;
		D3DXVECTOR4   Diffuse;
		D3DXVECTOR4   Specular;
		float               SpecularPower;
		int                 UseTexture;
		float                 Padding[2];
	};

	struct LightBufferType
	{
		Light Light[2];
		D3DXVECTOR4 CameraPosition;
		D3DXVECTOR4 GlobalAmbient;
		Material Material;
	};

	struct CameraBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};


public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	//bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX , D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, float deltavalue, ID3D11ShaderResourceView*);

	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, LightClass*, D3DXVECTOR3, D3DXVECTOR4, Materialclass*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	//bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, float deltavalue, ID3D11ShaderResourceView*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, LightClass*, D3DXVECTOR3, D3DXVECTOR4, Materialclass*, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*);

	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightBuffer;
	ID3D11ShaderResourceView*  texture;
};

#endif