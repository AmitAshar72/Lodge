
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_
#include <d3dx10math.h>
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void setAmbientLight(float, float, float, float);
	void SetDirection(float, float, float);

	void Initialize(D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR3, float, float, float, float, float, int);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 getAmbientLight();
	D3DXVECTOR4 GetPosition();	
	float m_spotAngle, m_constantAttenuation, m_linearAttenuation, m_quadraticAttenuation, m_range;
	bool m_enabled;
	int m_type;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_Color;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_ambientLight;

private:
	
};

#endif