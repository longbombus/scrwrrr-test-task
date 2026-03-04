attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

uniform mat3 u_NormalMatrix;
uniform mat4 u_MVPMatrix;

uniform vec3 u_lightDirection;
uniform vec4 u_nightColor;
uniform float u_dayNightFactor;

varying vec4 v_light;
varying vec2 v_texCoord;

void main()
{
    float lightness = dot(normalize((u_NormalMatrix * a_normal)), normalize(u_lightDirection)) * 0.5 + 0.5;

    v_light = vec4(mix(vec3(1.0), u_nightColor.rgb, u_dayNightFactor), lightness);
    v_texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
    gl_Position = u_MVPMatrix * a_position;
}
