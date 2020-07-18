
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "positionclass.h"
#include "timerclass.h"
#include "inputclass.h"
#include "soundclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"
#include "Materialclass.h"
#include "TextureManager.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, HINSTANCE);

	bool InitializeLights(HWND);
	bool InitializeMaterials(HWND);

	void Shutdown();
	bool Frame();
	

private:
	bool Render();
	bool HandleInput(float);
	

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass *m_Model, *m_Door, *m_Window, *m_Window1, *m_Speaker, *m_Floor, *m_Wall1, *m_Wall2, *m_Wall3, *m_Wall4, *m_Wall5, *m_Wall6, *m_Wall7, *m_Wall8, *m_Wall9, *m_Wall10, *m_Ceiling, *m_Sofa, *m_CeilingLight, *m_Sphere;
	LightShaderClass* m_LightShader;
	LightClass *m_Light, *lights;
	PositionClass* m_Position;
	SoundClass* m_Sound;
	TimerClass* m_Timer;
	InputClass* m_Input;	
	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;
	Materialclass *m_default;
	TextureManager* m_texture_light;
};

#endif