attribute	vec3				a_posLocal;
attribute	vec2				a_uvTexture;

uniform	mat4				u_MVP;
uniform	mat4				u_wMatrix;

varying	vec2				v_uvTexture;
varying	vec4				v_posWorld;

void main()
{
	vec4 posLocal = vec4(a_posLocal, 1.0);
	gl_Position = u_MVP * a_posLocal;
	
	v_uvTexture = a_uvTexture;
	v_posWorld = u_wMatrix * a_posLocal;
}