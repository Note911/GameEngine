in vec3 fragmentPos;
in vec4 fragmentColor;
in vec2 fragmentUV;
in vec3 normalInterp;

const vec3 eyePosition = vec3(0.0,0.0,0.0);

uniform sampler2D posX;
uniform sampler2D negX;
uniform sampler2D posY;
uniform sampler2D negY;
uniform sampler2D posZ;
uniform sampler2D negZ;

out vec4 color;

void main(){
	vec3 normal = normalize(normalInterp);
	vec3 gazeDirection = normalize(eyePosition - fragmentPos);
	
	vec3 reflection = reflect(gazeDirection, normal);
	reflection = normalize(reflection);
	reflection += vec3(1,1,1);
	reflection /= 2.0;

	
	float max = reflection.x;

	if(abs(reflection.y) > abs(max))
		max = reflection.y;
	if(abs(reflection.z) > abs(max))
		max = reflection.z;

	vec4 textureColor = vec4(1,0,0,1);
	
	if(max == reflection.x){
		if(sign(max) == 1.0){
			textureColor = texture(posX, reflection.yz);
		}
		else{
			textureColor = texture(negX, reflection.yz);
		}			
	}
	else if(max == reflection.y){
		if(sign(max) == 1.0){
			textureColor = texture(posY, reflection.xz);
		}
		else{
			textureColor = texture(negY, reflection.xz);
		}			
	}
	else if(max == reflection.z){
		if(sign(max) == 1.0){
			textureColor = texture(posZ, reflection.xy);
		}
		else{
			textureColor = texture(negZ, reflection.xy);
		}			
	}

	color = textureColor;
	

}