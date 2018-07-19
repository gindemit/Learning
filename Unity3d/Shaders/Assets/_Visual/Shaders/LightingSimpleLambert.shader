Shader "Custom/Lighting Simple Lambert"
{
    Properties
    {
        _Albedo("Albedo", Color) = (1,0,0,1)
    }
    SubShader
    {

        CGPROGRAM
        #pragma surface surf SimpleLambert

        half4 LightingSimpleLambert(SurfaceOutput s, half3 lightDir, half atten)
        {
            half NdotL = dot(s.Normal, lightDir);
            half4 c;
            c.rgb = s.Albedo * _LightColor0.rgb * (NdotL * atten);
            c.a = s.Alpha;
            return c;
        }

        struct Input
        {
            float4 color : COLOR;
        };

        float4 _Albedo;

        void surf(Input IN, inout SurfaceOutput o) {
            o.Albedo = _Albedo;
        }

        ENDCG
    }
    Fallback "Diffuse"
}