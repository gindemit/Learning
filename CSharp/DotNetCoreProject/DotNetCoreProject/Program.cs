using System;
using System.Linq;
using DotNetCoreProject.Model;

namespace DotNetCoreProject
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var db = new RussianGermanDictionaryContext())
            {
                var testQuery =
                    from word in db.Words
                    where word.Id < 100
                    select word;

                foreach (var word in testQuery)
                {
                    Console.WriteLine(word);
                }
            }

            Console.ReadKey();
        }
    }
}   
