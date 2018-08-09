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
                float3 vertex : POSITION, // vertex position input
                float3 normal : NORMAL, // vertex position input
                float2 uv : TEXCOORD0 // first texture coordinate input
            )
            {
                v2f o;
                o.pos = mul(UNITY_MATRIX_VP, mul(unity_ObjectToWorld, float4(vertex + normal*0.01, 1)));
                o.uv = uv;
                return o;
            }

            struct fragOutput {
                fixed4 color : SV_Target0;
            };

            fragOutput frag(v2f i)
            {
                fragOutput o;
                o.color = fixed4(i.uv, 0.5, 0);
                return o;
            }
        ENDCG
        }
    }
}