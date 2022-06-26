#version 460 core
out vec4 FragColor;
in vec4 fColor;

vec2 resolution=vec2(500,500);
vec3 colorA=vec3(0.0,1.0,1.0);
vec3 colorB=vec3(0.0,0.0,1.0);

void main()
{
    vec2 st=gl_FragCoord.xy/resolution.xy;
    
    vec3 newcolor=mix(colorA,colorB,0.7);
    // vec3 newcolor=fColor.xyz;
    FragColor=vec4(newcolor,1.0);
}