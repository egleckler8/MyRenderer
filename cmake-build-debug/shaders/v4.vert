#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 modelViewMat;
uniform mat4 projMat;
uniform mat3 normalMat;


void main()
{
    // Put fragment position into view space
    FragPos = vec3(modelViewMat * vec4(aPos, 1.0f));
    Normal = normalMat * aNormal;

    // Transform the position into clip perspective
    gl_Position = projMat * modelViewMat * vec4(aPos, 1.0);

    TexCoords = aTexCoords;

}