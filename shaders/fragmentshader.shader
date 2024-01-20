#version 330 core
out vec4 color;
in vec2 uv0;
in vec3 normals;
in vec3 FragPos;
in vec3 viewPos0;

uniform sampler2D u_Texture;
uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0); //default light green

struct Light {
    vec3 lightColor;
    vec3 lightPos;
};

const int MAX_LIGHTS = 20;
uniform Light lights[MAX_LIGHTS];

void main(){
        vec4 textureColor = texture(u_Texture, uv0);
        vec3 result = ambientColor * textureColor.rgb;

        //normalise the normals
        vec3 norm = normalize(normals);

        for (int i = 0; i < MAX_LIGHTS; ++i) {
               // Calculate the direction of the light
               vec3 lightDir = normalize(lights[i].lightPos - FragPos);

               // Diffuse strength
               float diff = max(dot(norm, lightDir), 0.0);

               // Apply to light
               vec3 diffuse = diff * lights[i].lightColor;

               // Specular
               float specularStrength = 0.5;
               vec3 viewDir = normalize(viewPos0 - FragPos);
               vec3 reflectDir = reflect(-lightDir, norm);

               float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
               vec3 specular = specularStrength * spec * lights[i].lightColor;

               // Lighting result
               result += (diffuse + specular) * textureColor.rgb;
           }

         color = vec4(result, textureColor.a);
}
