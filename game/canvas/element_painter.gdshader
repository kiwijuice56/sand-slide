shader_type canvas_item;

uniform sampler2D water_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D fire_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D marble_texture: repeat_enable, source_color, filter_nearest;
uniform vec4 rock_color_1: source_color = vec4(1.0);
uniform vec4 sand_color_1: source_color = vec4(1.0);
uniform vec4 water_color_1: source_color = vec4(1.0);
uniform vec4 water_color_2: source_color = vec4(1.0);
uniform vec4 water_color_3: source_color = vec4(1.0);
uniform vec4 polliwog_color_1: source_color = vec4(1.0);
uniform vec4 fire_color_1: source_color = vec4(1.0);
uniform vec4 fire_color_2: source_color = vec4(1.0);
uniform vec4 fire_color_3: source_color = vec4(1.0);
uniform vec4 smoke_color_1: source_color = vec4(1.0);
uniform vec4 smoke_color_2: source_color = vec4(1.0);
uniform vec4 algae_color_1: source_color = vec4(1.0);
uniform vec4 sand_duck_color_1: source_color = vec4(1.0);
uniform vec4 lead_azide_color_1: source_color = vec4(1.0);
uniform vec4 explosion_color_1: source_color = vec4(1.0);
uniform vec4 explosion_color_2: source_color = vec4(1.0);
uniform vec4 soil_color: source_color = vec4(1.0);
uniform vec4 grass_color_1: source_color = vec4(1.0);
uniform vec4 seed_color_1: source_color = vec4(1.0);
uniform vec4 seed_color_2: source_color = vec4(1.0);
uniform vec4 dust_color_1: source_color = vec4(1.0);
uniform vec4 dust_color_2: source_color = vec4(1.0);

float remainder(float x) {
	if (abs(x) > 1.0) 
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
			if (id == given_id) {
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
			COLOR = vec4(0.0, 0.0, 0.0, 1.0); 
			break;
		case 1:
			COLOR = sand_color_1;
			break;
		case 2:
			COLOR = rock_color_1;
			break;
		case 3:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 32.0), 2.0*UV.y + sin(TIME / 32.0));
			
			float x = texture(water_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * UV.x + TIME / 16.0) * 16.0 * UV.x + PI * x + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = water_color_1 * y + water_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * UV.x + sin(TIME / 24.0), 1.5 * UV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * texture(water_noise, ratio * texCoord2) + COLOR * z + water_color_3 * (1.0 - z);
			break;
		case 4:
			COLOR = polliwog_color_1;
			break;
		case 5:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 32.0), 2.0*UV.y + sin(TIME / 32.0));
			
			float x = texture(fire_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * UV.x + TIME / 16.0) * 16.0 * UV.x + PI * x * 2.0 + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = fire_color_1 * y + fire_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(2.0 * UV.x + sin(TIME / 24.0), 2.0 * UV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) * texture(fire_noise, ratio * texCoord2) + COLOR * z + fire_color_3 * (1.0 - z);
			break;
		case 6:
			float y = match_amount(TEXTURE, UV, 6);
			
			COLOR = smoke_color_1 * y + smoke_color_2 * (1.0 - y);
			break;
		case 7:
			COLOR = algae_color_1;
			break;
		case 8:
			COLOR = sand_duck_color_1;
			break;
		case 9:
			float x = match_amount(TEXTURE, UV, 9);
			COLOR = explosion_color_1 * x + explosion_color_2 * (1.0 - x);
			break;
		case 10:
			COLOR = lead_azide_color_1;
			break;
		case 11:
			COLOR = soil_color;
			break;
		case 12:
			COLOR = seed_color_1;
			break;
		case 13:
			COLOR = seed_color_2;
			break;
		case 14:
			COLOR = grass_color_1;
			break;
		case 15:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			COLOR = texture(marble_texture, UV * ratio);
			break;
		case 16:
			float x = match_amount(TEXTURE, UV, 16);
			COLOR = dust_color_1 * x + dust_color_2 * (1.0 - x);
			break;
	}
}
