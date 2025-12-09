#version 450 

//cpu로부터 받은 속성 0번의 입력을 vec4로 받음
layout(location = 0) in vec3 coord3d;
layout(location=1) in vec3 normal;


uniform mat4 model;
uniform mat4 view; 
uniform mat4 projection; 

out vec3 fColor;

void main(void)
{

	gl_Position = (projection * (view * (model * vec4( coord3d,1.0))));
	fColor = (normal + vec3(1.0, 1.0, 1.0)) * 0.5;

}
