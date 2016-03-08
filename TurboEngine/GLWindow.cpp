#include "GLWindow.h"
#include "glew.h"
#include "wglew.h"
#include "Vertex.h"
#include "ShaderUtility.h"
#include "ModelLoader.h"
#include <vector>
#include "Mesh.h"
#include <time.h>
#include "BezierPositionAnimation.h"
#include "CurveAnimation.h"

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

glm::vec3 colors[3];
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	colors[0] = glm::vec3(0.7f, 0.7f, 0.7f);
	colors[1] = glm::vec3(0.2f, 0.8f, 0.7f);
	colors[2] = glm::vec3(0.3f, 0.3f, 0.8f);
	POINT windowPos = { 100, 100 };
	POINT windowSize = { 800,600 };
	if (!okno.Initialize(hInstance, windowPos, windowSize))
	{
		MessageBox(nullptr, "Initialization failed", "Turbo Engine", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
	return okno.Run();
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return okno.WndProc(hWnd, message, wParam, lParam);
}
void TrackMouse(HWND hwnd)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE; //Type of events to track & trigger.
	tme.dwHoverTime = 1; //How long the mouse has to be in the window to trigger a hover event.
	tme.hwndTrack = hwnd;
	TrackMouseEvent(&tme);
}
bool Window::Initialize(HINSTANCE applicationHandle, POINT windowPosition, POINT windowSize, bool fullScreen, bool resolutionChange)
{
	char windowName[] = "Turbo Engine";
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = applicationHandle;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = windowName;

	if (RegisterClassEx(&wc) == 0)
		return false;
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	if (fullScreen)
	{
		windowStyle = WS_POPUP;
		windowPosition.x = windowPosition.y = 0;
		if (resolutionChange)
		{
			windowSize.x = 1024;
			windowSize.y = 768;
			if (!ChangeResolution(windowSize.x, windowSize.y))
				return false;
		}
		else
		{
			RECT screenSize;
			GetWindowRect(GetDesktopWindow(), &screenSize);
			windowSize.x = screenSize.right - screenSize.left;
			windowSize.y = screenSize.bottom - screenSize.top;
		}
	}

	windowHandle = CreateWindow(
		windowName, windowName, windowStyle, windowPosition.x, windowPosition.y,
		windowSize.x, windowSize.y, nullptr, nullptr, applicationHandle, nullptr);
	if (windowHandle == nullptr)
		return false;
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
	//TrackMouse(windowHandle);
	return true;
}


