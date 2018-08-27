using System;
using System.Threading;
using System.Globalization;

namespace DotNetCoreProject
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Thread.CurrentThread.CurrentUICulture = CultureInfo.GetCultureInfo("en-US");

            using (var db = new Model.New.RuDeDictContext())
            {
                NewDbFormat.WordTranslator translator = new NewDbFormat.WordTranslator(db);
                do
                {
                    Console.WriteLine("Enter word to translate");
                    string input = Console.ReadLine();
                    if (input == "q")
                    {
                        break;
                    }
                    translator.PrintTranslationToConsole(input);
                }
                while (true);
            }
        }
    }
}
