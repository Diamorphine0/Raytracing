#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normalCoord;

// we pass the vertex coordinates to the fragment shader
//and the normals
out vec2 uv0;
out vec3 normals;
out vec3 FragPos;

// we define the Transform uniform
uniform mat4 Transform;
uniform mat4 ModelMatrix;

void main(){
  //  Output position of the vertex, in clip space : MVP * position
  gl_Position = Transform * vec4(vertexPosition_modelspace, 1);
  uv0 = texCoord;
  normals = normalCoord;
  FragPos = vec3(ModelMatrix * vec4(vertexPosition_modelspace, 1));
}
