using System;
using System.Security.Cryptography;

namespace DotNetCoreProject
{
    internal sealed class Cipher
    {
        private readonly AesManaged mAesManaged;
        private readonly ICryptoTransform mDecryptor;

        public Cipher()
        {
            mAesManaged = new AesManaged();
            mAesManaged.Mode = CipherMode.CBC;
            mAesManaged.Padding = PaddingMode.None;

            byte[] key = System.Text.Encoding.ASCII.GetBytes("0123456789abcdef");
            mDecryptor = mAesManaged.CreateDecryptor(key, key);
        }

        public byte[] Decrypt(String paramString)
        {
            // 76158dabf1b299d167e416d6271089ef
            // [B@ad3dc89
            byte[] input = convertString(paramString);
            //Console.WriteLine(System.Text.Encoding.ASCII.GetString(input));
            return mDecryptor.TransformFinalBlock(input, 0, input.Length);
        }

        private static byte[] convertString(String paramString)
        {
            Object localObject = null;
            if (paramString == null) { }
            while (paramString.Length < 2)
            {
                return (byte[])localObject;
            }
            int j = paramString.Length / 2;
            byte[] arrayOfByte = new byte[j];
            int i = 0;
            for (; ; )
            {
                localObject = arrayOfByte;
                if (i >= j)
                {
                    break;
                }
                arrayOfByte[i] = ((byte)Convert.ToInt32(paramString.Substring(i * 2, 2), 16));
                i += 1;
            }
            return arrayOfByte;
        }
    }
}   
