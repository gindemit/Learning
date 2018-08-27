using System;
using System.Linq;
using DotNetCoreProject.Model.New;

namespace DotNetCoreProject.NewDbFormat
{
    internal class WordTranslator
    {
        RuDeDictContext mDb;

        public WordTranslator(RuDeDictContext db)
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
            Console.WriteLine($"{word.Name}({word.IdWord}):");
            var queryWordCategory =
                from category in mDb.WordCategories
                where word.IdWord == category.IdWord
                select new {
                    IdCategory = category.IdCategory,
                    IdCategoryName = category.IdCategoryName,
                    IdTranslatedWord = category.IdWord };

            foreach (var wordCategory in queryWordCategory)
            {
                var categoryQuery =
                from cn in mDb.CategoryNames
                where cn.IdCategoryName == wordCategory.IdCategoryName
                select new { IdCategory = wordCategory.IdCategory, CategoryName = cn.Name };

                System.Diagnostics.Debug.Assert(categoryQuery.Count() == 1);
                int idIdCategory = categoryQuery.First().IdCategory;
                string categoryName = categoryQuery.First().CategoryName;
                Console.WriteLine("\t" + categoryName);

                var categoryWordQuery =
                    from c in mDb.CategoryWords
                    join w in mDb.Words on c.IdWord equals w.IdWord
                    where c.IdCategory == idIdCategory
                    select new { Definition = c.Definition, Description = c.Description, Name = w.Name, PartGenus = w.PartGenus, Plural = w.Plural };

                foreach (var categoryWordResult in categoryWordQuery)
                {
                    Console.WriteLine($"\t\t{categoryWordResult.Name}, {(Shared.PartGenus)categoryWordResult.PartGenus}, {categoryWordResult.Plural}, {categoryWordResult.Definition}, {categoryWordResult.Description}");
                }
            }
        }
    }
}
