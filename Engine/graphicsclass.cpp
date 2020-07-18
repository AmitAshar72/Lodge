
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Sound = 0;
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Floor = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Position = 0;
	m_Timer = 0;
	m_Wall1 = 0;
	m_Wall2 = 0;
	m_Wall3 = 0;
	m_Wall4 = 0;
	m_Wall5 = 0;
	m_Wall6 = 0;
	m_Wall7 = 0;
	m_Wall8 = 0;
	m_Wall9 = 0;
	m_Wall10 = 0;
	m_Ceiling = 0;
	m_Input = 0;
	m_Door = 0;
	m_Window = 0;
	m_Window1 = 0;
	m_Speaker = 0;
	m_SkyDome = 0;
	m_SkyDomeShader = 0;
	m_default = 0;
	m_texture_light = 0;
	m_Sofa = 0;
	m_CeilingLight = 0;
	m_Sphere = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, HINSTANCE hinstance)
{
	bool result;
	D3DXVECTOR3 camPos;
	camPos.x = 0.0f;
	camPos.y = 4.0f;
	camPos.z = -10.0f;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(camPos.x, camPos.y, camPos.z);
	
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/table.txt", L"../Engine/data/tableTex.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// Create the light object.
	m_Sphere = new ModelClass;
	if (!m_Sphere)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Sphere->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/lightTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the ceiling light object.
	m_CeilingLight = new ModelClass;
	if (!m_CeilingLight)
	{
		return false;
	}

	// Initialize the model object.
	result = m_CeilingLight->Initialize(m_D3D->GetDevice(), "../Engine/data/light.txt", L"../Engine/data/emissTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// Create the sofa object.
	m_Sofa = new ModelClass;
	if (!m_Sofa)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Sofa->Initialize(m_D3D->GetDevice(), "../Engine/data/sofa.txt", L"../Engine/data/sofaBlack.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the speaker object.
	m_Speaker = new ModelClass;
	if (!m_Speaker)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Speaker->Initialize(m_D3D->GetDevice(), "../Engine/data/speaker.txt", L"../Engine/data/modelTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the door object.
	m_Door = new ModelClass;
	if (!m_Door)
	{
		return false;
	}

	// Initialize the door object.
	result = m_Door->Initialize(m_D3D->GetDevice(), "../Engine/data/door.txt", L"../Engine/data/modelTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the window object.
	m_Window = new ModelClass;
	if (!m_Window)
	{
		return false;
	}

	// Initialize the window object.
	result = m_Window->Initialize(m_D3D->GetDevice(), "../Engine/data/window.txt", L"../Engine/data/modelTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the window1 object.
	m_Window1 = new ModelClass;
	if (!m_Window1)
	{
		return false;
	}

	// Initialize the window object.
	result = m_Window1->Initialize(m_D3D->GetDevice(), "../Engine/data/window.txt", L"../Engine/data/modelTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the floor object.
	m_Floor = new ModelClass;
	if (!m_Floor)
	{
		return false;
	}

	// Initialize the floor object.
	result = m_Floor->Initialize(m_D3D->GetDevice(), "../Engine/data/model.txt", L"../Engine/data/floorTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall1 object.
	m_Wall1 = new ModelClass;
	if (!m_Wall1)
	{
		return false;
	}
	result = m_Wall1->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the wall2 object.
	m_Wall2 = new ModelClass;
	if (!m_Wall2)
	{
		return false;
	}
	result = m_Wall2->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the wall3 object.
	m_Wall3 = new ModelClass;
	if (!m_Wall3)
	{
		return false;
	}
	result = m_Wall3->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Create the wall4 object.
	m_Wall4 = new ModelClass;
	if (!m_Wall4)
	{
		return false;
	}
	result = m_Wall4->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall5 object.
	m_Wall5 = new ModelClass;
	if (!m_Wall5)
	{
		return false;
	}
	result = m_Wall5->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// Create the wall6 object.
	m_Wall6 = new ModelClass;
	if (!m_Wall6)
	{
		return false;
	}
	result = m_Wall6->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall7 object.
	m_Wall7 = new ModelClass;
	if (!m_Wall7)
	{
		return false;
	}
	result = m_Wall7->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall8 object.
	m_Wall8 = new ModelClass;
	if (!m_Wall8)
	{
		return false;
	}
	result = m_Wall8->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall9 object.
	m_Wall9 = new ModelClass;
	if (!m_Wall9)
	{
		return false;
	}
	result = m_Wall9->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the wall10 object.
	m_Wall10 = new ModelClass;
	if (!m_Wall10)
	{
		return false;
	}
	result = m_Wall10->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/wallTex.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the ceiling object.
	m_Ceiling = new ModelClass;
	if (!m_Ceiling)
	{
		return false;
	}
	result = m_Ceiling->Initialize(m_D3D->GetDevice(), "../Engine/data/plane.txt", L"../Engine/data/offWhite.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	// Initialize the sound object.
	result = m_Sound->Initialize(hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}


	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(camPos.x, camPos.y, camPos.z);


	m_texture_light = new TextureManager;
	if (!m_texture_light)
	{
		return false;
	}

	m_texture_light->Initialize(3);

	result = m_texture_light->LoadTexture(m_D3D->GetDevice(), L"../Engine/data/tableTex.dds", L"../Engine/data/Snow_normal.dds", L"../Engine/data/emissTex.dds", 0);
	if (!result)
	{
		return false;
	}

	result = m_texture_light->LoadTexture(m_D3D->GetDevice(), L"../Engine/data/floorWood.dds", L"../Engine/data/floorWoodNormal.dds", L"../Engine/data/emissTex.dds", 1);
	if (!result)
	{
		return false;
	}

	result = m_texture_light->LoadTexture(m_D3D->GetDevice(), L"../Engine/data/sofaBlack.dds", L"../Engine/data/sofaBlackNormal.dds", L"../Engine/data/emissTex.dds", 2);
	if (!result)
	{
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the points light objects.
	if (!InitializeMaterials(hwnd))
	{
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}
	
	// Initialize the light object.
	m_Light->setAmbientLight(0.45f, 0.45f, 0.45f, 1.0f);
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.01f, 0.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.0f);

	// Initialize the points light objects.
	if (!InitializeLights(hwnd))
	{
		return false;
	}


	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeLights(HWND)
{
	D3DXVECTOR4 color;
	D3DXVECTOR3 direction, position_1, position_2;
	float angle, constantAttenuation, linearAttenuation, quadraticAttenuation, range;
	int type;

	bool result;	

	lights = new LightClass[2];
	if (!lights)
	{
		return false;
	}


	// Defintion of the light attributes
	color = D3DXVECTOR4(3.0f, 3.0f, 3.0f, 10.0f);
	
	angle = D3DXToRadian(60.0f);
	constantAttenuation = 1.0f;
	linearAttenuation = 0.1f;
	quadraticAttenuation = 0.001f;
	range = 45.0f;
	type = 2;
	//position_1 = D3DXVECTOR3(-10.0f, 15.0f, 20.0f);
	position_1 = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	//position_2 = D3DXVECTOR3(10.0f, 15.0f, 2.0f);
	direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	lights[0].Initialize(color, position_1, direction, angle, constantAttenuation, linearAttenuation, quadraticAttenuation, range, type);

	

	lights[1].Initialize(color, position_2, direction, angle, constantAttenuation, linearAttenuation, quadraticAttenuation, range, type);

	return true;

}

bool GraphicsClass::InitializeMaterials(HWND)
{
	D3DXVECTOR4 Ambient, Diffuse, Specular, Emissive;
	float SpecularPower;
	int flag;

	m_default = new Materialclass;
	if (!m_default)
	{
		return false;
	}

	Emissive = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	Ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	Diffuse = D3DXVECTOR4(1.0f, 0.829f, 0.829f, 1.0f);
	Specular = D3DXVECTOR4(0.296648f, 0.296648f, 0.296648f, 1.0f);
	//Specular = D3DXVECTOR4(0.5f,0.5f,0.5f, 1.0f);
	SpecularPower = 45.0f;
	flag = 1;
	m_default->Initialize(Emissive, Ambient, Diffuse, Specular, SpecularPower, flag);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_default)
	{
		delete m_default;
		m_default = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_texture_light)
	{
		delete m_texture_light;
		m_texture_light = 0;
	}



	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the graphics object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// Release the ceiling oject.
	if (m_Ceiling)
	{
		m_Ceiling->Shutdown();
		delete m_Ceiling;
		m_Ceiling = 0;
	}
	// Release the wall10 oject.
	if (m_Wall10)
	{
		m_Wall10->Shutdown();
		delete m_Wall10;
		m_Wall10 = 0;
	}

	// Release the wall9 oject.
	if (m_Wall9)
	{
		m_Wall9->Shutdown();
		delete m_Wall9;
		m_Wall9 = 0;
	}

	// Release the wall8 oject.
	if (m_Wall8)
	{
		m_Wall8->Shutdown();
		delete m_Wall8;
		m_Wall8 = 0;
	}

	// Release the wall7 oject.
	if (m_Wall7)
	{
		m_Wall7->Shutdown();
		delete m_Wall7;
		m_Wall7 = 0;
	}

	// Release the wall6 oject.
	if (m_Wall6)
	{
		m_Wall6->Shutdown();
		delete m_Wall6;
		m_Wall6 = 0;
	}

	// Release the wall5 oject.
	if (m_Wall5)
	{
		m_Wall5->Shutdown();
		delete m_Wall5;
		m_Wall5 = 0;
	}

	// Release the wall4 oject.
	if (m_Wall4)
	{
		m_Wall4->Shutdown();
		delete m_Wall4;
		m_Wall4 = 0;
	}

	// Release the wall3 object.
	if (m_Wall3)
	{
		m_Wall3->Shutdown();
		delete m_Wall3;
		m_Wall3 = 0;
	}

	// Release the wall2 object.
	if (m_Wall2)
	{
		m_Wall2->Shutdown();
		delete m_Wall2;
		m_Wall2 = 0;
	}

	// Release the wall1 object.
	if (m_Wall1)
	{
		m_Wall1->Shutdown();
		delete m_Wall1;
		m_Wall1 = 0;
	}

	// Release the floor object.
	if (m_Floor)
	{
		m_Floor->Shutdown();
		delete m_Floor;
		m_Floor = 0;
	}

	// Release the window object.
	if (m_Window1)
	{
		m_Window1->Shutdown();
		delete m_Window1;
		m_Window1 = 0;
	}

	// Release the window object.
	if (m_Window)
	{
		m_Window->Shutdown();
		delete m_Window;
		m_Window = 0;
	}

	// Release the door object.
	if (m_Door)
	{
		m_Door->Shutdown();
		delete m_Door;
		m_Door = 0;
	}

	// Release the speaker object.
	if (m_Speaker)
	{
		m_Speaker->Shutdown();
		delete m_Speaker;
		m_Speaker = 0;
	}

	// Release the model object.
	if (m_Sofa)
	{
		m_Sofa->Shutdown();
		delete m_Sofa;
		m_Sofa = 0;
	}

	// Release the model object.
	if (m_CeilingLight)
	{
		m_CeilingLight->Shutdown();
		delete m_CeilingLight;
		m_CeilingLight = 0;
	}

	// Release the model object.
	if (m_Sphere)
	{
		m_Sphere->Shutdown();
		delete m_Sphere;
		m_Sphere = 0;
	}
	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	//static float rotation = (float)D3DX_PI / 2.0f;
	//static float delta = 0.0f;
	//// Update the delta variable each frame. (keep this between 0 and 1)
	//delta += 0.001;
	//if (delta > 1.0f)
	//{
	//	delta -= 1.0f;
	//}

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	m_Timer->Frame();
	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}
		
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}
	
	return result;

}

bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, scalingMatrix, orthoMatrix, translationMatrix;
	D3DXVECTOR3 cameraPosition;
	bool result;
	float posX, posY, posZ;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);	
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixScaling(&scalingMatrix, 50.0f, 50.0f, 50.0f);
	D3DXMatrixTranslation(&translationMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	D3DXMatrixMultiply(&worldMatrix, &scalingMatrix, &translationMatrix);
	// Turn off back face culling.
	m_D3D->TurnOffCulling();
	// Turn off the Z buffer.
	m_D3D->TurnZBufferOff();
	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	// Turn back face culling back on.
	m_D3D->TurnOnCulling();
	// Turn the Z buffer back on.
	m_D3D->TurnZBufferOn();

	

	//TABLE	
	D3DXMatrixRotationY(&worldMatrix, ((float)D3DX_PI / 2.0f));
	D3DXMatrixScaling(&scalingMatrix, 0.05f,0.05f,0.05f);	
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -10.0f, -0.85f, 2.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lights, m_Camera->GetPosition(),  m_Light->getAmbientLight(), 
		m_default, m_texture_light->GetColorTexture(0), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0) );
	if(!result)
	{
		return false;
	}

	//Light
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.55f, 0.25f, 0.55f);
	//D3DXMatrixRotationX(&worldMatrix, ((float)D3DX_PI / 2.0f));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 8.75f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);

	m_Sphere->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Sphere->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(),
		m_default, m_Sphere->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//CEILING LIGHT
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.05f, 0.05f, 0.05f);
	D3DXMatrixRotationX(&worldMatrix, ((float)D3DX_PI / 2.0f));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 14.0f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);

	m_CeilingLight->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_CeilingLight->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(),
		m_default, m_CeilingLight->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//SOFA
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.005f, 0.005f, 0.005f);
	D3DXMatrixRotationY(&worldMatrix, ((float)D3DX_PI / 2.0f));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 10.0f, -0.9f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);

	m_Sofa->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Sofa->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lights, m_Camera->GetPosition(), m_Light->getAmbientLight(),
		m_default, m_Sofa->GetTexture(), m_texture_light->GetNormalMapTexture(2), m_texture_light->GetEmmisiveTexture(2));
	if (!result)
	{
		return false;
	}


	//SPEAKER
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&worldMatrix, ((float)D3DX_PI));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -10.0f, 2.83f, 2.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	
	m_Speaker->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Speaker->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lights, m_Camera->GetPosition(), m_Light->getAmbientLight(),
		m_default, m_Speaker->GetTexture(),m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//DOOR
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, 0.0f, 3.1f, -14.85f);
	m_Door->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Door->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lights, m_Camera->GetPosition(), m_Light->getAmbientLight(),
		m_default, m_Door->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WINDOW 1
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, D3DXToRadian(90.0f));
	D3DXMatrixScaling(&scalingMatrix, 0.08f, 0.08f, 0.08f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -5.0f, 4.85f, 15.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Window->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Window->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Window->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WINDOW 2
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, D3DXToRadian(90.0f));
	D3DXMatrixScaling(&scalingMatrix, 0.08f, 0.08f, 0.08f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 5.0f, 4.85f, 15.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Window1->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Window1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default,
		m_Window1->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//FLOOR
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 30.0f, 0.01f, 30.0f);
	//D3DXMatrixRotationZ(&worldMatrix, D3DXToRadian(180.0f));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f,-0.9f , 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Floor->Render(m_D3D->GetDeviceContext());	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Floor->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lights, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_texture_light->GetColorTexture(1), m_texture_light->GetNormalMapTexture(1), m_texture_light->GetEmmisiveTexture(1));
	if (!result)
	{
		return false;
	}
	
	//WALL 1 right wall
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.1f, 7.5f, 14.85f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 14.85f, 6.6f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall1->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall1->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 2 left wall
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 0.1f, 7.5f, 14.85f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -14.85f, 6.6f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall2->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall2->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 3 door wall 1
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 15.0f, 3.81f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 10.27f, -14.85f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall3->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall3->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 4 door wall 2
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 6.5f, 3.68f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 8.5f, 2.78f, -14.85f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall4->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall4->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 5 door wall 3
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 6.5f, 3.68f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -8.5f, 2.78f, -14.85f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall5->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall5->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall5->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 6 window wall 1
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 14.9f, 3.1f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 10.9f, 14.9f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall6->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall6->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall6->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 7 window wall 2
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 4.1f, 4.37f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 10.8f, 3.47f, 14.9f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall7->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall7->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall7->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 8 window wall 3
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 4.1f, 4.37f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, -10.8f, 3.47f, 14.9f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall8->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall8->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall8->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 9 window wall 4
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 3.25f, 3.1f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 4.85f, 14.9f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall9->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall9->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall9->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//WALL 10 window wall 5
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixScaling(&scalingMatrix, 6.7f, 1.4f, 0.1f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 0.5f, 14.9f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Wall10->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Wall10->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Wall10->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}

	//Ceiling
	//reset worldmatrix
	m_D3D->GetWorldMatrix(worldMatrix);	
	D3DXMatrixScaling(&scalingMatrix, 15.0f, 0.1f, 15.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scalingMatrix);
	D3DXMatrixTranslation(&translationMatrix, 0.0f, 14.1f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translationMatrix);
	m_Ceiling->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ceiling->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Light, m_Camera->GetPosition(), m_Light->getAmbientLight(), m_default, m_Ceiling->GetTexture(), m_texture_light->GetNormalMapTexture(0), m_texture_light->GetEmmisiveTexture(0));
	if (!result)
	{
		return false;
	}
	
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsAPressed();
	m_Position->TurnLeft(keyDown);
	
	keyDown = m_Input->IsDPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	m_Sound->setListenerPosition(posX, posY, posZ);
	
	return true;
}



