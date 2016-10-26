precision mediump float;

uniform	sampler2D			u_texture;
uniform	vec3					u_camPos;

varying	vec2				v_uvTexture;
varying	vec4				v_posWorld;

void main()
{
	//vec4 finalColor=texture2D(u_texture,v_uv);
	//if(finalColor.a <=0.2)
		//discard;
	gl_FragColor = vec4(1.0,0,0,1.0);
}
