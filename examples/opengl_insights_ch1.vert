#version 130

out vec2 texCoord;
in vec4 vPosition;
void main()
{
    texCoord = gl_MultiTexCoord0.xy;
    // texCoord    = vec2(1, 1);
    gl_Position = vPosition;
}
// Listing 1.3. Hello World vertex shader.
