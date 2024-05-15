/*
 * Fragment shader for the lighting pass on the g-buffer
 */

#version 330 core

#define SHININESS_RANGE 5000.0
#define SHININESS_MIN 2.0

// Receive texture coordinates from screen space
in vec2 TexCoords;

out vec4 FragColor;

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

// Texture maps from the g-buffer
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

// Lighting uniforms
#define MAX_NUM_PT_LIGHTS 32
uniform PointLight pointLights[MAX_NUM_PT_LIGHTS];
uniform int numActivePtLights; // how many lights are in the scene?

uniform DirectionalLight dirLight;
uniform bool dirLightIsActive; // is there a directional light on the scene?

// Lighting in view or world space?? WORLD for now
uniform vec3 viewPos;


// Fn declarations for lighting type calculations
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 Albedo, float Specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Albedo, float Specular);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Albedo, float Specular)
float CalcShininess();



void main() {

    // Get the data from the G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    // Then, calculate lighting as usual:
    vec3 viewDir = normalize(viewPos - FragPos);

    // directional lighting
    vec3 directionalLighting = CalcDirectionalLight(dirLight, Normal, viewDir, Albedo, Specular);

    // point lighting
    vec3 pointLighting = vec3(0.0f);
    for (int i = 0; i < MAX_NUM_PT_LIGHTS && i < numActivePtLights; i++)
    {
        pointLighting += CalcPointLight(pointLights[i], Normal, FragPos, viewDir, Albedo, Specular);
    }

    // spot lighting
    // vec3 spotLighting = CalcSpotLight(spotLight, Normal, FragPos, viewDir, Albedo, Specular);

    // add up the results & output
    vec3 result = directionalLighting + pointLighting; // + spotLighting;
    FragColor = vec4(result, 1.0);
}



// Calculates the directional light on this fragment.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 Albedo, float Specular)
{

    // Compute light direction
    vec3 lightDir = normalize(-light.direction);

    // ambient lighting
    vec3 ambientLight = light.ambient * Albedo;

    // diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * Albedo;

    // specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), CalcShininess());
    vec3 specularLight = light.specular * spec * Specular;

    // No attenuation on directional light (right now).
    //specularLight *= 0.0;

    // combine results & output
    vec3 result = ambientLight + diffuseLight + specularLight;
    return result;

}



// Calculates lighting on a fragment from a single point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 Albedo, float Specular)
{

    // Compute light direction
    vec3 lightDir = normalize(light.position- fragPos);

    // ambient lighting
    vec3 ambientLight = light.ambient * Albedo;

    // diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * Albedo;

    // specular lighting
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), CalcShininess());
    vec3 specularLight = light.specular * spec * Specular;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // Attenuate!
    diffuseLight *= attenuation;
    specularLight *= attenuation;

    // combine the results and output
    vec3 result = ambientLight + diffuseLight + specularLight;
    return result;

}



// Calculates spot lighting on a fragment
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//
//    // Must convert the light direction into view space!
//    vec3 lightDirView = vec3(ViewMat * vec4(light.direction, 1.0f));
//
//    // angle between light direction and spotlight direction
//    float theta = dot(lightDirView, normalize(-lightDirView));
//
//    // For the blur like a normal spotlight/flashlight
//    float epsilon = light.cutoffAngle - light.outerCutoffAngle;
//    float intensity = clamp((theta - light.outerCutoffAngle) / epsilon, 0.0, 1.0);
//
//    // Ambient lighting is always the same regardless of
//    // whether this fragment is in the spotlight
//    vec3 ambientLight = light.ambient * Albedo;
//
//    // Must convert the light position into view space!
//    vec3 lightPosView = vec3(ViewMat * vec4(light.position, 1.0f));
//
//    // Attenuation
//    float distance = length(lightPosView - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
//
//    // We'll add lighting contributions to this vector
//    vec3 result = vec3(0.0f);
//
//    // Only do other lighting calculations if the fragment
//    // is in the spotlight
//    if (theta > light.cutoffAngle)
//    {
//
//        // Compute light direction
//        vec3 lightDir = normalize(lightPosView - fragPos);
//
//        // diffuse lighting
//        float diff = max(dot(normal, lightDir), 0.0);
//        vec3 diffuseLight = light.diffuse * diff * Albedo;
//
//        // specular lighting
//        vec3 reflectDir = reflect(-lightDir, normal);
//
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), CalcShininess());
//        vec3 specularLight = light.specular * spec * Specular;
//
//        result += (specularLight + diffuseLight) * attenuation * intensity;
//
//    }
//
//    // Add in the ambient light, of course!
//    result += ambientLight;
//
//    return result;
//
//}



// Calculates the shininess of this material at the tex coords
float CalcShininess()
{
    // Get the shininess exponent from the R channel of the texture, since it's BW
    // Then make sure to multiply to transform the 0.0-1.0 to the shininess range!
    float shininess = 50; // SHININESS_RANGE * texture(texture_roughness_1, TexCoords).r + SHININESS_MIN;
    return shininess;
}
