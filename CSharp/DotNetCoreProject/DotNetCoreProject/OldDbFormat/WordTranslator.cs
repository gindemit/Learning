using System;
using System.Linq;
using DotNetCoreProject.Model;

namespace DotNetCoreProject.OldDbFormat
{
    internal class WordTranslator
    {
        RussianGermanDictionaryContext mDb;
        Cipher mCipher = new Cipher();

        public WordTranslator(RussianGermanDictionaryContext db)
        {
            mDb = db;
        }
        public void PrintTranslationToConsole(string wordStr)
        {
            var queryWord =
                from word in mDb.Words
                where word.Name == wordStr
                select word;

            foreach (var word in queryWord)
            {
                PrintCategories(word);
                Console.WriteLine();
            }
        }

        private void PrintCategories(Word word)
        {
            Console.WriteLine($"{word.Name}({word.Id}):");
            var queryWordIdCategory =
                from category in mDb.WordCategories
                where word.Id == category.IdWord
                select category.IdCategory;

            foreach (string idCategory in queryWordIdCategory)
            {
                PrintWordsPerCategory(idCategory);
            }
        }

        private void PrintWordsPerCategory(string idCategory)
        {
            string decryptedIdCategory = System.Text.Encoding.ASCII.GetString(mCipher.Decrypt(idCategory));

            int parsedIdCategory = int.Parse(decryptedIdCategory);
            //SELECT c.id, cn.name from category c join categorynamen cn on c.nameid=cn.id where c.id=
            var categoryQuery =
                from c in mDb.Categories
                join cn in mDb.CategoryNames on c.NameId equals cn.Id
                where c.Id == parsedIdCategory
                select new { Id = c.Id, Name = cn.Name };

            System.Diagnostics.Debug.Assert(categoryQuery.Count() == 1);
            int idIdCategory = categoryQuery.First().Id;
            string categoryName = categoryQuery.First().Name;
            Console.WriteLine("\t" + categoryName);

            var categoryWordQuery =
                from c in mDb.CategoryWords
                join w in mDb.Words on c.IdWord equals w.Id
                where c.IdCategory == idIdCategory
                select new { Definition = c.Definition, Description = c.Description, Name = w.Name, Part = w.Part };

            foreach (var categoryWordResult in categoryWordQuery)
            {
                Console.WriteLine($"\t\t{categoryWordResult.Name}, {categoryWordResult.Part}, {categoryWordResult.Definition}, {categoryWordResult.Description}");
            }
        }
    }
}   
