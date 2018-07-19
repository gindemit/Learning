Shader "Custom/Test Shader"
{
    Properties
    {
        _Albedo("Albedo", Color) = (1,0,0,1)
    }
    SubShader
    {

        CGPROGRAM

        #pragma surface surf SimpleSpecular

        half4 LightingSimpleSpecular(SurfaceOutput s, half3 lightDir, half3 viewDir, half atten)
        {
            half3 h = normalize(lightDir + viewDir);

            half diff = max(0, dot(s.Normal, lightDir));

            float nh = max(0, dot(s.Normal, h));
            float spec = pow(nh, 48);

            half4 c;
            c.rgb = (s.Albedo * _LightColor0.rgb * diff + _LightColor0.rgb * spec) * atten;
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