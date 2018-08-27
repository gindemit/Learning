using System;
using System.Collections.Generic;
using System.Linq;
using DotNetCoreProject.Model;

namespace DotNetCoreProject.OldDbFormat
{
    internal sealed class AlphabetBuilder
    {
        RussianGermanDictionaryContext mDb;
        Cipher mCipher = new Cipher();
        Dictionary<char, int> mChars = new Dictionary<char, int>(128);

        public AlphabetBuilder(RussianGermanDictionaryContext db)
        {
            mDb = db;
        }
        public void BuildAlphabet()
        {
            var queryWord =
                from word in mDb.Words
                select word;

            foreach (var word in queryWord)
            {
                GetCategories(word);
            }
            PrintResult();
        }

        private void PrintResult()
        {
            Console.WriteLine("Result:");
            foreach (var result in mChars)
            {
                Console.WriteLine(result.Key + " - " + result.Value);
            }
        }

        private void GetCategories(Word word)
        {
            var queryWordIdCategory =
                from category in mDb.WordCategories
                where word.Id == category.IdWord
                select category.IdCategory;

            foreach (string idCategory in queryWordIdCategory)
            {
                GetWordsPerCategory(idCategory);
            }
        }

        private void GetWordsPerCategory(string idCategory)
        {
            string decrypted = System.Text.Encoding.ASCII.GetString(mCipher.Decrypt(idCategory));

            var categoryQuery =
                from c in mDb.Categories
                join cn in mDb.CategoryNames on c.NameId equals cn.Id
                where c.Id == int.Parse(decrypted)
                select new { Id = c.Id, Name = cn.Name };

            System.Diagnostics.Debug.Assert(categoryQuery.Count() == 1);
            int idCategoryInt = categoryQuery.First().Id;
            string categoryName = categoryQuery.First().Name;

            var categoryWordQuery =
                from c in mDb.CategoryWords
                join w in mDb.Words on c.IdWord equals w.Id
                where c.IdCategory == idCategoryInt
                select new { Definition = c.Definition, Description = c.Description, Name = w.Name, Part = w.Part };

            foreach (var categoryWordResult in categoryWordQuery)
            {
                foreach (char character in categoryWordResult.Name)
                {
                    int count;
                    if (mChars.TryGetValue(character, out count))
                    {
                        mChars[character] = count + 1;
                    }
                    else
                    {
                        mChars.Add(character, 1);
                    }
                }
            }
        }
    }
}