bool Window::ChangeResolution(long width, long height, long colorDepth) const
{
	DEVMODE dSS;
	memset(&dSS, 0, sizeof(dSS));
	dSS.dmSize = sizeof(dSS);
	dSS.dmPelsWidth = width;
	dSS.dmPelsHeight = height;
	dSS.dmBitsPerPel = colorDepth;
	dSS.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	return ChangeDisplaySettings(&dSS, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
}

void GlWindow::UpdateObjects(float deltaTime)
{

}

void GlWindow::KeyDown(WPARAM wParam)
{
	keyPressed[wParam] = true;
	if (wParam == VK_F1 && actualLightning)
		actualLightning->NextType();
	if (wParam == VK_F3)
		NextCamera();
	if (wParam == VK_F4)
		actualCamera->fov += 1;
	if (wParam == VK_F5)
		actualCamera->fov -= 1;
	if (wParam == VK_F2)
	{

		if (!raceStarted)
			StartRace();
		else
			StopRace();
	}
}

void GlWindow::KeyUp(WPARAM wParam)
{
	keyPressed[wParam] = false;
}

//Main Loop
WPARAM GlWindow::Run()
{
	MSG msg;
	long time = GetTickCount();
	long elapsed = 0;
	while (shouldRun)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} //system messages handling
		KeyControl(elapsed / 1000.0f);
		UpdateObjects(elapsed);

		Animate(elapsed);
		DrawScene();
		// robienie rzeczy.

		long actualTime = GetTickCount();
		elapsed = actualTime - time;
		time = actualTime;
		if (elapsed < 30.0L)
			Sleep(30.0L - elapsed);

	}
	return msg.wParam;
}
float carSpeed = 3.0f;
void GlWindow::KeyControl(float time)
{
	if (cameraIndex == 0)
	{
		if (keyPressed['A'])//A
		{
			actualCamera->MoveByLocalVector(glm::vec3(10, 0, 0)*time);
		}
		if (keyPressed['S'])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 0, -10)*time);
		}
		if (keyPressed['D'])//D
		{
			actualCamera->MoveByLocalVector(glm::vec3(-10, 0, 0)*time);
		}
		if (keyPressed['W'])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 0, 10)*time);
		}
		if (keyPressed[VK_SHIFT])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, -10, 0)*time);
		}
		if (keyPressed[VK_SPACE])
		{
			actualCamera->MoveByLocalVector(glm::vec3(0, 10, 0)*time);
		}
	}
	else
	{
		if (keyPressed['A'])//A
		{
			userCar->Rotate(90.0f * time, 0, 0);
		}
		if (keyPressed['S'])
		{
			userCar->MoveByLocalVector(glm::vec3(0, 0, -10)*carSpeed*time);
		}
		if (keyPressed['D'])//D
		{
			userCar->Rotate(-90.0f * time, 0,0);
		}
		if (keyPressed['W'])
		{
			userCar->MoveByLocalVector(glm::vec3(0, 0, 10)*carSpeed*time);
		}
	}
	temp = NULL;
}

void GlWindow::MouseMoved(LPARAM lParam, WPARAM wParam)
{
	POINT mousePos{ LOWORD(lParam),HIWORD(lParam) };
	if (prevMousePos.x == -1)
		prevMousePos = mousePos;
	POINT move;
	move.x = mousePos.x - prevMousePos.x;
	move.y = mousePos.y - prevMousePos.y;
	float movement = (float)sqrt(move.x*move.x + move.y*move.y);
	if (movement > 3.0f)
	{
		if (cameraIndex != 1)
		{
			float wsp = 0.1f;
			float dx = move.x*wsp;
			float dy = move.y*wsp*2.0f;
			if (wParam & MK_LBUTTON)
			{
				actualCamera->Rotate(dx, dy,0);
			}
		}
		prevMousePos = mousePos;
	}
}

void GlWindow::StartRace()
{
	if (raceStarted)
		return;
	for (auto car : cars)
	{
		car->SetAnimationStart(true);
	}
	raceStarted = true;
}

void GlWindow::StopRace()
{
	if (!raceStarted)
		return;
	for (auto car : cars)
	{
		car->SetAnimationStart(false);
	}
	raceStarted = false;
}

