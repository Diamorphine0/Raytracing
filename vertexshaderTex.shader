#version 330 core

layout(location = 0) in vec3 coordinates;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec3 colors;

uniform mat4 Transform;

out vec2 uv0;

void main(){
	gl_Position = Transform * vec4(coordinates, 1.0);
	uv0 = uv;
}
