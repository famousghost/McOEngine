#version 330 core

#define MAX_STEPS 255
#define MAX_DIST 100.0
#define MIN_DIST 0.01

out vec4 fragColor;

uniform vec2 MCScreenResolution;
uniform vec3 MCWorldSpaceLightPos;

in vec3 camWorldPos;
in vec3 camDirectionPos;

float sdfSphere(vec3 p, vec3 offset, float r)
{
	return length(p - offset) - r;
}

float sdfScene(vec3 p)
{
	return sdfSphere(p, vec3(0.0f, 0.0f, 0.0f), 0.1f);
}
float rayMarching(vec3 ro, vec3 rd)
{
	float depth = 0.0f;
	for(int i = 0; i < MAX_STEPS; ++i)
	{
		vec3 p = ro + rd * depth;
		float d = sdfScene(p);
		depth += d;
		if(d >= MAX_DIST || d <= MIN_DIST)
			break;
	}
	return depth;
}

vec3 getNormal(vec3 p)
{
	float e = 0.05f;
	return normalize(vec3(sdfScene(vec3(p.x - e, p.y, p.z)) - sdfScene(vec3(p.x + e, p.y, p.z)),
	                      sdfScene(vec3(p.x, p.y - e, p.z)) - sdfScene(vec3(p.x, p.y + e, p.z)),
						  sdfScene(vec3(p.x, p.y, p.z - e)) - sdfScene(vec3(p.x, p.y, p.z + e))));
}	

float saturate(float x)
{
	return clamp(x, 0.0f, 1.0f);
}

float diffuseLight(vec3 p, vec3 normal, vec3 lightPos)
{
	vec3 lightDir = normalize(p - lightPos);
	return saturate(dot(lightDir, normal));
}

float specularLight(vec3 p, vec3 normal, vec3 rd, vec3 lightPos, float strength)
{
	vec3 lightDir = normalize(p - lightPos);
	vec3 lightDirReflected = normalize(reflect(-lightDir, normal));
	
	return pow(saturate(dot(lightDirReflected, rd)), strength);
}

void main()
{
	vec2 uv = (gl_FragCoord.xy - 0.5f * MCScreenResolution.xy) / MCScreenResolution.y;
	
	vec3 ro = vec3(0.0f, 0.0f, 5.0f);
	vec3 rd = normalize(vec3(uv, -1.0f));
	
	float d = rayMarching(ro, rd);
	vec3 col = vec3(0.2f, 0.2f, 0.2f);
	if(d <= MAX_DIST)
	{
		vec3 p = ro + rd * d;
		
		vec3 normal = getNormal(p);
		
		float diff = diffuseLight(p, normal, MCWorldSpaceLightPos);
		float spec = specularLight(p, normal, rd, MCWorldSpaceLightPos, 32.0f);
		
		col = vec3(diff + spec) * vec3(1.0f, 0.0f, 0.0f);
	}

	fragColor = vec4(col, 1.0f);
}