uniform sampler2D u_texture;
uniform sampler2D u_emissive;

uniform vec4 u_nightColor;
uniform float u_dayNightFactor;

varying vec2 v_texCoord;

void main()
{
    vec3 albedo = texture2D(u_texture, v_texCoord).rgb;
    vec3 emissive = texture2D(u_emissive, v_texCoord).rgb;
    
    vec3 color
        = albedo * mix(vec3(1.0), u_nightColor.rgb, u_dayNightFactor)
        + emissive * u_dayNightFactor;

    gl_FragColor = vec4(color, 1.0);
}
