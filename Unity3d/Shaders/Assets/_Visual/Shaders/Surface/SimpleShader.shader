Shader "Custom/SimpleShader"
{
    Properties
    {
        _Albedo("Albedo", Color) = (1, 1, 1, 1)
        _Emission("Emission", Color) = (0, 0, 0, 0)
    }
        SubShader
    {
        Tags{ "RenderType" = "Lambert" }
        CGPROGRAM
        #pragma surface surf Lambert

        struct Input
        {
            float4 color : COLOR;
        };
        float3 _Albedo;
        float3 _Emission;

        void surf(Input IN, inout SurfaceOutput o)
        {
            o.Albedo = _Albedo;
            o.Emission = _Emission;
        }

        ENDCG
    }
        Fallback "Diffuse"
}