/*
 * Vertex shader for the lighting pass on the g-buffer
 */

#version 330 core

// Inputs from screen space
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

// Output tex coords to the frag shader
out vec2 TexCoords;


void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 0.0, 1.0);
}


