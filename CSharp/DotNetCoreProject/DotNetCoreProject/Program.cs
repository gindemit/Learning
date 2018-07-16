using System;
using System.Diagnostics;

namespace DotNetCoreProject
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start stop watch...");
            Stopwatch sw = new Stopwatch();
            sw.Start();

            int test = 0;
            for (int i = 0; i < 2000000000; i++)
            {
                test++;
            }

            Console.WriteLine("Elapsed: " + sw.ElapsedMilliseconds + ", " + test);
            Console.ReadKey();
        }
    }
}
