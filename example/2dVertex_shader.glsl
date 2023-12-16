#version 330 core
layout (location = 0) in vec2 aPos;       // Position variable
layout (location = 1) in vec4 aColor;     // Color variable
layout (location = 2) in vec2 aTexCoords; // Texture coordinate variable

// Uniforms for transformation matrices
uniform mat4 u_Projection;

// Outputs to the fragment shader
out vec4 VertexColor;
out vec2 TexCoords;

void main()
{
    // Apply projection transformation and output position
    gl_Position = u_Projection * vec4(aPos, 0.0, 1.0);

    // Pass color and texture coordinates to the fragment shader
    VertexColor = aColor;
    TexCoords = aTexCoords;
}