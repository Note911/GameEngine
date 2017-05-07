#version 130

in vec3 vertexPos;
in vec4 vertexColor;
in vec2 vertexUV;
in vec3 inputNormal;

uniform mat4 projection, modelview, normalMat;

out vec3 fragmentPos;
out vec4 fragmentColor;
out vec2 fragmentUV;


void main() {
	gl_Position = projection  * modelview * vec4(vertexPos, 1.0);

	fragmentColor = vertexColor;

	fragmentPos = vertexPos;

	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}