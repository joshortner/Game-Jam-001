// Two pass Gaussian Blur Shader
uniform bool horizontal;
uniform sampler2D texture;
uniform float width;
uniform float height; 

float weight[5];
void main()
{
    weight[0] = 0.227027;
    weight[1] = 0.1945946;
    weight[2] = 0.1216216;
    weight[3] = 0.054054;
    weight[4] = 0.016216;
    
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec3 result = texture2D(texture, gl_TexCoord[0].xy).rgb * weight[0]; // current fragment's contribution
    vec2 tex_offset = vec2(1.0 / width, 1.0 / height); // gets size of single texel

    if (horizontal) {
        for(int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(tex_offset.x * float(i), 0.0)).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(tex_offset.x * float(i), 0.0)).rgb * weight[i];
        }
    }
    else {
        for (int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(0.0, tex_offset.y * float(i))).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(0.0, tex_offset.y * float(i))).rgb * weight[i];
        }
    }
    gl_FragColor = vec4(result, 1.0);
}