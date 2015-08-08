#pragma once
#include "OpenGLAppSample.h"

class OpenGLApp :
	public OpenGLAppSample
{
public:
	OpenGLApp(uint width, uint height, std::string name);
	virtual ~OpenGLApp();
	
	int Run();
	void SetBuffersData(glm::vec3 * vert, glm::vec3 * color, GLuint* ind, uint& num);

protected:
	
	void LoadAssets();
	void PrepareData();
	void OnInit();
	void OnUpdate();
	void OnRender();
	void OnDestroy();

private:
	GLuint m_program;
	GLuint m_VAO;
	GLuint m_vertexBuff;
	GLuint m_indexBuff;
	GLuint m_colorBuff;
	glm::vec3*		m_vertexData;
	glm::vec3*		m_colorData;
	GLuint*			m_indexData;
	uint			m_numVertex;
	SDL_Window*	m_window;
	SDL_GLContext m_context;
	SDL_Event m_event;
	bool m_running;
};

