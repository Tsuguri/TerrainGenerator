#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <windows.h>
#include <glm\glm.hpp>
#include "ObjectRenderer.h"
#include "Scene.h"

class Window
{
protected:
	HWND windowHandle;
	long windowWidth;
	long windowHeight;
	bool shouldRun = true;
public:
	Window() :windowHandle(nullptr) {};
	bool Initialize(HINSTANCE applicationHandle, POINT windowPosition, POINT windowSize, bool fullScreen=false, bool resolutionChange=true);
	bool ChangeResolution(long width, long height, long colorDepth=32) const;

	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
class GlWindow : public Window
{
private:
	HGLRC RCHandle;
	HDC DCHandle;

	void LoadModels();
	ObjectRenderer* objRend;
	std::vector<ModelRenderable*> cars;
	bool raceStarted = false;
	int cameraIndex;
	std::vector<Camera*> cameras;
	D3Component* temp;
	ModelRenderable* userCar;

	Camera* actualCamera;
	Scene* actualLightning;
	void UpdateObjects(float);
	POINT prevMousePos={-1,-1};
	bool mouseTracked = false;
	bool keyPressed[1024];
	void KeyDown(WPARAM wParam);
	void KeyUp(WPARAM wParam);
	bool shouldRender = true;
public:
	WPARAM Run();

	void KeyControl(float time);
	void MouseMoved(LPARAM lParam,WPARAM wParam);
	void StartRace();
	void StopRace();
	
	void NextCamera();

	GlWindow() : Window(), RCHandle(nullptr), DCHandle(nullptr) {};
	bool SetPixelsFormat(HDC dcHandle) const;
	bool InitializeGlW(HWND windowHandle);
	void DeleteGlW();
	void SetBarInfo(HWND windowHandle);

	void SetScene();
	void DrawScene();
	void Animate(float time);



	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
} okno;

#endif