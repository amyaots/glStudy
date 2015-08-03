#include "OpenGLApp.h"

//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd )
int wmain(int argc, char* argv[])
{
	glm::vec2 vert[] = { glm::vec2(-0.5f, -0.5f),
						 glm::vec2(0.f, 0.5f),
						 glm::vec2(0.5f, -0.5f) };
	glm::vec3 col[] = { glm::vec3(1.f, 0.f,0.f),
						glm::vec3(0.f, 1.f, 0.f),
						glm::vec3(0.f, 0.f, 1.f) };
	GLuint ind[] = { 0, 1, 2 };

	const char * path[] = { "vert.glsl", "frag.glsl" };

	OpenGLApp* app = new OpenGLApp(800, 600, "Test app");

	app->SetShaderFilePath(path);
	app->SetBuffersData(vert, col, ind);	

	return app->Run();;
}