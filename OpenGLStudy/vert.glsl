#version 450 core
in vec4 color;
in vec4 vPosition;
out vec4 vColor;
//uniform mat4 MVP;

void main( void )
{
    gl_Position = vPosition;
    vColor = color;
}
