#include "GLWindow.h"
#include "glew.h"
#include "wglew.h"
#include "Vertex.h"
#include "ShaderUtility.h"
#include "ModelLoader.h"
#include <vector>
#include "Mesh.h"
#include <time.h>

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
//Main Loop
WPARAM Window::Run()
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

		// robienie rzeczy.

		long actualTime = GetTickCount();
		elapsed = actualTime - time;
		time = actualTime;
		if (elapsed < 30.0L)
			Sleep(30.0L - elapsed);

	}
	return msg.wParam;
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

void GlWindow::LoadModels()
{
	std::vector<Vertex>* verts = new std::vector<Vertex>();
	Vertex vets[6];
	vets[0] = Vertex(-1, -1, 0, 1, 1, 1, 0, 0);
	vets[1] = Vertex(-1, 1, 0, 1, 1, 1, 0, 0);
	vets[2] = Vertex(1, 1, 0, 1, 1, 1, 0, 0);
	vets[3] = Vertex(-1, -1, 0, 1, 1, 1, 0, 0);
	vets[4] = Vertex(1, 1, 0, 1, 1, 1, 0, 0);
	vets[5] = Vertex(1, -1, 0, 1, 1, 1, 0, 0);
	for (int i = 0; i < 6; i++)
		verts->push_back(vets[i]);
	Mesh* mesh = new Mesh(verts);
	Renderable* rend = new Renderable(mesh);
	objRend->AddRenderable(rend);
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

void GlWindow::DrawScene()
{
	objRend->Render(actualCamera);

	SwapBuffers(DCHandle);
}

LRESULT GlWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long result = Window::WndProc(hWnd, message, wParam, lParam);
	switch (message)
	{
	case WM_CREATE:
	{
		if (!InitializeGlW(hWnd))
		{
			MessageBox(nullptr, "Loading context failed", "Turbo Engine", MB_OK | MB_ICONERROR);
			throw 0;
			return EXIT_FAILURE;
		}
		//shaderId = ShaderUtility::LoadShader("BasicVertex.vsh", "BasicFragment.fsh");
		ShaderProgram* shad = new ShaderProgram("BasicVertex.vsh", "BasicFragment.fsh");
		if (shad->programId == 0)
			exit(EXIT_FAILURE);
		SetBarInfo(hWnd);
		objRend = new ObjectRenderer(windowWidth, windowHeight, shad);
		actualCamera = new Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 1, 100, 45, 1920.0 / 1080.0);
		LoadModels();
	}
	break;
	case WM_SIZE:
		objRend->ResizeWindow(windowWidth, windowHeight);
		break;
	case WM_DESTROY:
		DeleteGlW();
		break;
	case WM_PAINT:
		DrawScene();
		ValidateRect(hWnd, NULL);
		break;
	}
	return result;
}
