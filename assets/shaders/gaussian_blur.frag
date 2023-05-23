// Two pass Gaussian Blur Shader
uniform bool horizontal;
uniform sampler2D texture;
uniform float width;
uniform float height; 

float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec3 result = texture2D(texture, gl_TexCoord[0].xy).rgb * weight[0]; // current fragment's contribution
    vec2 tex_offset = vec2(1.0 / width, 1.0 / height); // gets size of single texel

    if (horizontal) {
        for(int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else {
        for (int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    gl_FragColor = vec4(result, 1.0);
}