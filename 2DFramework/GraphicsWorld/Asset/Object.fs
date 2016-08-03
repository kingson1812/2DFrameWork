precision mediump float;

uniform	sampler2D			u_texture;
uniform	vec3					u_camPos;
uniform	vec4					u_fogColor;
//uniform	float						u_fogStart;
//uniform	float						u_fogRange;

varying	vec2					v_uv;
varying	vec4					v_posW;

void main()
{
	//float lerpValue = clamp(((distance(v_posW,u_camPos)-u_fogStart)/u_fogRange),0.0,1.0);
	vec4 finalColor=texture2D(u_texture,v_uv);
	if(finalColor.a <=0.2)
		discard;
	gl_FragColor = finalColor;
}
