
////////////////////////////////////////////////////////////////////////////////
// Filename: TextureManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "TextureManager.h"

TextureManager::TextureManager()
{
	m_Texture = 0;
	m_NormalMapTexture = 0;
	m_emmisiveTexture = 0;
}


TextureManager::~TextureManager()
{
}

TextureManager::TextureManager(const TextureManager &)
{
}

ID3D11ShaderResourceView* TextureManager::GetColorTexture(int index)
{
	return m_Texture[index].GetTexture();
}

ID3D11ShaderResourceView* TextureManager::GetNormalMapTexture(int index)
{
	return m_NormalMapTexture[index].GetTexture();
}

ID3D11ShaderResourceView * TextureManager::GetEmmisiveTexture(int index)
{
	return m_emmisiveTexture[index].GetTexture();
}

void TextureManager::ReleaseTexture()
{
	for (int i =0; i< m_textures;i++)
	{
		m_Texture[i].Shutdown();
		m_NormalMapTexture[i].Shutdown();
		m_emmisiveTexture[i].Shutdown();
	}

	// Release the texture object.
	if (m_Texture)
	{
		delete[] m_Texture;
		m_Texture = 0;
	}

	// Release the normal map texture object.
	if (m_NormalMapTexture)
	{
		delete[] m_NormalMapTexture;
		m_NormalMapTexture = 0;
	}

	// Release the normal map texture object.
	if (m_emmisiveTexture)
	{
		delete[] m_emmisiveTexture;
		m_emmisiveTexture = 0;
	}

	return;
}

bool TextureManager::Initialize(int index)
{
	m_textures = index;

	// Create the color texture object.
	m_Texture = new TextureClass[m_textures];
	if (!m_Texture)
	{
		return false;
	}

	// Create the normal map texture object.
	m_NormalMapTexture = new TextureClass[m_textures];
	if (!m_NormalMapTexture)
	{
		return false;
	}

	// Create the normal map texture object.
	m_emmisiveTexture = new TextureClass[m_textures];
	if (!m_emmisiveTexture)
	{
		return false;
	}

	return true;

}

bool TextureManager::LoadTexture(ID3D11Device* device, WCHAR* colorTexturefilename, WCHAR* normalMapFilename, WCHAR* emmisiveFilename, int index)
{
	bool result;


	

	// Initialize the color texture object.
	result = m_Texture[index].Initialize(device, colorTexturefilename);
	if (!result)
	{
		return false;
	}

	

	// Initialize the normal map texture object.
	result = m_NormalMapTexture[index].Initialize(device, normalMapFilename);
	if (!result)
	{
		return false;
	}

	

	// Initialize the normal map texture object.
	result = m_emmisiveTexture[index].Initialize(device, emmisiveFilename);
	if (!result)
	{
		return false;
	}


	return true;
}