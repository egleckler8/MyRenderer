/*
 * Copied from LearnOpenGL pg. 216
 */

#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projMat;
uniform mat4 viewMat;

void main()
{
    TexCoords = aPos;

    // Early depth testing--trick the depth buffer?
    // https://learnopengl.com/Advanced-OpenGL/Cubemaps
    vec4 pos = projMat * viewMat * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}