#version 330 core
out vec4 FragColor;

in vec4 ourColor;
// in vec2 TexCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float uCompare;

void main() {
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), vec4(texture(texture2, TexCoord)).a * uCompare);
    FragColor = ourColor;
}
