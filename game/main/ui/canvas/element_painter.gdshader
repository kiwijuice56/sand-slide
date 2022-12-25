shader_type canvas_item;

uniform int width = 1000;
uniform int height = 800;
uniform int px_scale = 4;

uniform int[84] flat_color_id_match;
uniform vec3[24] flat_color;

uniform int[84] gradient_id_match;
uniform vec3[32] gradient_color_a;
uniform vec3[32] gradient_color_b;
uniform vec3[32] gradient_color_c;
uniform vec3[32] gradient_color_d;
uniform vec3[32] gradient_color_e;

uniform float[32] gradient_offset_1;
uniform float[32] gradient_offset_2;
uniform float[32] gradient_offset_3;

uniform int[84] fluid_id_match;
uniform vec3[24] color_a;
uniform vec3[24] color_b;
uniform vec3[24] color_c;
uniform int[24] noise_texture;
uniform float[24] noise_scale;
uniform float[24] noise_speed;
uniform float[24] current_size;
uniform float[24] wave_cycle;
uniform float[24] contraction_size;
uniform float[24] wave_density;
uniform float[24] shimmer_speed;
uniform float[24] shimmer_density;
uniform float[24] shimmer_opacity;
uniform float[24] shimmer_cycle;

uniform int[84] metal_id_match;
uniform vec3[24] metal_color_a;
uniform vec3[24] metal_color_b; 

uniform sampler2D water_texture: source_color, repeat_enable;
uniform sampler2D fire_texture: source_color, repeat_enable;
uniform sampler2D crystal_texture: source_color, repeat_enable;

// Returns a value [0, 1] of the saturation of cells given_id arround the pixel
// at uv. Returns 0 when no cells of given_id are touching the 
// pixel and 1 when all 8 surrounding cells are of type given_id
float match_amount(sampler2D tex, vec2 uv, int given_id) {
	vec2 pixel_size = 1.0 / vec2(textureSize(tex, 0));
	int matching = 0;
    for(int y = -1; y <= 1; y++) {
		for(int x = -1; x <= 1; x++) {
			if (x == 0 && y == 0)
				continue;
			vec2 pixel_off = vec2(float(x), float(y));
			int id = int(texture(tex, uv + pixel_off * pixel_size).r * 255.0);
			if (id == given_id) 
				matching++;
		}
	}
	return float(matching) / 8.0;
}

void fragment() {
	// Since the SandSimulation saves the grid as an L8 texture, we can check
	// the identity of a point by seeing how bright it is
	int id = int(texture(TEXTURE, UV).r * 255.0);
	// Each element has its own case to draw
	// IDs are the same as the ones given in ../extension/sand_simulation.cpp
	
	// PUVs scaled to pixels 
	int pX = int(round(floor(UV.x * float(width) / float(px_scale))));
	int pY = int(round(floor(UV.y * float(height) / float(px_scale))));
	vec2 PUV = vec2(float(pX) / (float(width) / float(px_scale)), float(pY) / (float(height) / float(px_scale)));
	
	vec3 col = vec3(0.0);
	if (fluid_id_match[id] != 0) {
		int i = fluid_id_match[id] - 1;
		vec2 ratio = (SCREEN_PIXEL_SIZE.x > SCREEN_PIXEL_SIZE.y) ?
			vec2(SCREEN_PIXEL_SIZE.y / SCREEN_PIXEL_SIZE.x, 1) : 
			vec2(1, SCREEN_PIXEL_SIZE.x / SCREEN_PIXEL_SIZE.y);
		vec2 texCoord = vec2(noise_scale[i] * PUV.x + sin(TIME / noise_speed[i]), noise_scale[i] * PUV.y + sin(TIME / noise_speed[i]));
		
		float x = PUV.x + PUV.y + sin(PUV.x / current_size[i]) * 2.0 + sin(TIME / wave_cycle[i]);
		
		switch (noise_texture[i]) {
			case 0: x *= texture(water_texture, ratio * texCoord).r; break;
			case 1: x *= texture(fire_texture, ratio * texCoord).r; break;
			case 2: x *= texture(crystal_texture, ratio * texCoord).r; break;
		}
		float y = abs((cos(sin(wave_density[i] * PUV.x + sin(TIME / contraction_size[i])) * 16.0 * PUV.x + PI * x + PUV.y * 8.0) + 1.0) / 2.0 - 0.5);
		float z = match_amount(TEXTURE, UV, id);
		col = color_a[i].rgb * y + color_b[i].rgb * (1.0 - y);
		texCoord = vec2(shimmer_density[i] * PUV.x + sin(TIME / shimmer_speed[i]), shimmer_density[i] * PUV.y + sin(TIME / shimmer_speed[i]));
		
		vec3 tex;
		switch (noise_texture[i]) {
			case 0: tex = texture(water_texture, ratio * texCoord).rgb; break;
			case 1: tex = texture(fire_texture, ratio * texCoord).rgb; break;
			case 2: tex = texture(crystal_texture, ratio * texCoord).rgb; break;
		}
		
		col = (cos(TIME / shimmer_cycle[i]) + 1.0) / 2.0 * shimmer_opacity[i] * tex + col * z + color_c[i] * (1.0 - z);
	} else if (flat_color_id_match[id] != 0) {
		col = flat_color[flat_color_id_match[id] - 1];
	} else if (gradient_id_match[id] != 0) {
		float x = match_amount(TEXTURE, UV, id);
		int i = gradient_id_match[id] - 1;
		col = mix(gradient_color_a[i], gradient_color_b[i], smoothstep(0.0, gradient_offset_1[i], x));
		col = mix(col, gradient_color_c[i], smoothstep(gradient_offset_1[i], gradient_offset_2[i], x));
		col = mix(col, gradient_color_d[i], smoothstep(gradient_offset_2[i], gradient_offset_3[i], x));
		col = mix(col, gradient_color_e[i], smoothstep(gradient_offset_3[i], 1.0, x));
	} else if (metal_id_match[id] != 0) {
		int i = metal_id_match[id] - 1;
		col = mix(metal_color_a[i], metal_color_b[i], PUV.y);
	}
	COLOR = vec4(col.r, col.g, col.b, 1.0);
}