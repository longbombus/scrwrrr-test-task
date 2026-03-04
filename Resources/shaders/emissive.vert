attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

uniform mat4 u_MVPMatrix;

uniform vec4 u_nightColor;
uniform float u_dayNightFactor;

varying vec3 v_light;
varying vec2 v_texCoord;

void main()
{
    v_light = mix(vec3(1.0), u_nightColor.rgb, u_dayNightFactor);
    v_texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
    gl_Position = u_MVPMatrix * a_position;
}
