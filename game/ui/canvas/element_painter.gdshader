shader_type canvas_item;

// Each element defines its uniforms for colors, textures, etc. and uses them to 
// render itself. The parameters can be configured at canvas/element_painter.tres

// This code is not optimal or modular, but convenient to quickly add elements

uniform int width = 1000;
uniform int height = 800;
uniform int px_scale = 4;

// Noise and other textures for elements that are not simple colors
uniform sampler2D water_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D fire_noise: repeat_enable, source_color, filter_nearest;
uniform sampler2D marble_texture: repeat_enable, source_color, filter_nearest;
uniform sampler2D glass_texture: repeat_enable, source_color, filter_nearest;
uniform sampler2D crystal_texture: repeat_enable, source_color, filter_nearest;
uniform sampler2D sky_texture: repeat_enable, filter_nearest;

uniform vec4 rock_color_1: source_color = vec4(1.0);
uniform vec4 sand_color_1: source_color = vec4(1.0);

// Elements can define multiple uniform colors that can be interpolated based on
// position, time, etc.
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
uniform vec4 lead_azide_color_2: source_color = vec4(1.0);

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
uniform vec4 uranium_color_2: source_color = vec4(1.0);

uniform vec4 nuclear_explosion_color_1: source_color = vec4(1.0);
uniform vec4 nuclear_explosion_color_2: source_color = vec4(1.0);

uniform vec4 neutron_color_1: source_color = vec4(1.0);
uniform vec4 neutron_color_2: source_color = vec4(1.0);

uniform vec4 lightning_color_1: source_color = vec4(1.0);

uniform vec4 plasma_color_1: source_color = vec4(1.0);
uniform vec4 plasma_color_2: source_color = vec4(1.0);

uniform vec4 electron_color_1: source_color = vec4(1.0);
uniform vec4 electron_color_2: source_color = vec4(1.0);

uniform vec4 storm_plasma_color_1: source_color = vec4(1.0);
uniform vec4 storm_plasma_color_2: source_color = vec4(1.0);

uniform vec4 hurricane_color_1: source_color = vec4(1.0);
uniform vec4 hurricane_color_2: source_color = vec4(1.0);

uniform vec4 powder_color_2: source_color = vec4(1.0);
uniform vec4 powder_color_3: source_color = vec4(1.0);

// Short hand of shifting the range [-1, 1] to [0, 1] since the negative return 
// values of sin/cos can cause errors
float shift(float x) {
	return (x + 1.0) / 2.0;
}

