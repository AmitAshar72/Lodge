
#include "lightclass.h"


LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::setAmbientLight(float red, float green, float blue, float alpha)
{
	m_ambientLight = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}

void LightClass::Initialize(D3DXVECTOR4 color, D3DXVECTOR3 position, D3DXVECTOR3 direction, float angle, float constantAttenuation,
	float linearAttenuation, float quadraticAttenuation, float range, int type)
{
	m_enabled = true;
	m_Color = color;
	m_position = position;
	m_spotAngle = angle;
	m_constantAttenuation = constantAttenuation;
	m_linearAttenuation = linearAttenuation;
	m_quadraticAttenuation = quadraticAttenuation;
	m_range = range;
	D3DXVECTOR3 LightDirection = direction;
	D3DXVec3Normalize(&LightDirection, &LightDirection);
	m_direction = LightDirection;
	m_type = type;
}


D3DXVECTOR4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


D3DXVECTOR4 LightClass::getAmbientLight()
{
	return m_ambientLight;
}

D3DXVECTOR4 LightClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 LightClass::GetDirection()
{
	return m_direction;
}