shader_type canvas_item;

uniform sampler2D perlin: source_color;
uniform vec4 sand_color: source_color = vec4(1.0);
uniform vec4 water_color_1: source_color = vec4(1.0);
uniform vec4 water_color_2: source_color = vec4(1.0);

void fragment() {
	int id = int(texture(TEXTURE, UV).r * 255.0);
	switch (id) {
		case 0:
			COLOR = vec4(0.0, 0.0, 0.0, 1.0); break;
		case 1:
			float rNoise = 0.2 * texture(perlin, UV).r;
			COLOR = sand_color - vec4(0., rNoise, 0., 0.) ; break;
		case 2:
			COLOR = vec4(0.7, 0.35, 0.15, 1.0); break;
		case 3:
			float x = (UV.x + UV.y + sin(UV.x / 16.0) * 2.0 + sin(TIME / 4.0));
			x = abs(x - 0.5);
			float y = (cos(sin(48.0 * UV.x) + PI * x * 2.0) + 1.0) / 2.0;
			
			vec2 texCoord = vec2(UV.x + sin(TIME / 16.0), UV.y + sin(TIME / 16.0));
			if (texCoord.x < 0.0)
				texCoord.x += 1.0;
			if (texCoord.y < 0.0)
				texCoord.y += 1.0;
			if (texCoord.x > 1.0)
				texCoord.x -= 1.0;
			if (texCoord.y > 1.0)
				texCoord.y -= 1.0;
			
			y = abs(y - 0.5);
			COLOR = water_color_1 * y + water_color_2 * (1.0 - y);
			COLOR += (sin(TIME * 1.5) + 1.0) / 3.0 * texture(perlin, texCoord);
			break;
	}
}
