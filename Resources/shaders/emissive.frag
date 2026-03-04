uniform sampler2D u_texture;
uniform sampler2D u_emissive;

varying float v_ligtness;
varying vec2 v_texCoord;

void main()
{
    vec3 albedo = texture2D(u_texture, v_texCoord).rgb;
    vec3 emissive = texture2D(u_emissive, v_texCoord).rgb;
    gl_FragColor = vec4(
        albedo * v_ligtness + emissive * (1.0 - v_ligtness),
        1.0
    );
}
