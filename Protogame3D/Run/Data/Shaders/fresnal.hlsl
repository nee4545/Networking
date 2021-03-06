#include "ShaderUtils.hlsl"

struct vs_input_t
{
   // we are not defining our own input data; 
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float4 tangent : TANGENT;
};

//--------------------------------------------------------------------------------------
// Programmable Shader Stages
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// for passing data from vertex to fragment (v-2-f)
struct v2f_t
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : UV;


    float3 world_position : WORLD_POSITION;
    float3 world_normal : WORLD_NORMAL;
    float4 world_tangent : WORLD_TANGENT;
};


//--------------------------------------------------------------------------------------
cbuffer material_constants : register( b5 )                                                     // constant buffer slot 5
{
    float3 FRESNEL_COLOR;
    float  FRESNEL_POWER;
    float3 pad00;
    float  FRESNEL_FACTOR;
};
//--------------------------------------------------------------------------------------
//                      PROGRAMMABLE SHADER STAGES FUNCTIONS
//--------------------------------------------------------------------------------------
//
// VERTEX SHADER
//
//--------------------------------------------------------------------------------------
v2f_t VertexFunction(vs_input_t input)
{
    v2f_t v2f = (v2f_t) 0;
   // move the vertex through the spaces
    float4 local_pos        = float4( input.position , 1.0f );                                  // passed in position is usually inferred to be "local position", ie, local to the object
    float4 world_pos        = mul( MODEL , local_pos );                                         // world pos is the object moved to its place int he world by the model, not used yet
    float4 camera_pos       = mul( VIEW , world_pos );
    float4 clip_pos         = mul( PROJECTION , camera_pos );
   // normal is currently in model/local space
    float4 local_normal     = float4( input.normal , 0.0f );
    float4 world_normal     = mul( MODEL , local_normal );
   // tangent & bitangent
    float4 local_tangent    = float4( input.tangent.xyz , 0.0f );
    float4 world_tangent    = mul( MODEL , local_tangent );
    v2f.position            = clip_pos;                                                         // we want to output the clip position to raster (a perspective point)
    v2f.color               = input.color;
    v2f.uv                  = input.uv;
    v2f.world_position      = world_pos.xyz;
    v2f.world_normal        = world_normal.xyz;
    v2f.world_tangent       = float4( world_tangent.xyz , input.tangent.w );
    return v2f;
}
//--------------------------------------------------------------------------------------
//
// FRAGMENT SHADER
//
//--------------------------------------------------------------------------------------
// SV_Target0 at the end means the float4 being returned
// is being drawn to the first bound color target.
//--------------------------------------------------------------------------------------
float4 FragmentFunction(v2f_t input) : SV_Target0
{
    float3 tangent          = normalize( input.world_tangent.xyz );
    float3 normal           = normalize( input.world_normal );
    float3 bitangent        = normalize( cross( normal , tangent ) ) * input.world_tangent.w;
    float3x3 TBN            = float3x3( tangent, bitangent, normal );
    
    float4 normalColor = tNormal.Sample( sSampler , input.uv );
    float3 surfaceNormal = NormalColorToVector3( normalColor.xyz );
    float3 worldNormal = mul( surfaceNormal , TBN );
    
    float3 dirToSurface = normalize( input.world_position - CAMERA_POSITION );
    float dp = length( cross( dirToSurface , worldNormal ) );
    
    float factor = FRESNEL_FACTOR * pow( dp , FRESNEL_POWER * 16.0f + 15 * sin( SYSTEM_TIME_DELTASECONDS ) );
    return float4( FRESNEL_COLOR , factor );
}
