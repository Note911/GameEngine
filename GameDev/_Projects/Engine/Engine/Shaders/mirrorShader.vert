in vec3 vertexPos;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 inputNormal;

uniform mat4 projection, modelview, normalMat;

out vec3 fragmentPos;
out vec4 fragmentColor;
out vec2 fragmentUV;
out vec3 normalInterp;

void main(){

	gl_Position = projection * modelview * vec4(vertexPos, 1.0);
	vec4 vertPos = modelview * vec4(vertexPos, 1.0);
	vec3 vertexPosition = vec3(vertPos.x, vertPos.y, vertPos.z);

	fragmentPos = vertexPosition;
	fragmentColor = vertexColor;
	fragmentUV = vertexUV;
	normalInterp = vec3(normalMat * vec4(inputNormal, 0.0));
}