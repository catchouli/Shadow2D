varying vec3 vPos;

void main(void)
{
	gl_Position = ftransform();
	vPos = gl_Position;
	gl_FrontColor = gl_Color;
}