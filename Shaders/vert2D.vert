#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection; // 画面全体に表示するための直交投影行列

out vec2 TexCoord;

void main()
{
    vec4 pos = vec4(aPos, 0.0, 1.0);
    gl_Position = uProjection * uModel * pos;
    TexCoord = aTexCoord;
}
