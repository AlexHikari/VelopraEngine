#version 330 core
in vec4 VertexColor;
in vec2 TexCoords;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    // Combine texture color with vertex color (if texture is used)
    FragColor = texture(u_Texture, TexCoords) * VertexColor;
}
