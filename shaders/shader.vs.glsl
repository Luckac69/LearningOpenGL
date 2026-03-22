#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // color at vertex
layout (location = 2) in vec2 aTexCoord;
  
out vec3 ourColor; // output color to fragment shader
out vec2 TexCoord;

uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos.xy + offset, aPos.z, 1.0); // see how we directly give a vec3 to vec4's constructor
    ourColor = aColor;
    TexCoord = aTexCoord;
}
