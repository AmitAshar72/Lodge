#include "Materialclass.h"



Materialclass::Materialclass()
{
}


Materialclass::Materialclass(const Materialclass& other)
{
}

Materialclass::~Materialclass()
{
}

void Materialclass::Initialize(D3DXVECTOR4 _emissive, D3DXVECTOR4 _ambient, D3DXVECTOR4 _diffuse, D3DXVECTOR4 _Specular, float _specularPower, int _flag)
{
	Emissive = _emissive;
	Ambient= _ambient;
	Diffuse= _diffuse;
	Specular= _Specular;
	SpecularPower= _specularPower;
	Flag= _flag;

}
