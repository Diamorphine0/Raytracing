#version 330 core
out vec4 color;
in vec4 texColor;
in vec3 fragmentColor;
//in vec2 v_TexCoord;

void main(){
  // the problem occurs when passing the texColor
  color = texColor;
}
