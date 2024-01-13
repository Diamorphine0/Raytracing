#version 330 core
out vec4 color;
in vec2 uv0;

uniform sampler2D u_Texture;

void main(){
  color = texture(u_Texture, uv0);
}
