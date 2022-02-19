#version 140

in vec2 texCoord;
out vec4 FragColor;
uniform float d;
uniform sampler2D image;

void main()
{
    FragColor =
    ( texture( image , vec2(texCoord.x + d, texCoord.y))
    + texture( image , vec2(texCoord.x, texCoord.y + d))
    + texture( image , vec2(texCoord.x - d, texCoord.y))
    + texture( image , vec2(texCoord.x, texCoord.y - d))) / 4.0;
}
// Listing 1.5. Image-smoothing shader.