/*
 * Copied from LearnOpenGL pg. 216
 */

#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skyboxTex;

void main()
{
    FragColor = texture(skyboxTex, TexCoords);
    FragColor = vec4(TexCoords, 1.0);
}