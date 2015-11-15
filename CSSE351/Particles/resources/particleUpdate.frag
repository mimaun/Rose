#version 330

uniform uint mapSizeX;
uniform uint mapSizeY;
uniform uint increaseVelocity;

in vec4 pos;
in vec4 vel;

layout(location = 0) out vec4 posOutTexture;
layout(location = 1) out vec4 velOutTexture;

void main()
{
	int stepCount = 10;
	float t = 1.0f/stepCount/10;
	
	vec3 p = pos.xyz;
	vec3 v = vel.xyz;
	vec3 a = normalize(-p) * 1; //assumes mass is at 0,0,0
	
	for(int i=0; i<stepCount; i++) {
		//TODO update p and v
        p = p + v*t + 0.5 * a * t * t;
        v = v + a*t;
        
        if(increaseVelocity == 1u)
            v = v * (1+t);
		
	}
	
	posOutTexture = vec4(p,1);
	velOutTexture = vec4(v,1);
}

