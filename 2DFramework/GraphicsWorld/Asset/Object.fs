precision mediump float;

uniform		sampler2D			u_texture2D;
//uniform		vec3					u_posCamera;

varying		vec2					v_uvTexture;
//varying		vec4					v_posWorld;

void main()
{
	vec4 finalColor=texture2D(u_texture2D,v_uvTexture);
	//if(finalColor.a <=0.2)
		//discard;
	gl_FragColor = finalColor;
}
