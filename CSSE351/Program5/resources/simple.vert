#version 330

uniform mat4 P;     // projection matrix
uniform mat4 C;     // camera Matrix
uniform mat4 mT;    // model Transform
uniform mat4 mR;    // model Rotation
uniform mat4 M;     // modelview matrix: M = C * mR * mT
uniform mat4 N;     // inverseTranspose - Normal matrix  // nverse transpose of M
uniform mat4 L;     // light rotation matrix
uniform vec4 lightPos;  // lightPosition
uniform vec4 camPos;    // cameraPosition
uniform int shadingMode;       // mode

// attribution
in vec3 pos;        // position slot
in vec3 colorIn;    // color slot

//vec4 view;
//vec4 light;

smooth out vec4 smoothColor;
out vec3 viewDir;
out vec3 vectorToLight;
out vec3 normal;


vec4 justColor()
{
    return vec4(vec3(colorIn), 1.0);
}

vec4 gouraud()
{
    vec4 ambientColor = vec4(colorIn, 1) * 0.1;
    
    vec4 newLightPos = P * C * L * lightPos;
    vec3 newPos = (P * M * vec4(pos, 1)).xyz;
    
    vec3 viewDir = normalize((P * camPos).xyz - newPos);
    vec3 vectorToLight = normalize(newLightPos.xyz - newPos);
    
    normal = normalize(vec3(P * N * vec4(colorIn * 2 - vec3(1.0f), 1.0))); // colorIn * 2 - vec3(1.0f) == vertex normal
    
    float diffuse = max(dot(normal, vectorToLight), 0);
    vec3 reflection = normalize(reflect(-vectorToLight, normal));
    vec3 specular = vec3(1) * pow(max(dot(reflection, viewDir), 0.0), 10.0);
    
    vec4 returnColor = vec4(
                            ambientColor.xyz
                            + diffuse * colorIn
                            + specular, 1
                            );
    return returnColor;
//    return abs(vec4(1) - vec4(colorIn, 1));
}

vec4 phong()
{
    vec4 norm = vec4(normal, 0);
    
    
    vec4 newLightPos = P * C * L * lightPos;
    vec3 newPos = (P * M * vec4(pos, 1)).xyz;
    
    viewDir = normalize((P * camPos).xyz - newPos);
    vectorToLight = normalize(newLightPos.xyz - newPos);
    
    normal = normalize(vec3(P * N * vec4(colorIn * 2 - vec3(1.0f), 1.0))); // colorIn * 2 - vec3(1.0f) == vertex normal
    
    return vec4(colorIn, 1);
}

void main()
{
    
	vec4 pos = vec4(pos, 1);
    
    normal = normalize(vec3(P * N * vec4(colorIn * 2 - vec3(1.0f), 1.0))); // colorIn * 2 - vec3(1.0f) == vertex normal
//    light = normalize(lightPos * L - pos);
//    view = normalize(-(vec4(pos)));
    
	gl_Position = P*M*pos;
    
    if(shadingMode == 0)
        smoothColor = justColor();
    else if (shadingMode == 1)
        smoothColor = gouraud();
    else
        smoothColor = phong();
}