void GlWindow::NextCamera()
{
	cameraIndex = (cameraIndex + 1) % cameras.size();
	actualCamera = cameras[cameraIndex];
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		shouldRun = false;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		RECT rect;
		GetClientRect(hWnd, &rect);
		windowHeight = rect.bottom - rect.top;
		windowWidth = rect.right - rect.left;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0L;
}
std::vector<std::vector<glm::vec3>> makePaths()
{
	std::vector<std::vector<glm::vec3>> paths;

	std::vector<glm::vec3> path1;
	path1.push_back(glm::vec3(18, 0, 0));
	path1.push_back(glm::vec3(20, 0, 48));
	path1.push_back(glm::vec3(16, 0, 93));
	path1.push_back(glm::vec3(22, 0, 105));
	path1.push_back(glm::vec3(30, 0, 99));
	path1.push_back(glm::vec3(38, 0, 60));
	path1.push_back(glm::vec3(42, 0, 21));
	path1.push_back(glm::vec3(30, 0, 0));
	paths.push_back(path1);

	std::vector<glm::vec3> path2;
	path2.push_back(glm::vec3(12, 0, 0));
	path2.push_back(glm::vec3(12, 0, 39));
	path2.push_back(glm::vec3(10, 0, 78));
	path2.push_back(glm::vec3(12, 0, 96));
	path2.push_back(glm::vec3(14, 0, 105));
	path2.push_back(glm::vec3(20, 0, 111));
	path2.push_back(glm::vec3(30, 0, 105));
	path2.push_back(glm::vec3(38, 0, 87));
	path2.push_back(glm::vec3(44, 0, 60));
	path2.push_back(glm::vec3(48, 0, 36));
	path2.push_back(glm::vec3(46, 0, 21));
	path2.push_back(glm::vec3(40, 0, 0));
	paths.push_back(path2);

	std::vector<glm::vec3> path3;
	path3.push_back(glm::vec3(6, 0, 0));
	path3.push_back(glm::vec3(6, 0, 24));
	path3.push_back(glm::vec3(4, 0, 45));
	path3.push_back(glm::vec3(6, 0, 78));
	path3.push_back(glm::vec3(10, 0, 102));
	path3.push_back(glm::vec3(14, 0, 108));
	path3.push_back(glm::vec3(18, 0, 111));
	path3.push_back(glm::vec3(26, 0, 114));
	path3.push_back(glm::vec3(36, 0, 108));
	path3.push_back(glm::vec3(40, 0, 93));
	path3.push_back(glm::vec3(36, 0, 84));
	path3.push_back(glm::vec3(32, 0, 69));
	path3.push_back(glm::vec3(30, 0, 51));
	path3.push_back(glm::vec3(32, 0, 21));
	path3.push_back(glm::vec3(32, 0, 0));

	paths.push_back(path3);



	return paths;
}

void GlWindow::LoadModels()
{
	Renderable* temp;
	Model* model = new Model("Nissan.3DS");
	std::vector<Renderable*> models;
	std::vector<std::vector<glm::vec3>> paths = makePaths();
	int i = 1;
	for (auto path : paths)
	{
		temp = new Renderable(model);
		temp->SetLocalPosition(glm::vec3(i*6.0f, 0, 0));
		temp->SetScale(glm::vec3(0.01f));
		temp->color = colors[i % 3];
		//parent->SetLocalRotationEuler(-glm::vec3(glm::pi<float>() / 2, 0, 0));
		temp->SetAnimation(new CurveAnimation(path, 20.0f));
		objRend->AddRenderable(temp);
		cars.push_back(temp);
		i++;
	}
	temp = new Renderable(model);
	temp->SetLocalPosition(glm::vec3(0, 0, 0));
	temp->SetScale(glm::vec3(0.01f));
	temp->color = glm::vec3(1.0f);
	objRend->AddRenderable(temp);
	cameras[2]->SetParent(temp);
	cameras[2]->SetLocalPosition(glm::vec3(0,2,-3));
	cameras[3]->WatchComponent(temp);
	userCar = temp;
	LoadBackground("Palm2.3DS");
	//parent = new Renderable(model);

}

