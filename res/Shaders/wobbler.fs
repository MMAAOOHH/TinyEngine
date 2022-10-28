#version 330 core


in vec2 TexCoords;
in vec2 f_Position;

out vec4 color;

uniform vec2 u_resolution;
uniform float u_radius;
uniform vec3 u_color;
uniform sampler2D image;
uniform float u_time;
uniform vec2 u_screenResolution;


float circle(vec2 uv, float radius)
{
  return 1 - step(radius, length(uv - vec2(0.5)));
}

float wobble(float time, float p, float amplitude, float frequence, float speed)
{
    return amplitude * sin(p * frequence + time * speed);
}

void main()
{
  vec2 uv = TexCoords.xy / u_resolution.xy;
  vec2 uvscreen = TexCoords / u_screenResolution;

  // Wobble
  float t = u_time;
  float a = 0.009;
  float f = 50.0;
  float s = 6.0;

  uv.x += wobble(t, uvscreen.x, a, f, s);
  uv.y += wobble(t, uvscreen.y, a, f, s);

  // Circle
  vec3 col = vec3(0);
  float c = circle(uv, u_radius);
  col = vec3(c);
 
  color = vec4(col, 1.0)  * vec4(u_color, 1.0);
  if(color.rgb == vec3(0)) discard;

}