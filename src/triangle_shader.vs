#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor; // specify a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 transform;

void main() {
   gl_Position = transform * vec4(aPos, 1.0);
   ourColor = aColor; // set output variable to a dark red color
   TexCoord = aTexCoord;
}