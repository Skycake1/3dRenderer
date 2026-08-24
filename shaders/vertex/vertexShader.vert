#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//update to do lighting in the vertex shader bc its prettier

out vec3 diffuse;
out vec3 ambient;
out vec3 specular;

out vec3 fragPos;
out vec3 normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightColor;


void main()
{
    fragPos = vec3(model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;


    gl_Position = projection * view * vec4(fragPos, 1.0);

    // ambient
    float ambientStrength = 0.1;
    ambient = ambientStrength * lightColor;

    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    diffuse = diff * lightColor;


}
