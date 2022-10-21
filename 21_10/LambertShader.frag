#version 330
in vec3 worldPos;
in vec3 worldNorm;

uniform vec3 lightPosition;

out vec4 outColor;

void main() {
    // Ambient
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    // Light vector
    vec3 lightVector = normalize(lightPosition - worldPos);

    // Diffuse
    float dot_product = max(dot(lightVector, normalize(worldNorm)), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);

    outColor = ambient + diffuse;
}