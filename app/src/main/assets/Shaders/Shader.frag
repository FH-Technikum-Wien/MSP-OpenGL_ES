#version 300 es
precision mediump float;

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D diffuseTexture;

void main()
{
    // Main texture color
    vec3 color = texture(diffuseTexture, TexCoord).rgb;
    FragColor = vec4(color, 1.0);
}