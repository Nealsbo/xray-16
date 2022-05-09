#ifndef SHARED_COMMON_H
#define SHARED_COMMON_H
//

#define half        float
#define half2       vec2
#define half3       vec3
#define half4       vec4
#define float2      vec2
#define float3      vec3
#define float4      vec4
#define int2        ivec2
#define int3        ivec3
#define int4        ivec4
#define uint2       uvec2
#define uint3       uvec3
#define uint4       uvec4
#define half3x3     mat3
#define half4x4     mat4
#define half3x4     mat4x3
#define float3x3    mat3
#define float4x4    mat4
#define float3x4    mat4x3

vec4	mul(int a,		vec4 b)	{ return a * b; }
vec4	mul(float a,	vec4 b)	{ return a * b; }
vec3	mul(mat3 a,		vec3 b)	{ return a * b; }
vec3	mul(vec3 a,		mat3 b)	{ return a * b; }
mat3	mul(mat3 a,		mat3 b)	{ return a * b; }
vec4	mul(mat4 a,		vec4 b)	{ return a * b; }
vec4	mul(vec4 a,		mat4 b)	{ return a * b; }
mat4	mul(mat4 a,		mat4 b)	{ return a * b; }
vec3	mul(mat4x3 a,	vec4 b)	{ return a * b; }
vec3	mul(mat4x3 a,	vec3 b)	{ return mat3(a) * b; }
void	sincos(float x, out float s, out float c) { s = sin(x); c = cos(x); }

#define lerp        mix
#define frac        fract
#define saturate(a) clamp(a, 0.0, 1.0)
#define clip(x)		if (x < 0) discard
#define tex2D		texture
#define tex2Dproj	textureProj
#define tex2Dlod(s,t)	textureLod(s,t.xy,t.w)
#define tex3D		texture
#define texCUBE 	texture
#define asuint		floatBitsToUint
#define asfloat		uintBitsToFloat
#define mask(m,a,b)	mix(b,a,m)

#define COLOR		0
#define COLOR0		0
#define COLOR1		1
#define COLOR2		2
#define POSITION	3
#define POSITIONT	3
#define POSITION0	3
#define POSITION1	4
#define TANGENT		4
#define NORMAL		5
#define NORMAL0		5
#define NORMAL1		6
#define BINORMAL	6
#define FOG		7
#define TEXCOORD0	8
#define TEXCOORD1	9
#define TEXCOORD2	10
#define TEXCOORD3	11
#define TEXCOORD4	12
#define TEXCOORD5	13
#define TEXCOORD6	14
#define TEXCOORD7	15

uniform float3x4	m_W;
uniform float3x4	m_V;
uniform float4x4 	m_P;
uniform float3x4	m_WV;
uniform float4x4 	m_VP;
uniform float4x4 	m_WVP;
uniform float4		timers;
uniform float4		fog_plane;
uniform float4		fog_params;		// x=near*(1/(far-near)), ?,?, w = -1/(far-near)
uniform float4		fog_color;
uniform float3		L_sun_color;
uniform float3		L_sun_dir_w;
uniform float3		L_sun_dir_e;
uniform float4		L_hemi_color;
uniform float4		L_ambient;		// L_ambient.w = skynbox-lerp-factor
uniform float3 		eye_position;
uniform float3		eye_direction;
uniform float3		eye_normal;
uniform	float4 		dt_params;

float3 unpack_normal(float3 v) { return 2*v-1; }
float3 unpack_bx2(float3 v) { return 2*v-1; }
float3 unpack_bx4(float3 v) { return 4*v-2; }

float2 	unpack_tc_base(float2 tc, float du, float dv)
{
	return (tc.xy + float2	(du,dv))*(32.f/32768.f);
}

float2 unpack_tc_lmap(float2 tc) { return tc*(1.f/32768.f); } // [-1  .. +1 ]

float calc_cyclic(float x)
{
	float 	phase 	= 1/(2*3.141592653589f);
	float 	sqrt2	= 1.4142136f;
	float 	sqrt2m2	= 2.8284271f;
	float 	f 	= sqrt2m2*frac(x)-sqrt2;	// [-sqrt2 .. +sqrt2]
	return 	f*f - 1.f;				// [-1     .. +1]
}

float2 calc_xz_wave(float2 dir2D, float frac)		{
	// Beizer
	float2  ctrl_A	= float2(0.f,		0.f	);
	float2 	ctrl_B	= float2(dir2D.x,	dir2D.y	);
	return  lerp	(ctrl_A, ctrl_B, frac);
}

#endif
