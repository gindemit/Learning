using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ComputeShaderExample : MonoBehaviour
{
    [SerializeField]
    private ComputeShader computeShader;


    public RenderTexture result;

    private void Start()
    {
        if (SystemInfo.supportsComputeShaders)
        {
            result = new RenderTexture(512, 512, 24);
            result.enableRandomWrite = true;
            result.Create();

            int kernel = computeShader.FindKernel("CSMain");
            computeShader.SetTexture(kernel, "Result", result);
            computeShader.Dispatch(kernel, 512 / 8, 512 / 8, 1);
        }
        else
        {
            Debug.LogError("Compute shaders are not supported");
        }
    }
}
