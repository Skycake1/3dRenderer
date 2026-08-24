#version 330 core
out vec4 FragColor;


in vec3 ambient;
in vec3 diffuse;
vec3 specular;



in vec3 normal;
in vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightColor;


float specularStrength = 0.5;
void main()
{
  //  vec3 result = (ambient + diffuse + specular) * objectColor;

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);


    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);

}
