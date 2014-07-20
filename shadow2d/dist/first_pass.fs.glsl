struct light_t
{
	bool enabled;
	vec3 light_pos;
	vec3 light_col;
};

struct shading_attributes_t
{
	vec3 col;

	int light_count;
	light_t lights[10];
};

uniform shading_attributes_t shading_attributes;

varying vec3 vPos;

void main(void)  
{
	const float a = 1;
	const float b = 1;
	
	const vec2 light_pos = vec2(0.0f, 0.0f);
	
	float dist = length(light_pos + vec2(vPos));
	
	float att = 1.0f / (1.0f + a * dist + b * dist * dist);

	gl_FragColor = vec4(att, 0.0f, 0.0f, 1.0f);
}