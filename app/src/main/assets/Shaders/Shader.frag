#version 300 es
precision mediump float;

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = vec4(TexCoord.x, TexCoord.y, 1.0, 1.0);
}