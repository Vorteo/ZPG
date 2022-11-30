#version 450
in vec4 worldPos;
in vec3 worldNorm;

uniform vec3 lightPosition;

out vec4 frag_color;

void main() {
    // Light vector
    vec3 lightVector = normalize((lightPosition - worldPos.xyz / worldPos.w));

    // Diffuse
    float dot_product = max(dot(lightVector, worldNorm), 0.0);
    vec4 diffuse = dot_product * vec4( 0.07, 0.48, 0.22, 1.0);
     // Ambient
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    frag_color = ambient + diffuse;
}