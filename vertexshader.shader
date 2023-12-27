#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 Transform;

void main(){
  // Output position of the vertex, in clip space : MVP * position
  gl_Position = Transform * vec4(vertexPosition_modelspace,1);
  fragmentColor = vertexColor;
}
