#ifndef _TILERENDER
#define _TILERENDER

#include "value.fx"
#include "func.fx"

struct TileInfo
{
    float2 vLeftTop;
    float2 vSlice;
};

StructuredBuffer<TileInfo> g_TileInfo : register(t20);

#define ATLAS_TEX g_tex_0
#define LeftTop   g_vec2_0
#define Slice     

#define MAX_COL   g_int_1
#define MAX_ROW   g_int_2


struct VS_IN
{
    float3 vPos : POSITION; // Semantic, InputLayout   
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};

VS_OUT VS_TileRender(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
                
    
    _in.vPos.xy += float2(0.5f, -0.5f);    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV * float2(MAX_COL, MAX_ROW);
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    return output;
}


float4 PS_TileRender(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
     
    if (1 == g_int_0)
    {        
        int2 ColRow = (int2)floor(_in.vUV);
        float2 vSampleUV = frac(_in.vUV);       
        
        int idx = ColRow.y * MAX_COL + ColRow.x;        
        if (g_TileInfo[idx].vLeftTop.x == -1.f)
            vColor = float4(0.f, 0.f, 1.f, 1.f);
        else
            vColor = ATLAS_TEX.Sample(g_sam_1, g_TileInfo[idx].vLeftTop + (g_TileInfo[idx].vSlice * vSampleUV));
    }
    
    if (0.f == vColor.a)
        discard;
    
    
    // 광원처리   
    float3 vLightColor = (float3) 0.f;
    CalcLight2D(_in.vWorldPos, vLightColor);
   
    // 물체의 색상 * 광원색상 == 최종 색상
    vColor.rgb = vColor.rgb * vLightColor;
        
    return vColor;
}


#endif