
#version 330 core
out vec4 FragColor;
in vec3 fClr;
void main(){
	FragColor = vec4(fClr, 1.0);
}
