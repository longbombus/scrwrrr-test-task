attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

uniform mat3 u_NormalMatrix;
uniform mat4 u_MVPMatrix;
uniform vec3 u_lightDirection;

varying float v_ligtness;
varying vec2 v_texCoord;

void main()
{
    v_ligtness = dot(normalize((u_NormalMatrix * a_normal)), normalize(u_lightDirection)) * 0.5 + 0.5;
    v_texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
    gl_Position = u_MVPMatrix * a_position;
}
