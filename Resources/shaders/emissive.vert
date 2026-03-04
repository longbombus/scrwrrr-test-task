attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

uniform mat4 u_MVPMatrix;

varying vec3 v_normal;
varying vec2 v_texCoord;

void main()
{
    v_normal = a_normal;
    v_texCoord = vec2(a_texCoord.x, 1.0 - a_texCoord.y);
    gl_Position = u_MVPMatrix * a_position;
}
