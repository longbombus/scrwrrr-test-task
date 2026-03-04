uniform sampler2D u_texture;
uniform sampler2D u_emissive;

varying vec3 v_normal;
varying vec2 v_texCoord;

void main()
{
    vec4 color = texture2D(u_texture, v_texCoord);
    vec3 emissive = texture2D(u_emissive, v_texCoord).rgb;
    color.rgb += emissive;
    gl_FragColor = color;
}
