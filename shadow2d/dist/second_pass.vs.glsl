varying vec3 vPos;

varying vec2 texCoord;

void main(void)
{
	texCoord = gl_MultiTexCoord0.xy;
	gl_Position = ftransform();
	vPos = gl_Position;
	gl_FrontColor = gl_Color;
}