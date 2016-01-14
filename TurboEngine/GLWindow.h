#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <windows.h>
#include <glm\glm.hpp>
#include "ObjectRenderer.h"

class Window
{
protected:
	HWND windowHandle;
	long windowWidth;
	long windowHeight;
public:
	Window() :windowHandle(nullptr) {};
	bool Initialize(HINSTANCE applicationHandle, POINT windowPosition, POINT windowSize, bool fullScreen=false, bool resolutionChange=true);
	bool ChangeResolution(long width, long height, long colorDepth=32) const;
	WPARAM Run();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
class GlWindow : public Window
{
private:
	HGLRC RCHandle;
	HDC DCHandle;

	unsigned int vao;
	unsigned int vbo[3];
	void InitializeVertexBuffer();
	void DeleteVertexBuffer();
	unsigned int shaderId;
	ObjectRenderer* objRend;

public:
	GlWindow() : Window(), RCHandle(nullptr), DCHandle(nullptr) {};
	bool SetPixelsFormat(HDC dcHandle) const;
	bool InitializeGlW(HWND windowHandle);
	void DeleteGlW();
	void SetBarInfo(HWND windowHandle);
	//void SetScene(bool isometric=false);
	void DrawScene();
	LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
} okno;

#endif