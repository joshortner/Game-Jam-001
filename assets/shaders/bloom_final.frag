uniform sampler2D u_scene_texture;
uniform sampler2D u_bloom_texture;

//void main()
//{
    //vec4 scene_pixel = texture2D(u_scene_texture, gl_TexCoord[0].xy);
    //vec4 bloom_pixel = texture2D(u_bloom_texture, gl_TexCoord[0].xy);
    //gl_FragColor = scene_pixel + bloom_pixel;
//}

//uniform bool bloom;
uniform float u_exposure;

void main()
{   
    const float gamma = 2.2;      
    vec4 scene_pixel = texture2D(u_scene_texture, gl_TexCoord[0].xy);
    vec4 bloom_pixel = texture2D(u_bloom_texture, gl_TexCoord[0].xy);
    //gl_FragColor = scene_pixel + bloom_pixel;

    //if (bloom) {
    //    hdrColor += bloomColor; // additive blending
    //}

    scene_pixel += bloom_pixel;

    // tone mapping
    vec3 result = vec3(1.0) - exp(-scene_pixel.xyz * u_exposure);
    
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    gl_FragColor = vec4(result, scene_pixel.a);
}