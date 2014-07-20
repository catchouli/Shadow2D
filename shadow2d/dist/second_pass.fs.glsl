#version 120

uniform sampler2D colour_tex;
uniform sampler2D depth_tex;

uniform vec2 light_pos = vec2(-0.5f, 0.0f);

varying vec3 vPos;

varying vec2 texCoord;

bool raycast(vec2 start, vec2 end);

uniform vec2 screen_dimensions;

uniform vec2 step_scale = vec2(1.0f, 1.0f);

void main(void)  
{
	const float zNear = 0.0;
	const float zFar = 1.0;

	const float a = 1;
	const float b = 1;
	
	float dist = length(light_pos + vec2(vPos));
	
	float att = 1.0f / (1.0f + a * dist + b * dist * dist);
	
    float z_b = texture2D(depth_tex, texCoord).x;
    float z_n = 2.0 * z_b - 1.0;
	float z_e = 2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear));

	gl_FragColor = vec4(0.0);

	if (z_b == 1.0)
	{
		float endx = 1.0f - (light_pos.x * 0.5f + 0.5f);
		float endy = 1.0f - (light_pos.y * 0.5f + 0.5f);

		if (!raycast(texCoord, vec2(endx, endy)))
			gl_FragColor.r = att;

		//gl_FragColor.x = endx;
		//gl_FragColor.y = endy;
		//gl_FragColor.z = 0.0;
	}
	else
	{
		gl_FragColor = vec4(1.0);
	}
}

bool raycast(vec2 start, vec2 end)
{
	if (texture2D(depth_tex, start) != 1.0)
	{
		return true;
	}

	vec2 diff = end - start;

	float magnitude = length(diff);

	vec2 d = diff / magnitude;

	if (abs(d.x) < 0.0001f)
		d.x = 0.0001f;
	if (abs(d.y) < 0.0001f)
		d.y = 0.0001f;

	vec2 d_coeff = (1.0f / d);
	vec2 d_bias = -(start / d);

	vec2 step = step_scale * (1.0f / screen_dimensions) * vec2(d.x > 0 ? 1.0f : -1.0f, d.y > 0 ? 1.0f : -1.0f);

	float t = 0;

	vec2 cur = start;

	while (t < magnitude)
	{
		vec2 next = cur + step;
		vec2 t_next = next * d_coeff + d_bias;

		if (t_next.x < t_next.y)
		{
			t = t_next.x;
			cur.x = next.x;
		}
		else
		{
			t = t_next.y;
			cur.y = next.y;
		}

		if (texture2D(depth_tex, cur) != 1.0)
		{
			return true;
		}
	}

	return false;
}