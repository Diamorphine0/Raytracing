#version 330

in vec2 uv0;

out vec4 FragColor;

uniform sampler2D gSampler;

void main(){
	FragColor = texture2D(gSampler, uv);
}
