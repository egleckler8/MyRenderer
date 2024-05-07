#version 330 core
out vec4 FragColor;

// Each attribute is a color value
struct Material
{
    // must use this naming convention for texture uniforms
    // in order to work with the mesh class!
    sampler2D texture_diffuse_1;
    sampler2D texture_specular_1;

    float shininess;
};


struct PointLight
{
    vec3 position; // world space

    // Color values for Phong
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attentuation coeffs:
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight
{
    vec3 direction; // world space

    // Color values for Phong
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position; // world space
    vec3 direction; // ^
    float cutoffAngle; // rads
    float outerCutoffAngle; // ^

    // Color values for Phong
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attentuation coeffs:
    float constant;
    float linear;
    float quadratic;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat4 ViewMat;

#define NUM_POINT_LIGHTS 1

uniform Material material;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform DirectionalLight dirLight;
uniform SpotLight spotLight;

// Fn declarations for lighting type calculations
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{


    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);

    // directional lighting
    vec3 directionalLighting = CalcDirectionalLight(dirLight, norm, viewDir);

    // point lighting
    vec3 pointLighting = vec3(0.0f);
    for (int i = 0; i < NUM_POINT_LIGHTS; i++)
    {
        pointLighting += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // spot lighting
    vec3 spotLighting = CalcSpotLight(spotLight, norm, FragPos, viewDir);

    // add up the results & output
    vec3 result = directionalLighting + pointLighting;
    FragColor = vec4(result, 1.0f);


}



// Calculates the directional light on this fragment.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{

    // Compute light direction
    // Must convert the light direction into view space!
    vec3 lightDirView = vec3(ViewMat * vec4(light.direction, 1.0f));
    vec3 lightDir = normalize(-lightDirView);

    // ambient lighting
    vec3 ambientLight = light.ambient * vec3(texture(material.texture_diffuse_1, TexCoords));

    // diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * vec3(texture(material.texture_diffuse_1, TexCoords));

    // specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * spec * vec3(texture(material.texture_specular_1, TexCoords));

    // No attenuation on directional light (right now).

    // combine results & output
    vec3 result = ambientLight + diffuseLight + specularLight;
    return result;

}



// Calculates lighting on a fragment from a single point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{

    // Compute light direction
    // Must convert the light position into view space!
    vec3 lightPosView = vec3(ViewMat * vec4(light.position, 1.0f));
    vec3 lightDir = normalize(lightPosView - fragPos);

    // ambient lighting
    vec3 ambientLight = light.ambient * vec3(texture(material.texture_diffuse_1, TexCoords));

    // diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * vec3(texture(material.texture_diffuse_1, TexCoords));

    // specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * spec * vec3(texture(material.texture_specular_1, TexCoords));

    // Attenuation
    float distance = length(lightPosView - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);


    // combine the results and output
    vec3 result = (ambientLight + diffuseLight + specularLight) * attenuation;
    return result;

}



// Calculates spot lighting on a fragment
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{

    // Must convert the light direction into view space!
    vec3 lightDirView = vec3(ViewMat * vec4(light.direction, 1.0f));

    // angle between light direction and spotlight direction
    float theta = dot(lightDirView, normalize(-lightDirView));

    // For the blur like a normal spotlight/flashlight
    float epsilon = light.cutoffAngle - light.outerCutoffAngle;
    float intensity = clamp((theta - light.outerCutoffAngle) / epsilon, 0.0, 1.0);

    // Ambient lighting is always the same regardless of
    // whether this fragment is in the spotlight
    vec3 ambientLight = vec3(light.ambient * vec3(texture(material.texture_diffuse_1, TexCoords)));

    // Must convert the light position into view space!
    vec3 lightPosView = vec3(ViewMat * vec4(light.position, 1.0f));

    // Attenuation
    float distance = length(lightPosView - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // We'll add lighting contributions to this vector
    vec3 result = vec3(0.0f);

    // Only do other lighting calculations if the fragment
    // is in the spotlight
    if (theta > light.cutoffAngle)
    {

        // Compute light direction
        vec3 lightDir = normalize(lightPosView - fragPos);

        // diffuse lighting
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuseLight = light.diffuse * diff * vec3(texture(material.texture_diffuse_1, TexCoords));

        // specular lighting
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specularLight = light.specular * spec * vec3(texture(material.texture_specular_1, TexCoords));

        result += (specularLight + diffuseLight) * attenuation * intensity;

    }

    // Add in the ambient light, of course!
    result += (ambientLight * attenuation);

    return result;

}