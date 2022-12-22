shader_type canvas_item;

// Each element defines its uniforms for colors, textures, etc. and uses them to 
// render itself. The parameters can be configured at canvas/element_painter.tres

// This code is not optimal or modular, but convenient to quickly add elements

uniform int width = 1000;
uniform int height = 800;
uniform int px_scale = 4;

uniform int[53] flat_color_id_match;
uniform vec3[13] flat_color;

uniform int[53] gradient_id_match;
uniform vec3[19] gradient_color_a;
uniform vec3[19] gradient_color_b;

uniform int[53] fluid_id_match;

uniform vec3[10] color_a;
uniform vec3[10] color_b;
uniform vec3[10] color_c;
uniform float[10] noise_scale;
uniform float[10] noise_speed;
uniform float[10] current_size;
uniform float[10] wave_cycle;
uniform float[10] contraction_size;
uniform float[10] wave_density;
uniform float[10] shimmer_speed;
uniform float[10] shimmer_density;
uniform float[10] shimmer_opacity;
uniform float[10] shimmer_cycle;

uniform sampler2D water_texture: source_color, repeat_enable;

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
			uv += pixel_off * pixel_size;
			uv.x -= floor(uv.x);
			uv.y -= floor(uv.y);
			col += texture(tex, uv);
		}
	}
	return col / 9.0;
}

// Take a hue value and cyclically shift it
vec3 hue_shift(vec3 color, float hueAdjust){
	const vec3 kRGBToYPrime = vec3(0.299, 0.587, 0.114);
	const vec3 kRGBToI = vec3(0.596, -0.275, -0.321);
	const vec3 kRGBToQ = vec3(0.212, -0.523, 0.311);
	const vec3 kYIQToR = vec3(1.0, 0.956, 0.621);
	const vec3 kYIQToG = vec3(1.0, -0.272, -0.647);
	const vec3 kYIQToB = vec3(1.0, -1.107, 1.704);
	float YPrime = dot(color, kRGBToYPrime);
	float I = dot(color, kRGBToI);
	float Q = dot(color, kRGBToQ);
	float hue = atan(Q, I);
	float chroma = sqrt(I * I + Q * Q);
	
	hue += hueAdjust;
	
	Q = chroma * sin (hue);
	I = chroma * cos (hue);
	
	vec3 yIQ = vec3(YPrime, I, Q);
	return vec3(dot (yIQ, kYIQToR), dot(yIQ, kYIQToG), dot(yIQ, kYIQToB));
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
	int pX = int(round(floor(UV.x * float(width) / float(px_scale))));
	int pY = int(round(floor(UV.y * float(height) / float(px_scale))));
	vec2 PUV = vec2(float(pX) / (float(width) / float(px_scale)), float(pY) / (float(height) / float(px_scale)));
	
	vec3 col = vec3(0.0);
	if (fluid_id_match[id] != 0) {
		int i = fluid_id_match[id] - 1;
		vec2 ratio = screen_ratio(SCREEN_PIXEL_SIZE);
		vec2 texCoord = vec2(noise_scale[i] * PUV.x + sin(TIME / noise_speed[i]), noise_scale[i] * PUV.y + sin(TIME / noise_speed[i]));
		float x = soft_sample(water_texture, ratio * texCoord).r * (PUV.x + PUV.y + sin(PUV.x / current_size[i]) * 2.0 + sin(TIME / wave_cycle[i]));
		float y = abs(shift(cos(sin(wave_density[i] * PUV.x + sin(TIME / contraction_size[i])) * 16.0 * PUV.x + PI * x + PUV.y * 8.0)) - 0.5);
		float z = match_amount(TEXTURE, UV, id);
		col = color_a[i].rgb * y + color_b[i].rgb * (1.0 - y);
		texCoord = vec2(shimmer_density[i] * PUV.x + sin(TIME / shimmer_speed[i]), shimmer_density[i] * PUV.y + sin(TIME / shimmer_speed[i]));
		col = shift(cos(TIME / shimmer_cycle[i])) * shimmer_opacity[i] * soft_sample(water_texture, ratio * texCoord).rgb + col * z + color_c[i] * (1.0 - z);
	} else if (flat_color_id_match[id] != 0) {
		col = flat_color[flat_color_id_match[id] - 1];
	} else if (gradient_id_match[id] != 0) {
		float x = match_amount(TEXTURE, UV, id);
		int i = gradient_id_match[id] - 1;
		col = gradient_color_a[i] * x + gradient_color_b[i] * (1.0 - x);
	} else {
		col = COLOR.rgb;
	}
	COLOR = vec4(col.r, col.g, col.b, 1.0);
	
}