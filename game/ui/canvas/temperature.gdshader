// https://godotshaders.com/shader/white-balance-shader/
shader_type canvas_item;

uniform sampler2D warm_color: source_color;
uniform sampler2D cool_color: source_color;
uniform float temperature = 0;

void fragment() {
	vec4 input_color = textureLod(SCREEN_TEXTURE, SCREEN_UV, 0.0);
	
	float grayscale_value = dot(input_color.rgb, vec3(0.299, 0.587, 0.114));
	vec3 sampled_color;
	if (temperature > 0.0) {
		sampled_color = texture(warm_color, vec2(grayscale_value, 0.0)).rgb;
		COLOR.rgb = mix(input_color.rgb, sampled_color, temperature);
	}
	else {
		sampled_color = texture(cool_color, vec2(grayscale_value, 0.0)).rgb;
		COLOR.rgb = mix(input_color.rgb, sampled_color, temperature * -1.0);
	}
	COLOR.a = input_color.a;
}