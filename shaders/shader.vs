
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 clr;
layout(location = 2) in vec2 offset;

uniform mat4 transform;
out vec3 fClr;

void main(){
	fClr = clr;
	gl_Position =  transform*vec4(pos+offset, 0.0, 1.0);
}
