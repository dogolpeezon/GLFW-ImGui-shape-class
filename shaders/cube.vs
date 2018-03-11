#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 clr;
layout(location = 2) in vec3 nrm;
layout(location = 3) in vec3 tex;

uniform mat4 model, view, projection;
uniform float time;
//in vec3 pos;
//in vec4 clr;

out vec4 fClr;

void main(){
	fClr = clr;
	vec3 new_pos = pos*(1.0+0.25*sin(pos.x+pos.y+pos.z+5.0*time));
	gl_Position =  projection * view * model * vec4(new_pos, 1.0f);
}
