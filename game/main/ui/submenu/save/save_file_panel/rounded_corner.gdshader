shader_type canvas_item;
//https://gist.github.com/rohanrhu/11ffd387e1cc228d15bcea56fad4f593

uniform float radius: hint_range(0., 1.) = 1;
uniform float square_scale: hint_range(0., 1.) = 0.1;

void fragment() {
    float sc = square_scale + square_scale/2.;
    float r = square_scale + (1. - radius) * (square_scale/2.);
    
    float scax = 1. - square_scale;
    
    float dx;
    float dy;
    float d;
    float a;
    
    if (UV.x < square_scale && UV.y > scax) {
        dx = square_scale - UV.x;
        dy = scax - UV.y;
        d = sqrt(dx * dx + dy * dy);
        a = asin(d);
        
        if (a > r) {
            COLOR.a = 0.;
        }
    }
    
    if (UV.x < square_scale && UV.y < square_scale) {
        dx = square_scale - UV.x;
        dy = square_scale - UV.y;
        d = sqrt(dx * dx + dy * dy);
        a = asin(d);
        
        if (a > r) {
             COLOR.a = 0.;
        }
    }
    
    if (UV.x > scax && UV.y < square_scale) {
        dx = scax - UV.x;
        dy = square_scale - UV.y;
        d = sqrt(dx * dx + dy * dy);
        a = asin(d);
        
        if (a > r) {
             COLOR.a = 0.;
        }
    }

    if (UV.x > scax && UV.y > scax) {
        dx = scax - UV.x;
        dy = scax - UV.y;
        d = sqrt(dx * dx + dy * dy);
        a = asin(d);
        
        if (a > r) {
            COLOR.a = 0.;
        }
    }
}