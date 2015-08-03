#include "OpenGLApp.h"



OpenGLApp::OpenGLApp(uint width, uint height, std::string name):
	OpenGLAppSample(width,height,name),
	m_running (true)
{
}


OpenGLApp::~OpenGLApp()
{
	delete[] m_vertexData;
	delete[] m_colorData;
	delete[] m_indexData;
	std::cout << "Destructor Successfull." << std::endl;
}

int OpenGLApp::Run()
{
	OnInit();
	while (m_running)
	{
		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT || m_event.key.keysym.sym == SDLK_ESCAPE) { m_running = false; }
		}
		OnUpdate();
		OnRender();
		SDL_GL_SwapWindow(m_window);
	}
	OnDestroy();
	SDL_Quit();
	return 0;
}

void OpenGLApp::SetBuffersData(glm::vec2 * vert, glm::vec3 * color, GLuint * ind)
{
	m_vertexData = vert;
	m_colorData = color;
	m_indexData = ind;
}

void OpenGLApp::CreateData()
{
	m_program = LoadShader();

	glCreateVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glCreateBuffers(1, &m_vertexBuff);
	glNamedBufferStorage(m_vertexBuff, sizeof(m_vertexData), m_vertexData, GL_MAP_WRITE_BIT);
	if(glIsBuffer(m_vertexBuff))
		std::cout << "Create vert buffer Successfull." << std::endl;

	
	glCreateBuffers(1, &m_colorBuff);
	glNamedBufferStorage(m_colorBuff, sizeof(m_colorData), m_colorData, GL_MAP_WRITE_BIT);
	if (glIsBuffer(m_vertexBuff))
		std::cout << "Create color buffer Successfull." << std::endl;

	glCreateBuffers(1, &m_indexBuff);
	glNamedBufferStorage(m_indexBuff, sizeof(m_indexData), m_indexData, GL_MAP_WRITE_BIT);
	if (glIsBuffer(m_indexBuff))
		std::cout << "Create index buffer Successfull." << std::endl;

	std::cout << "Create Data Successfull." << std::endl;
}


void OpenGLApp::PrepareData()
{
	CreateData();
	
	glBindVertexArray(m_VAO);
	glUseProgram(m_program);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuff);
	GLuint vPosition = glGetAttribLocation(m_program, "vPosition");
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuff);
	GLuint vColor = glGetAttribLocation(m_program, "color");
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vColor);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuff);

	glClearColor(0.3f, 0.5f, 0.8f, 0.0f);
	std::cout << "Prepare Data Successfull." << std::endl;
}

void OpenGLApp::OnInit()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);
	m_context = SDL_GL_CreateContext(m_window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);
	std::cout << "OPENGL VERSION: " << (const char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL VERSION : " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	PrepareData();
	std::cout << "Init Successfull." << std::endl;
}

void OpenGLApp::OnUpdate()
{
}

void OpenGLApp::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void OpenGLApp::OnDestroy()
{
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_vertexBuff);
	glDeleteBuffers(1, &m_colorBuff);
	glDeleteBuffers(1, &m_indexBuff);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_VAO);
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	std::cout << "Destroy Successfull." << std::endl;
}
