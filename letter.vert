#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTex; //Koordinate texture, propustamo ih u FS kao boje

uniform mat4 uM; //Matrica transformacije
uniform mat4 uP; //Matrica projekcija

out vec2 TexCoord;

void main()
{
	gl_Position = uP * uM * vec4(inPos, 1.0); //Zbog nekomutativnosti mnozenja matrica, moramo mnoziti MVP matrice i tjemena "unazad"
	TexCoord = inTex;


}