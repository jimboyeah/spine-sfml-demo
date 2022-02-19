#version 110

uniform sampler2D uTexture;

void main()
{
    // lookup the pixel in the uTexture
    vec4 pixel = texture2D(uTexture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel;
}
// https://www.sfml-dev.org/tutorials/2.5/graphics-shader.php#loading-shaders