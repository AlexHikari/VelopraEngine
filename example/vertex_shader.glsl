#version 330 core
layout (location = 0) in vec3 aPos;       // Position variable
layout (location = 1) in vec3 aNormal;    // Normal variable
layout (location = 2) in vec2 aTexCoords; // Texture coordinate variable

// Uniforms for transformation matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// Outputs to the fragment shader
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    // Apply transformations and output position
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);

    // Pass normals and texture coordinates to the fragment shader
    Normal = aNormal;
    TexCoords = aTexCoords;
}