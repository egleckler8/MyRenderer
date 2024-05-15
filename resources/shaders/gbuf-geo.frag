/*
 * Use this shader to render to the g-buffer!
 */
#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

// Outputs to the g-buffer
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

// Material textures--used by the particular
// render object that's drawing
uniform sampler2D texture_diffuse_1;
uniform sampler2D texture_specular_1;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;

    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);

    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(texture_diffuse_1, TexCoords).rgb;

    // store specular intensity in gAlbedoSpec’s alpha component
    gAlbedoSpec.a = texture(texture_specular_1, TexCoords).r;

}
