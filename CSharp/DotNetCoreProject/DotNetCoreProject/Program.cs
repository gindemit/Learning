using System;
using System.Linq;
using System.Collections.Generic;
using DotNetCoreProject.Model;

namespace DotNetCoreProject
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var db = new RussianGermanDictionaryContext())
            {
                WordTranslator translator = new WordTranslator(db);
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
