
// fragment shader

#version 120

uniform float left;
uniform float right;
uniform float top;
uniform float bottom;

uniform float cropLeft;
uniform float cropRight;
uniform float cropTop;
uniform float cropBottom;

void main()
{
    
    float alpha_video = ( float(gl_FragCoord.x > left) * float(gl_FragCoord.x < right) * float(gl_FragCoord.y < top) * float(gl_FragCoord.y > bottom) );
    
    float alpha_crop = 1.0 - ( float(gl_FragCoord.x > cropLeft) * float(gl_FragCoord.x < cropRight) * float(gl_FragCoord.y < cropTop) * float(gl_FragCoord.y > cropBottom) );
    float alpha = 0.5 * alpha_video * alpha_crop;
    //float(gl_FragCoord.y < 0.6) *
    //float(gl_FragCoord.y > 0.2));
    //gl_Color *
    //vec2 uv = gl_FragCoord.xy / screenSize;
    //vec4(1.0, 0.0, 1.0, 1.0) *
    //gl_FragColor.r = gl_FragCoord.x/1000;// =  vec4(1.0, 0.0, 1.0, alpha);
    gl_FragColor = vec4(0.5, 0.5, 0.5, alpha);
}
