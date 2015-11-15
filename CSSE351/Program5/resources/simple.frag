#version 330

uniform mat4 P;
uniform mat4 C;
uniform mat4 mT;
uniform mat4 mR;
uniform mat4 L;
uniform vec4 lightPos;
uniform vec4 camPos;
uniform int shadingMode;

smooth in vec4 smoothColor;
in vec3 viewDir;
in vec3 vectorToLight;
in vec3 normal;

out vec4 fragColor;

void main()
{

    //TODO add gouraud and phong shading support
    
    if(shadingMode == 0)
        fragColor = smoothColor;
    
    else if (shadingMode == 1)
        fragColor = smoothColor;
    
    else {
        
        vec4 ambientColor = vec4(smoothColor) * 0.1;
        float diffuse = max(dot(normal, vectorToLight), 0);
        vec3 reflection = normalize(-reflect(vectorToLight, normal));
        vec3 specular = vec3(1) * pow(max(dot(reflection, viewDir), 0.0), 10.0);
        
        fragColor = vec4(ambientColor.xyz
                                + diffuse * smoothColor.rgb
                                + specular, 1);
        
    }
}
