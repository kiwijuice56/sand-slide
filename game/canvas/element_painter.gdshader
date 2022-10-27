shader_type canvas_item;

uniform sampler2D sand_noise: source_color, filter_nearest;
uniform sampler2D rock_noise: source_color, filter_nearest;
uniform sampler2D water_noise: source_color, filter_nearest;
uniform vec4 rock_color_1: source_color = vec4(1.0);
uniform vec4 rock_color_2: source_color = vec4(1.0);
uniform vec4 sand_color_1: source_color = vec4(1.0);
uniform vec4 sand_color_2: source_color = vec4(1.0);
uniform vec4 water_color_1: source_color = vec4(1.0);
uniform vec4 water_color_2: source_color = vec4(1.0);
uniform vec4 water_color_3: source_color = vec4(1.0);

float remainder(float x) {
	x = abs(x);
	if (x > 1.0) 
		return x - floor(x);
	return x;
}

float shift(float x) {
	return (x + 1.0) / 2.0;
}

float match_amount(sampler2D tex, vec2 uv, int given_id) {
	vec2 pixel_size = 1.0 / vec2(textureSize(tex, 0));
	int matching = 0;
    for(int y = -1; y <= 1; y++) {
		for(int x = -1; x <= 1; x++) {
			if (x == 0 && y == 0)
				continue;
			vec2 pixel_off = vec2(float(x), float(y));
			int id = int(texture(tex, uv + pixel_off * pixel_size).r * 255.0);
			if(id == given_id) {
				matching++;
			}
		}
	}
	return float(matching) / 8.0;
}

void fragment() {
	int id = int(texture(TEXTURE, UV).r * 255.0);
	switch (id) {
		case 0:
			COLOR = vec4(0.0, 0.0, 0.0, 1.0); break;
		case 1:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			float x = 0.5;//texture(sand_noise, UV * ratio).r;
			COLOR = sand_color_1 * x + sand_color_2 * (1.0 - x);
			break;
		case 2:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			float x = 1.0;// 0.6 * texture(rock_noise, UV * ratio).r;
			COLOR = rock_color_1 * x + rock_color_2 * (1.0 - x);
			break;
		case 3:
			vec2 texCoord = vec2(remainder(UV.x + sin(TIME / 16.0)), remainder(UV.y + sin(TIME / 16.0)));
			
			float x = texture(water_noise, texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 4.0));
			
			
			float y = shift(cos(sin(3.0 * UV.x + TIME / 8.0) * 16.0 * UV.x + PI * x * 2.0 + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = water_color_1 * y + water_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(remainder(UV.x + sin(TIME / 9.0)), remainder(UV.y + sin(TIME / 12.0)));
			
			COLOR = texture(water_noise, texCoord2) + COLOR * z + water_color_3 * (1.0 - z);
			break;
	}
}
