#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//update to do lighting in the vertex shader bc its prettier

out vec3 diffuse;
out vec3 ambient;
out vec3 specular;

out vec3 result;


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
    vec3 fragPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = projection * view * vec4(fragPos, 1.0);

    // ambient
    float ambientStrength = 0.1;
     ambient = ambientStrength * lightColor;

    //diffuse
    //get our normal
    vec3 norm = normalize(aNormal);
    //get our light direction
    vec3 lightDir = normalize(lightPos - fragPos);
    //get the dot product (the angle between them)
    float diff = max(dot(norm, lightDir), 0.0);
    //adjust for colour

    diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);


    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    specular = specularStrength * spec * lightColor;


    result = (ambient + diffuse + specular) * objectColor;

}
