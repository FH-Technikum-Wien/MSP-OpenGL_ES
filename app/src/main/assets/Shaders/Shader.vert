#version 300 es
// Position with vertex attribute position 0
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Texture
layout (location = 2) in vec2 aTexCoord;


// Local to World
uniform mat4 modelMat;
// World to View (Camera)
uniform mat4 viewMat;
// View to Clip (perspective)
uniform mat4 projectionMat;

out vec2 TexCoord;

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}