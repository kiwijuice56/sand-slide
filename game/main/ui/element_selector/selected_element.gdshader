shader_type canvas_item;

void fragment() {
	COLOR.rgb = COLOR.rgb - vec3(0.125 / 2.0);
	if (COLOR.rgb != vec3(1.0) && COLOR.rgb != vec3(0.0) && sin(SCREEN_UV.x * 128.0 + SCREEN_UV.y * 80.0 + 3.0 * TIME) > 0.0) {
		COLOR.rgb = COLOR.rgb + vec3(0.125);
	} 
	COLOR.rgb += UV.y / 12.0;
}
