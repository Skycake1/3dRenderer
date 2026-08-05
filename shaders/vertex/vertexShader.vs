#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 offset2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float offset;

void main()
{
    offset2 = vec3(aPos.x + offset,aPos.y,aPos.z);
    gl_Position = projection * view * model * vec4(offset2, 1.0);
    TexCoord = aTexCoord;
}
