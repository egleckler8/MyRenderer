#version 330 core
out vec4 FragColor;

// Each attribute is a color value
struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Each attribute is a color value
struct Light
{
    vec3 position;

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

uniform Material material;
uniform Light light;

void main()
{

    //
    // PHONG LIGHTING MODEL
    //

    // Ambient lighting
    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diffusion = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diffusion * vec3(texture(material.diffuse, TexCoords));

    // Specular lighting
    // viewPos is always (0,0,0) in view space!
    // so, we just reverse the direction of FragPos...
    // the view direction vector should be pointing back
    // towards the viewer
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);


    // Adding it all up and output
    vec3 result = (ambientLight + diffuseLight + specularLight) * attenuation;
    FragColor = vec4(result, 1.0f);


}