void GlWindow::LoadBackground(char* objPath)
{
	Model* model = new Model(objPath);
	//D3Component* obj = new D3Component();
	//obj->SetLocalPosition(glm::vec3(0, 0, 0));s
	Renderable* tab[10];
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		tab[i] = new Renderable(model);
		tab[i]->SetLocalPosition(glm::vec3(24, 0, 15+i*15));
		tab[i]->SetScale(glm::vec3((rand()%10+10) / 100.0));
		tab[i]->SetRotation(glm::quat(glm::vec3(glm::radians(-90.0f), 0, 0)));
		objRend->AddRenderable(tab[i]);
	}
	//tab[0]->SetLocalPosition(glm::vec3(10, 0, 0));


	//background;

	std::vector<Vertex>* vecs=new std::vector<Vertex>();
	std::vector<GLuint>* indices = new std::vector<GLuint>();
	vecs->push_back(Vertex(-20, 0, -20, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(-20, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, 120, 0, 1, 0, 1, 0));
	vecs->push_back(Vertex(100, 0, -20, 0, 1, 0, 1, 0));
	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	Mesh* mesh= new Mesh(*vecs, *indices);
	Model* mod = new Model(mesh);
	Renderable* rend = new Renderable(mod);
	rend->color = glm::vec3(0.2f, 0.2f, 0.2f);
	objRend->AddRenderable(rend);
	//path
	std::vector<Vertex>* vecsP = new std::vector<Vertex>();
	std::vector<GLuint>* indicesP = new std::vector<GLuint>();
	vecsP->push_back(Vertex(0, 0.02f, -10.0f, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(0, 0.02f, 110, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(50, 0.02f, 110, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(50, 0.02f, -10.0f, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(25, 0.02f, 10, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(25, 0.02f, 90, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(35, 0.02f, 90, 0, 1, 0, 1, 0));
	vecsP->push_back(Vertex(35, 0.02f, 10, 0, 1, 0, 1, 0));
	indicesP->push_back(0);
	indicesP->push_back(1);
	indicesP->push_back(4);
	indicesP->push_back(4);
	indicesP->push_back(1);
	indicesP->push_back(5);

	indicesP->push_back(1);
	indicesP->push_back(2);
	indicesP->push_back(5);
	indicesP->push_back(5);
	indicesP->push_back(2);
	indicesP->push_back(6);

	indicesP->push_back(2);
	indicesP->push_back(3);
	indicesP->push_back(6);
	indicesP->push_back(6);
	indicesP->push_back(3);
	indicesP->push_back(7);

	indicesP->push_back(3);
	indicesP->push_back(0);
	indicesP->push_back(7);
	indicesP->push_back(7);
	indicesP->push_back(0);
	indicesP->push_back(4);
	Mesh* meshP = new Mesh(*vecsP, *indicesP);
	Model* modP = new Model(meshP);
	rend = new Renderable(modP);
	rend->SetLocalPosition(glm::vec3(-5.0f, 0, 0));
	rend->color = glm::vec3(0.4f, 0.2f, 0.2f);
	objRend->AddRenderable(rend);
	//path


}


bool GlWindow::SetPixelsFormat(HDC dcHandle) const
{
	PIXELFORMATDESCRIPTOR pxd;
	ZeroMemory(&pxd, sizeof(pxd));
	pxd.nVersion = 1;
	pxd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pxd.iPixelType = PFD_TYPE_RGBA;
	pxd.cColorBits = 32;
	pxd.cDepthBits = 32;
	pxd.iLayerType = PFD_MAIN_PLANE;
	int pixelFormat = ChoosePixelFormat(dcHandle, &pxd);
	if (pixelFormat == 0)
		return false;
	if (!SetPixelFormat(dcHandle, pixelFormat, &pxd))
		return false;
	return true;
}

bool GlWindow::InitializeGlW(HWND windowHandle)
{
	DCHandle = ::GetDC(windowHandle);
	if (!SetPixelsFormat(DCHandle))
		return false;
	HGLRC tempRCHandle = wglCreateContext(DCHandle);
	if (tempRCHandle == nullptr)
		return false;
	if (!wglMakeCurrent(DCHandle, tempRCHandle))
		return false;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(nullptr, "Glew initialization failed", "Turbo Engine", MB_OK | MB_ICONERROR);
		return false;
	}


	const int majorMin = 3;
	const int minorMin = 3;
	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	if (major < majorMin || (major == majorMin && minor < minorMin))
	{
		MessageBox(nullptr, "OpenGL version is not sufficient", "Turbo Engine", MB_OK | MB_ICONERROR);
		return false;
	}
	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,majorMin,
		WGL_CONTEXT_MINOR_VERSION_ARB,minorMin,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,0
	};


	RCHandle = wglCreateContextAttribsARB(DCHandle, nullptr, attributes);

	if (RCHandle == nullptr)
		return false;
	if (!wglMakeCurrent(DCHandle, RCHandle))
		return false;

	wglDeleteContext(tempRCHandle);
	return true;
}

void GlWindow::DeleteGlW()
{
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(RCHandle);
	::ReleaseDC(windowHandle, DCHandle);
}

void GlWindow::SetBarInfo(HWND windowHandle)
{
	char buffer[256];
	GetWindowText(windowHandle, buffer, 256);
	const GLubyte* version = glGetString(GL_VERSION);
	strcat_s(buffer, " | openGL ");
	strcat_s(buffer, (char*)version);
	const GLubyte* provider = glGetString(GL_VENDOR);
	strcat_s(buffer, " | ");
	strcat_s(buffer, (char*)provider);
	const GLubyte* graphicCard = glGetString(GL_RENDERER);
	strcat_s(buffer, " | ");
	strcat_s(buffer, (char*)graphicCard);
	const GLubyte* glewVersion = glewGetString(GLEW_VERSION);
	strcat_s(buffer, " | ");
	strcat_s(buffer, (char*)glewVersion);
	SetWindowText(windowHandle, buffer);
}

void GlWindow::SetScene()
{
	ShaderProgram* shader = new ShaderProgram("BasicVertex.vsh", "BasicFragment.fsh");
	if (shader->programId == 0)
		exit(EXIT_FAILURE);
	objRend = new ObjectRenderer(windowWidth, windowHeight, shader);
	cameras.push_back(new Camera(glm::vec3(0, 2, -4), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	cameras.push_back(new Camera(glm::vec3(0, 55, 50), glm::quat(glm::vec3(glm::radians(65.0f), glm::radians(90.0f), 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 80));
	cameras.push_back(new Camera(glm::vec3(20, 65, 50), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	cameras.push_back(new Camera(glm::vec3(0, 25, 50), glm::quat(glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0), 1.0f, 200.0f, 60));
	
	cameraIndex = 0;
	actualCamera = cameras[0];
	LoadModels();
	actualLightning = new Scene(glm::vec3(0, 3, 3), glm::vec3(1, 1, 1), 0);
}

void GlWindow::DrawScene()
{
	if (shouldRender)
	{
		objRend->Render(actualCamera, actualLightning);
		SwapBuffers(DCHandle);
	}

}

void GlWindow::Animate(float time)
{
	objRend->Animate(time);
}

LRESULT GlWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long result = Window::WndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
		//case WM_SYSCOMMAND:
		//	if ((wParam & 0xFFF0) == SC_MINIMIZE)
		//	{
		//		shouldRender = false;
		//	}
		//	if ((wParam & 0xFFF0) == SC_MAXIMIZE)
		//	{
		//		shouldRender = true;
		//	}
		//	break;
	case WM_CREATE:
	{
		if (!InitializeGlW(hWnd))
		{
			MessageBox(nullptr, "Loading context failed", "Turbo Engine", MB_OK | MB_ICONERROR);
			throw 0;
			return EXIT_FAILURE;
		}
		SetBarInfo(hWnd);
		SetScene();
	}
	break;
	case WM_SIZE:
		objRend->ResizeWindow(windowWidth, windowHeight);
		if (windowWidth < 10 || windowHeight < 10)
			shouldRender = false;
		else
			shouldRender = true;
		break;
	case WM_DESTROY:
		DeleteGlW();
		break;
	case WM_PAINT:
		DrawScene();
		ValidateRect(hWnd, NULL);
		break;
	case WM_KEYDOWN:
		KeyDown(wParam);
		break;
	case WM_KEYUP:
		KeyUp(wParam);
		break;
	case WM_MOUSEMOVE:
		if (!mouseTracked)
			TrackMouse(windowHandle);
		MouseMoved(lParam, wParam);
		break;
	case WM_MOUSEHOVER:
		prevMousePos = { -1,-1 };
		break;
	case WM_MOUSELEAVE:
		prevMousePos = { -1,-1 };
		break;
	}
	return result;
}
