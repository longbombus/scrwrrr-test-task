uniform sampler2D u_texture;
uniform sampler2D u_emissive;
uniform float u_dayNightFactor;

varying vec4 v_light;
varying vec2 v_texCoord;

void main()
{
    vec3 albedo = texture2D(u_texture, v_texCoord).rgb;
    vec3 emissive = texture2D(u_emissive, v_texCoord).rgb;
    gl_FragColor = vec4(
        (albedo * v_light.rgb) * v_light.a + emissive * u_dayNightFactor,
        1.0
    );
}
