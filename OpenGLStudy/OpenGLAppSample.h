#pragma once

#include "stdafx.h"

typedef unsigned int				uint;

class OpenGLAppSample
{
public:
	OpenGLAppSample(uint width, uint height, std::string name);
	virtual ~OpenGLAppSample();
	
	void SetShaderFilePath(const char** path);
	virtual int Run() = 0;

protected:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDestroy() = 0;

	virtual void PrepareData() = 0;
	GLuint LoadShader();

	std::string title;
	uint m_width;
	uint m_height;

private:
	const char** m_shaderFilePath;
};