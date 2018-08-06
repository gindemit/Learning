Shader "Custom/Show UVs"
{
    SubShader
    {
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            struct v2f {
                float2 uv : TEXCOORD0;
                float4 pos : SV_POSITION;
            };

            v2f vert(
                float4 vertex : POSITION, // vertex position input
                float2 uv : TEXCOORD0 // first texture coordinate input
            )
            {
                v2f o;
                o.pos = mul(UNITY_MATRIX_VP, mul(unity_ObjectToWorld, float4(vertex.xyz, 1.0)));
                o.uv = uv;
                return o;
            }

            struct fragOutput {
                fixed4 color : SV_Target0;
                float depth : SV_Depth;
            };

            fragOutput frag(v2f i)
            {
                fragOutput o;
                o.color = fixed4(i.uv, 0.5, 0);
                o.depth = 10000;
                return o;
            }
        ENDCG
        }
    }
}