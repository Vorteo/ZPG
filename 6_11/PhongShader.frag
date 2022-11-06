#version 330

in vec4 worldPos;
in vec3 worldNorm;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 frag_color;

void main () {	
	// Light vector
	vec3 lightVector = normalize(lightPosition - vec3(worldPos));
	// View Vector
	vec3 viewVector = normalize(viewPosition - vec3(worldPos));

	// Diffuse
	float d = dot(lightVector, worldNorm);
	float dot_product = max(d, 0.0);
	vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);	

	// Specular	
	float shininess= 0.8;
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	
	// check dot 
	if(d > 0.0)
	{
		float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);
		specular = shininess * spec * vec4( 0.385, 0.647, 0.812, 1.0);
	}

	// Ambient
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

	frag_color = ambient + diffuse + specular;

}