// Returns a value [0, 1] of the saturation of cells given_id arround the pixel
// at uv. Returns 0 when no cells of given_id are touching the 
// pixel and 1 when all 8 surrounding cells are of type given_id
float match_amount(sampler2D tex, vec2 uv, int given_id) {
	vec2 pixel_size = 1.0 / vec2(textureSize(tex, 0));
	int matching = 0;
    for(int y = -1; y <= 1; y++) {
		for(int x = -1; x <= 1; x++) {
			// Don't check the current cell
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

// Take the average of a certain point in a texture for
// softer images
vec4 soft_sample(sampler2D tex, vec2 uv) {
	vec2 pixel_size = (1.0 / vec2(textureSize(tex, 0)));
	vec4 col = vec4(0.0);
    for(int y = -1; y <= 1; y++) {
		for(int x = -1; x <= 1; x++) {
			vec2 pixel_off = vec2(float(x), float(y));
			col += texture(tex, uv + pixel_off * pixel_size);
		}
	}
	return col / 9.0;
}

// Take a hue value and cyclically shift it
vec3 hueShift( vec3 color, float hueAdjust ){
	const vec3  kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
	const vec3  kRGBToI      = vec3 (0.596, -0.275, -0.321);
	const vec3  kRGBToQ      = vec3 (0.212, -0.523, 0.311);
	const vec3  kYIQToR     = vec3 (1.0, 0.956, 0.621);
	const vec3  kYIQToG     = vec3 (1.0, -0.272, -0.647);
	const vec3  kYIQToB     = vec3 (1.0, -1.107, 1.704);
	float   YPrime  = dot (color, kRGBToYPrime);
	float   I       = dot (color, kRGBToI);
	float   Q       = dot (color, kRGBToQ);
	float   hue     = atan (Q, I);
	float   chroma  = sqrt (I * I + Q * Q);
	
	hue += hueAdjust;
	
	Q = chroma * sin (hue);
	I = chroma * cos (hue);
	
	vec3    yIQ   = vec3 (YPrime, I, Q);
	return vec3( dot (yIQ, kYIQToR), dot (yIQ, kYIQToG), dot (yIQ, kYIQToB) );
}

// Given the screen size in pixels (SCREEN_PIXEL_SIZE), returns the aspect ratio
// to unstretch textures
vec2 screen_ratio(vec2 ps) {
	return (ps.x > ps.y) ? vec2(ps.y / ps.x, 1) : vec2(1, ps.x / ps.y);
}

void fragment() {
	// Since the SandSimulation saves the grid as an L8 texture, we can check
	// the identity of a point by seeing how bright it is
	int id = int(texture(TEXTURE, UV).r * 255.0);
	// Each element has its own case to draw
	// IDs are the same as the ones given in ../extension/sand_simulation.cpp
	
	// PUVs scaled to pixels 
	int pX = int(floor(UV.x * float(width) / float(px_scale)));
	int pY = int(floor(UV.y * float(height) / float(px_scale)));
	vec2 PUV = vec2(float(pX) / float(width / px_scale), float(pY) / float(height / px_scale));
	
	switch (id) {
		case 0: 
			COLOR = soft_sample(sky_texture, 
			 screen_ratio(SCREEN_PIXEL_SIZE) * vec2(
				shift(sin(TIME / 64.0)) / 2.0, 
				shift(cos(TIME / 80.0)) / 2.0) + PUV * 0.5 
				/ 1.0); 
				break;
		case 1: COLOR = sand_color_1; break;
		case 2: COLOR = rock_color_1; break;
		case 3: // Water
			// I am honestly not entirely sure how this code works, but it is esentially using
			// sin and cos of different scales of TIME to create wavey effects
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + sin(TIME / 16.0)) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			// Base color for the waves
			COLOR = water_color_1 * y + water_color_2 * (1.0 - y);
			
			// Adding a layer of the noise texture and using match_amount to give shading to 
			// other cells in water
			float z = match_amount(TEXTURE, UV, id);
			texCoord = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord) + COLOR * z + water_color_3 * (1.0 - z);
			break;
		case 4: COLOR = polliwog_color_1; break;
		case 5: // Fire, same effect as water
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(fire_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x * 2.0 + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = fire_color_1 * y + fire_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			texCoord = vec2(2.0 * PUV.x + sin(TIME / 24.0), 2.0 * PUV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) * soft_sample(fire_noise, ratio * texCoord) + COLOR * z + fire_color_3 * (1.0 - z);
			break;
		case 6:
			float y = match_amount(TEXTURE, UV, 6);
			COLOR = smoke_color_1 * y + smoke_color_2 * (1.0 - y);
			break;
		case 7: COLOR = algae_color_1; break;
		case 8: COLOR = sand_duck_color_1; break;
		case 9:
			float x = match_amount(TEXTURE, UV, 9);
			COLOR = explosion_color_1 * x + explosion_color_2 * (1.0 - x);
			break;
		case 10: 
			float x = shift(sin(TIME));
			COLOR = lead_azide_color_1 * x + lead_azide_color_2 * (1.0 - x); break;
		case 11: COLOR = soil_color; break;
		case 12: COLOR = seed_color_1; break;
		case 13: COLOR = seed_color_2; break;
		case 14: COLOR = grass_color_1; break;
		case 15:
			COLOR = soft_sample(marble_texture, PUV * screen_ratio(SCREEN_PIXEL_SIZE));
			break;
		case 16:
			float x = match_amount(TEXTURE, UV, 16);
			COLOR = dust_color_1 * x + dust_color_2 * (1.0 - x);
			break;
		case 17:
			COLOR = PUV.y * steel_color_2 + (1.0 - PUV.y) * steel_color_1;
			break;
		case 18: COLOR = wood_color_1; break;
		case 19: // Ice is virtually the same as water except we slow the waves and lighten it up 
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 128.0), 2.0*PUV.y + sin(TIME / 128.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 64.0) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = water_color_1 * y + 1.35 * water_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			texCoord = vec2(1.5 * PUV.x + sin(TIME / 60.0), 1.5 * PUV.y + sin(TIME / 60.0));
			COLOR = 1.8 * shift(cos(TIME / 32.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord) + COLOR * z + water_color_3 * (1.0 - z);
			break;
		case 20: // Lava
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(fire_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x * 2.0 + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = fire_color_1 * y + fire_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			texCoord = vec2(2.0 * PUV.x + sin(TIME / 24.0), 2.0 * PUV.y + sin(TIME / 24.0));
			COLOR = shift(cos(TIME / 4.0)) * soft_sample(fire_noise, ratio * texCoord) + COLOR * z + fire_color_3 * (1.0 - z);
			break;
		case 21: // Acid
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = acid_color_1 * y + acid_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			texCoord = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord) + COLOR * z + acid_color_3 * (1.0 - z);
			break;
		case 22:
			float y = match_amount(TEXTURE, UV, 22);
			COLOR = acid_gas_color_1 * y + acid_gas_color_2 * (1.0 - y);
			break;
		case 23: COLOR = fairy_color_1; break;
		case 24: // Blue fire
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(fire_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x * 2.0 + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = b_fire_color_1 * y + b_fire_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			texCoord = vec2(2.0 * PUV.x + sin(TIME / 24.0), 2.0 * PUV.y + sin(TIME / 24.0));
			COLOR = shift(cos(TIME / 4.0)) * soft_sample(fire_noise, ratio * texCoord) + COLOR * z + b_fire_color_3 * (1.0 - z);
			break;
		case 25: // Glass
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			float dif = 1.0 - abs(PUV.x + PUV.y - abs(sin(TIME / 4.0)));
			if (dif < 0.0)
				dif = 0.0;
			COLOR = 0.5 * vec4(soft_sample(glass_texture, vec2(cos(TIME / 64.0), sin(TIME / 64.0)) + PUV * ratio).a * dif);
			COLOR += 0.5 * vec4(soft_sample(glass_texture, vec2(cos(TIME / 48.0), sin(TIME / 48.0)) + PUV * ratio).a * (1.0 - dif));
			COLOR += vec4((sin(TIME / 42.0) + 1.0) / 8.0);
			COLOR += (0.25 + shift(sin(TIME/16.0)) / 2.0) * soft_sample(sky_texture, vec2(shift(sin(TIME / 32.0)) / 2.0, shift(cos(TIME / 48.0)) / 2.0) + PUV * 0.5 * screen_ratio(SCREEN_PIXEL_SIZE));
			COLOR.a = 1.0;
			
			break;
		case 26:
			float y = match_amount(TEXTURE, UV, 26);
			COLOR = laser_color_2 * y + laser_color_1 * (1.0 - y);
			break;
		case 27: // Crystal
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec4 col = soft_sample(crystal_texture, PUV * ratio);
			float x = (col.r + col.g + col.b) / 3.0;
			x = shift(sin(x)) * shift(sin(TIME / 3.0));
			COLOR = crystal_color_1 * x + crystal_color_2 * (1.0 - x);
			vec2 texCoord = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			
			COLOR += x * shift(cos(TIME / 4.0)) * soft_sample(water_noise, ratio * texCoord);
			break;
		case 28:
			float y = match_amount(TEXTURE, UV, 28);
			COLOR = air_color_2 * y + air_color_1 * (1.0 - y);
			break;
		case 29:
			float y = match_amount(TEXTURE, UV, 29);
			COLOR = black_hole_color_2 * y + black_hole_color_1 * (1.0 - y);
			break;
		case 30: // Oil
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = oil_color_1 * y + oil_color_2 * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord2) + COLOR * z + oil_color_3 * (1.0 - z);
			break;
		case 31: COLOR = urchin_color_1; break;
		case 32: COLOR = dragon_color_1; break;
		case 33: COLOR = critter_color_1; break;
		case 34:
			float x = match_amount(TEXTURE, UV, 34);
			COLOR = nuclear_explosion_color_1 * x + nuclear_explosion_color_2 * (1.0 - x);
			break;
		case 35:
			float x = shift(sin(TIME));
			COLOR = uranium_color_1 * x + uranium_color_2 * (1.0 - x); break;
		case 36:
			float y = match_amount(TEXTURE, UV, 36);
			COLOR = neutron_color_2 * y + neutron_color_1 * (1.0 - y);
			break;
		case 37: COLOR = lightning_color_1; break;
		case 38:
			float y = match_amount(TEXTURE, UV, 38);
			COLOR = plasma_color_2 * y + plasma_color_1 * (1.0 - y);
			break;
		case 39:
			float y = match_amount(TEXTURE, UV, 39);
			COLOR = electron_color_2 * y + electron_color_1 * (1.0 - y);
			break;
		case 40:
			float y = match_amount(TEXTURE, UV, 40);
			COLOR = storm_plasma_color_2 * y + storm_plasma_color_1 * (1.0 - y);
			break;
		case 41:
			float y = match_amount(TEXTURE, UV, 41);
			COLOR = hurricane_color_2 * y + hurricane_color_1 * (1.0 - y);
			break;
		case 42:
			float p1 = cos(floor(UV.x * float(width / px_scale)));
			float p2 = cos(floor(UV.y * float(height / px_scale)));
			
			float z = float(floatBitsToInt(12312.4324143 + p1 * 2134904234234323.21332421 * p2 * 392342342324892.3242341) & 0xFF) / float(0xFF);
			if (z < 0.5)
				z += 0.5;
			vec3 col = hueShift(vec3(z, 0.2, 1.0), shift(cos(PUV.y)) * shift(sin(8.0 * PUV.x * sin(TIME / 12.0))) * shift(sin(z)) * 2.0 * PI);
			COLOR = vec4(col.r, col.g, col.b, 1.0);
			break;
		case 43: 
			float p1 = cos(floor(UV.x * float(width / px_scale)));
			float p2 = cos(floor(UV.y * float(height / px_scale)));
			
			float z = float(floatBitsToInt(12312.4324143 + p1 * 2134904234234323.21332421 * p2 * 392342342324892.3242341) & 0xFF) / float(0xFF);
			if (z < 0.5)
				z += 0.5;
			vec3 col = hueShift(vec3(z, 0.0, 1.0), shift(cos(PUV.y)) * shift(sin(8.0 * PUV.x * sin(TIME / 12.0))) * shift(sin(z)) * 2.0 * PI);
			vec4 powder_color = vec4(col.r, col.g, col.b, 1.0) / 2.5;
			
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = powder_color * y + powder_color_2 * (1.0 - y);
			
			z = match_amount(TEXTURE, UV, id);
			
			vec2 texCoord2 = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord2) + COLOR * z + powder_color_3 * (1.0 - z);
			break;
		case 44:
			vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
			vec2 texCoord = vec2(2.0*PUV.x + sin(TIME / 32.0), 2.0*PUV.y + sin(TIME / 32.0));
			
			float x = soft_sample(water_noise, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / 4.0) * 2.0 + sin(TIME / 2.0));
			
			float y = shift(cos(sin(3.0 * PUV.x + TIME / 16.0) * 16.0 * PUV.x + PI * x + PUV.y * 8.0));
			y = abs(y - 0.5);
			
			COLOR = PUV.y * y * steel_color_1 + steel_color_1 * (1.0 - PUV.y) * (1.0 - y);
			
			float z = match_amount(TEXTURE, UV, id);
			
			texCoord = vec2(1.5 * PUV.x + sin(TIME / 24.0), 1.5 * PUV.y + sin(TIME / 24.0));
			COLOR = shift(cos(TIME / 4.0)) / 2.0 * soft_sample(water_noise, ratio * texCoord) + COLOR * z + vec4(1.0) * (1.0 - z);
			break;
	}
}