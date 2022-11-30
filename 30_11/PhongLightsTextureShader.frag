#version 450

#define MAX_LIGHTS 3
struct Light {
    vec3 position, direction, color_of_light;
    float cutOff, outer_cutOff;
    int type;
    float constant, linear, quadratic;
};

in vec4 worldPos;
in vec3 worldNorm;
in vec2 uvc;
out vec4 frag_color;

uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPosition;
uniform sampler2D textureUnitID;


vec4 calculatePointLight(Light light,  vec3 viewVector)
{
	vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specular = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	vec3 lightVector = normalize(light.position - worldPos.xyz / worldPos.w);

	float distance = length(light.position - worldPos.xyz / worldPos.w);
	float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.01 * (distance * distance) );

	float diff = max(dot(lightVector, worldNorm), 0.0);	
	diffuse = diff * texture(textureUnitID, uvc);
	
	float shininess = 0.8;
	if(dot(lightVector, worldNorm) > 0)
	{
		float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);
		specular = shininess * spec * vec4(0.385, 0.647, 0.812, 1.0);	
	}

    diffuse  *= attenuation;
    specular *= attenuation;

	return (diffuse + specular);
}

vec4 calculateDirectionalLight(Light light,  vec3 viewVector)
{	
	vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specular = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	vec3 lightVector = normalize(-light.direction);

	float diff = max(dot(lightVector, worldNorm), 0.0);
	diffuse = diff * texture(textureUnitID, uvc) * vec4(light.color_of_light, 1.0);

	float shininess = 0.8;
	if(dot(lightVector, worldNorm) > 0)
	{
		float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);
		specular = shininess * spec * vec4(light.color_of_light, 1.0);	
	}

	return (diffuse + specular);
}

vec4 calculateSpotLight(Light light, vec3 viewVector)
{	
	vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specular = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	vec3 lightVector = normalize(light.position - worldPos.xyz / worldPos.w);

	float theta = dot(lightVector, normalize(-light.direction));
	float epsilon = light.cutOff - light.outer_cutOff;
	float intensity = clamp((theta - light.outer_cutOff) / epsilon, 0.0, 1.0);

	float distance = length(light.position - worldPos.xyz / worldPos.w);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance) );

	float diff = max(dot(lightVector, worldNorm), 0.0);
	diffuse = diff * texture(textureUnitID, uvc) * attenuation;
		
	float shininess = 0.8;
	float spec = pow(max(dot(viewVector, reflect(-lightVector, worldNorm)), 0.0), 40);
	specular = shininess * spec * vec4(0.385, 0.647, 0.812, 1.0);	

	diffuse *= intensity;
	specular *= intensity;

	return (diffuse + specular);
}

void main() {
    vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	vec3 viewVector = normalize(viewPosition - worldPos.xyz / worldPos.w);
   
   for(int i = 0 ; i < MAX_LIGHTS; i++)
	{		
		if(lights[i].type == 1)
		{
			result += calculatePointLight(lights[i], viewVector);
		}
		else if(lights[i].type == 2)
		{
			result += calculateDirectionalLight(lights[i], viewVector);
		}
		else if(lights[i].type == 3)
		{
			result += calculateSpotLight(lights[i], viewVector);
		}
	}

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	frag_color = ambient + result;
}