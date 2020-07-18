////////////////////////////////////////////////////////////////////////////////
// Filename: TextureManager.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_


//////////////
// INCLUDES //
//////////////

#include "textureclass.h"


class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();
	TextureManager(const TextureManager&);
	void ReleaseTexture();
	bool Initialize(int);
	bool LoadTexture(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*,int);
	ID3D11ShaderResourceView* GetColorTexture(int);
	ID3D11ShaderResourceView* GetNormalMapTexture(int);
	ID3D11ShaderResourceView* GetEmmisiveTexture(int);
private:
	TextureClass* m_Texture, *m_NormalMapTexture, *m_emmisiveTexture;
	int m_textures;
	
};

#endif