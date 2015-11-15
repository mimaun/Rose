#version 330

//TODO: receive a uniform value
uniform float timeVal;
uniform int mousexVal;

in vec2 pos;
in vec3 color;
in vec2 size;

out vec4 smoothColor;


void main()
{
    gl_Position = vec4(pos.x + sin(timeVal*2), pos.y + sin(timeVal), 0, 1);
    smoothColor = vec4(color, 1);
    
    //TODO: make an animation!
    //could use the frag shader also
    //	smoothColor = vec4(color.r * (0.5*sin(mousexVal/510) + 0.5),
    //					   color.g * (0.5*sin(mousexVal*2/510) + 0.5),
    //					   color.b * (0.5*sin(mousexVal*3.14159/510) + 0.5)
    //					   , 1);
    smoothColor = vec4(color.r,color.g + mousexVal*0.00051,color.b, 1);
}
