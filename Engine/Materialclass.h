#pragma once
///////////////////////////////////////////////////////////////////////////////
// Filename: Materialclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MATERIALCLASS_H_
#define _MATERIALCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include <DirectXMath.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: Materialclass
////////////////////////////////////////////////////////////////////////////////

class Materialclass
{
public:
	Materialclass();
	Materialclass(const Materialclass&);
	virtual ~Materialclass();
	

	void Initialize(D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR4, float, int);

	D3DXVECTOR4   Emissive;
	D3DXVECTOR4   Ambient;
	D3DXVECTOR4   Diffuse;
	D3DXVECTOR4   Specular;
	float         SpecularPower;
	int           Flag;
};

#endif