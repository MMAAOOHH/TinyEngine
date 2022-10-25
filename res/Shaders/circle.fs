#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

uniform float windowHeight;
uniform float radius;
uniform float smoothUni;

void main()
{   
    vec2 uv = TexCoords;
    uv -= 0.5;

    float val0 = smoothUni * 0.1;
    float val1 = smoothUni * 0.02;
    float val2 = smoothUni * 0.008;
    float val3 = smoothUni * 0.002;

    float percentage = radius / windowHeight;
    float smoothness;
    if (percentage > 1.0) smoothness = val3;
    else if (percentage > 0.5) smoothness = mix(val2, val3, (percentage-0.5) / 0.5);
    else if (percentage > 0.1) smoothness = mix(val1, val2, (percentage-0.1) / 0.4);
    else smoothness = mix(val0, val1, percentage / 0.1);

    float d = smoothstep(0.5, 0.5-smoothness, length(uv));
    
    color = vec4(spriteColor, d) * texture(image, TexCoords);
}