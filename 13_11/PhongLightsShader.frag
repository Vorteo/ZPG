#version 450

#define MAX_LIGHTS 3

struct Light {
	vec3 position, direction;
	float cutOff;
	int type;

	float constant, linear, quadratic;
};

uniform Light lights[MAX_LIGHTS];

in vec4 worldPos;
in vec3 worldNorm;

uniform vec3 viewPosition;

out vec4 frag_color;

vec4 calculatePointLight(Light light)
{
	vec3 lightVector = normalize(light.position - worldPos.xyz / worldPos.w);

	float dist = length(light.position - worldPos.xyz / worldPos.w);
	float attenuation = 1.0 / (1.0 + 0.1 * dist + 0.01 * (dist * dist) );

	float dot_product = max(dot(worldNorm, lightVector), 0.0);

	float s = 0.8;
	vec3 viewVector = normalize(viewPosition - worldPos.xyz / worldPos.w);
	float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);
	
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
	vec4 specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

    diffuse  *= attenuation;
    specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec4 calculateDirectionalLight(Light light)
{
	vec3 lightVector = normalize(-light.direction);
	float dot_product = max(dot(worldNorm, lightVector), 0.0);

	float s = 0.8;
	vec3 viewVector = normalize(viewPosition - worldPos.xyz / worldPos.w);
	float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);

	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
	vec4 specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);

	return (diffuse + specular);
}

vec4 calculateSpotLight(Light light)
{
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 lightVector = normalize(light.position - worldPos.xyz / worldPos.w);

	float theta = dot(lightVector, normalize(-light.direction));

	if(theta > light.cutOff)
	{	
		float dist = length(light.position - worldPos.xyz / worldPos.w);
		float attenuation = 1.0 / (1.0 + 0.1 * dist + 0.01 * (dist * dist) );

		float dot_product = max(dot(worldNorm, lightVector), 0.0);

		float s = 0.8;
		vec3 viewVector = normalize(viewPosition - worldPos.xyz / worldPos.w);
		float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);

		diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0) * attenuation;
		specular = s * spec * vec4(0.385, 0.647, 0.812, 1.0);
	}

	return (diffuse + specular);
}

void main () {

	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec4 result;

	for(int i = 0 ; i < MAX_LIGHTS; i++)
	{
		if(lights[i].type == 1)
		{
			result += calculatePointLight(lights[i]);
		}
		else if(lights[i].type == 2)
		{
			result += calculateDirectionalLight(lights[i]);
		}
		else if(lights[i].type == 3)
		{
			result += calculateSpotLight(lights[i]);
		}
	}

	frag_color = ambient + result;
}