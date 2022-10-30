shader_type canvas_item;

uniform sampler2D water_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D fire_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D marble_texture: repeat_enable, source_color, filter_nearest;
uniform sampler2D glass_texture: repeat_enable, source_color;
uniform sampler2D crystal_texture: repeat_enable, source_color;
uniform vec4 background_color: source_color = vec4(1.0);
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
uniform vec4 steel_color_1: source_color = vec4(1.0);
uniform vec4 steel_color_2: source_color = vec4(1.0);
uniform vec4 wood_color_1: source_color = vec4(1.0);
uniform vec4 acid_color_1: source_color = vec4(1.0);
uniform vec4 acid_color_2: source_color = vec4(1.0);
uniform vec4 acid_color_3: source_color = vec4(1.0);
uniform vec4 acid_gas_color_1: source_color = vec4(1.0);
uniform vec4 acid_gas_color_2: source_color = vec4(1.0);
uniform vec4 fairy_color_1: source_color = vec4(1.0);
uniform vec4 b_fire_color_1: source_color = vec4(1.0);
uniform vec4 b_fire_color_2: source_color = vec4(1.0);
uniform vec4 b_fire_color_3: source_color = vec4(1.0);
uniform vec4 laser_color_1: source_color = vec4(1.0);
uniform vec4 laser_color_2: source_color = vec4(1.0);
uniform vec4 air_color_1: source_color = vec4(1.0);
uniform vec4 air_color_2: source_color = vec4(1.0);
uniform vec4 crystal_color_1: source_color = vec4(1.0);
uniform vec4 crystal_color_2: source_color = vec4(1.0);
uniform vec4 black_hole_color_1: source_color = vec4(1.0);
uniform vec4 black_hole_color_2: source_color = vec4(1.0);
uniform vec4 oil_color_1: source_color = vec4(1.0);
uniform vec4 oil_color_2: source_color = vec4(1.0);
uniform vec4 oil_color_3: source_color = vec4(1.0);
uniform vec4 urchin_color_1: source_color = vec4(1.0);
uniform vec4 dragon_color_1: source_color = vec4(1.0);
uniform vec4 critter_color_1: source_color = vec4(1.0);
uniform vec4 uranium_color_1: source_color = vec4(1.0);
uniform vec4 nuclear_explosion_color_1: source_color = vec4(1.0);
uniform vec4 nuclear_explosion_color_2: source_color = vec4(1.0);

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
			COLOR = background_color; 
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
			COLOR = texture(marble_texture, SCREEN_UV * ratio);
			break;
		case 16:
			float x = match_amount(TEXTURE, UV, 16);
			COLOR = dust_color_1 * x + dust_color_2 * (1.0 - x);
			break;
		case 17:
			COLOR = UV.y * steel_color_2 + (1.0 - UV.y) * steel_color_1;
			break;
		case 18:
			COLOR = wood_color_1;
			break;
		case 19:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 128.0), 2.0*UV.y + sin(TIME / 128.0));
			
			float x = texture(water_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * UV.x + TIME / 64.0) * 16.0 * UV.x + PI * x + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = water_color_1 * y + 1.35 * water_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * UV.x + sin(TIME / 60.0), 1.5 * UV.y + sin(TIME / 60.0));
			
			COLOR = 1.8 * shift(cos(TIME / 32.0)) / 2.0 * texture(water_noise, ratio * texCoord2) + COLOR * z + water_color_3 * (1.0 - z);
			break;
		case 20:
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
		case 21:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 32.0), 2.0*UV.y + sin(TIME / 32.0));
			
			float x = texture(water_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * UV.x + TIME / 16.0) * 16.0 * UV.x + PI * x + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = acid_color_1 * y + acid_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * UV.x + sin(TIME / 24.0), 1.5 * UV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * texture(water_noise, ratio * texCoord2) + COLOR * z + acid_color_3 * (1.0 - z);
			break;
		case 22:
			float y = match_amount(TEXTURE, UV, 6);
			
			COLOR = acid_gas_color_2 * y + acid_gas_color_1 * (1.0 - y);
			break;
		case 23:
			COLOR = fairy_color_1;
			break;
		case 24:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 32.0), 2.0*UV.y + sin(TIME / 32.0));
			
			float x = texture(fire_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * UV.x + TIME / 16.0) * 16.0 * UV.x + PI * x * 2.0 + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = b_fire_color_1 * y + b_fire_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(2.0 * UV.x + sin(TIME / 24.0), 2.0 * UV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) * texture(fire_noise, ratio * texCoord2) + COLOR * z + b_fire_color_3 * (1.0 - z);
			break;
		case 25:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			float dif = 1.0 - abs(SCREEN_UV.x + SCREEN_UV.y - abs(sin(TIME / 4.0)));
			if (dif < 0.0)
				dif = 0.0;
			COLOR = 0.5 * vec4(texture(glass_texture, vec2(cos(TIME / 64.0), sin(TIME / 64.0)) + SCREEN_UV * ratio).a * dif);
			COLOR += 0.5 * vec4(texture(glass_texture, vec2(cos(TIME / 48.0), sin(TIME / 48.0)) + SCREEN_UV * ratio).a * (1.0 - dif));
			COLOR += vec4((sin(TIME / 42.0) + 1.0) / 8.0);
			COLOR.a = 1.0;
			
			break;
		case 26:
			float y = match_amount(TEXTURE, UV, 26);
			
			COLOR = laser_color_2 * y + laser_color_1 * (1.0 - y);
			break;
		case 27:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec4 col = texture(crystal_texture, SCREEN_UV * ratio);
			float x = (col.r + col.g + col.b) / 3.0;
			x = shift(sin(x)) * shift(sin(TIME / 3.0));
			COLOR = crystal_color_1 * x + crystal_color_2 * (1.0 - x);
			vec2 texCoord2 = vec2(1.5 * SCREEN_UV.x + sin(TIME / 24.0), 1.5 * SCREEN_UV.y + sin(TIME / 24.0));
			
			COLOR += x * shift(cos(TIME / 4.0)) * texture(water_noise, ratio * texCoord2);
			break;
		case 28:
			float y = match_amount(TEXTURE, UV, 28);
			
			COLOR = air_color_2 * y + air_color_1 * (1.0 - y);
			break;
		case 29:
			float y = match_amount(TEXTURE, UV, 29);
			
			COLOR = black_hole_color_2 * y + black_hole_color_1 * (1.0 - y);
			break;
		case 30:
			vec2 ps = SCREEN_PIXEL_SIZE;
			vec2 ratio = (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
			vec2 texCoord = vec2(2.0*UV.x + sin(TIME / 32.0), 2.0*UV.y + sin(TIME / 32.0));
			
			float x = texture(water_noise, ratio * texCoord).r * (UV.x + UV.y + sin(UV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * UV.x + TIME / 16.0) * 16.0 * UV.x + PI * x + UV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = oil_color_1 * y + oil_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * UV.x + sin(TIME / 24.0), 1.5 * UV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * texture(water_noise, ratio * texCoord2) + COLOR * z + oil_color_3 * (1.0 - z);
			break;
		case 31:
			COLOR = urchin_color_1;
			break;
		case 32:
			COLOR = dragon_color_1;
			break;
		case 33:
			COLOR = critter_color_1;
			break;
		case 34:
			float x = match_amount(TEXTURE, UV, 34);
			COLOR = nuclear_explosion_color_1 * x + nuclear_explosion_color_2 * (1.0 - x);
			break;
		case 35:
			COLOR = uranium_color_1;
			break;
	}
}
