#include "targetver.h"
#include "Shader.h"
#include "Application.h"
#include "utilities.h" 
//#include "vld.h"

int Globals::screenWidth = 1000;
int Globals::screenHeight = 700;
int Globals::item_size = 50;
int Globals::menuGPWidth = 350;
int Globals::colMap = 14;			//must change m_map in GSPlay too
int Globals::rowMap = 14;			//must change m_map in GSPlay too
int Globals::enermy_Id = 0;
int Globals::boom_Id = 0;
float Globals::timeEnermyMoving = 0.8f;

GLint Init(ESContext* esContext)
{
	Application::GetInstance()->Init();
	return 0;
}

void Draw(ESContext* esContext)
{
	Application::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, GLfloat deltaTime)
{
	Application::GetInstance()->Update(deltaTime);
}

void OnKey(ESContext* esContext, unsigned char key, bool bbIsPresseded)
{
	Application::GetInstance()->HandleKeyEvent(key, bbIsPresseded);
}

void OnMouseClick(ESContext* esContext, GLint x, GLint y, bool bbIsPresseded)
{
	Application::GetInstance()->HandleTouchEvent(x, y, bbIsPresseded);
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	Application::GetInstance()->HandleMouseMoveEvent(x, y);
}

void CleanUp()
{
	Application::GetInstance()->Exit();
	Application::FreeInstance();
}

GLint _tmain(GLint argc, _TCHAR* argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Boom", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, OnKey);
	esRegisterMouseFunc(&esContext, OnMouseClick);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//printf("Press any key...\n");
	//_getch();

	return 0;
}