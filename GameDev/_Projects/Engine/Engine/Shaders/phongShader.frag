
in vec3 fragmentPos;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec3 normalInterp;

const vec3 lightPosition = vec3(0.0,0.0,-2.0);
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
const vec3 specularColor = vec3(0.0, 1.0, 0.0);
const float shininessCoeffitient = 96.0;
const float screenGamma = 2.2;

uniform sampler2D mySampler;

out vec4 color;

void main(){

	vec4 textureColor = texture(mySampler, fragmentUV);
	vec3 normal = normalize(normalInterp);
	vec3 lightDirection = normalize(lightPosition - fragmentPos);
	float lambertian = max(dot(lightDirection, normal), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0){
		vec3 viewDirection = normalize(-fragmentPos);
		vec3 halfDirection = normalize(lightDirection + viewDirection);
		float specularAngle = max(dot(halfDirection, normal), 0.0);
		specular = pow(specularAngle, shininessCoeffitient);
	}
	vec3 colorLinear = ambientColor + lambertian * diffuseColor + specular * specularColor;
	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));
	color = vec4(colorGammaCorrected, 1.0) * textureColor * fragmentColor;
}