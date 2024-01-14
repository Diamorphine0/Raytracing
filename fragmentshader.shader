#version 330 core
out vec4 color;
in vec2 uv0;
in vec3 normals;
in vec3 FragPos;

uniform sampler2D u_Texture;
uniform vec3 ambientColor = vec3(0.0, 0.0, 0.0); //default light green
uniform vec3 lightColor = vec3(0.0, 1.0, 0.0);
uniform vec3 lightPos = vec3(1.0, 0.0, -1.0); //this will later be passed

void main(){
        vec4 textureColor = texture(u_Texture, uv0);

        //normalise the normals
        vec3 norm = normalize(normals);

        //calculate the direction of the light
        vec3 lightDir = normalize(lightPos - FragPos);

        //diffuse strength
        float diff = max(dot(norm, lightDir), 0.0);

        //apply to light
        vec3 diffuse = diff * lightColor;

        //lightning result
        vec3 result = (ambientColor + diffuse) * textureColor.rgb;
        color = vec4(result, textureColor.a);
}
