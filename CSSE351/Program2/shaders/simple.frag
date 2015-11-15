#version 330

in vec4 smoothColor;
out vec4 fragColor;


void main()
{
    //TODO: make an animation
    //could use the vertex shader also
    
    fragColor = vec4(smoothColor.r, smoothColor.b, smoothColor.g, 1);
    //	if(smoothColor.r < 0.5)
    //		fragColor = vec4(1,1,1,1);
}
