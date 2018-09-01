using System.Linq;
using DotNetCoreProject.Shared;
using Old = DotNetCoreProject.Model;
using New = DotNetCoreProject.Model.New;


namespace DotNetCoreProject.Converter
{
    internal sealed class ToNewFormatConverterRuDe
    {
        private readonly Old.RussianGermanDictionaryContext mOldDb;
        private New.RuDeDictContext mNewDb;
        private readonly OldDbFormat.Cipher mCipher = new OldDbFormat.Cipher();

        public ToNewFormatConverterRuDe(Old.RussianGermanDictionaryContext oldDb, New.RuDeDictContext newDb)
        {
            mOldDb = oldDb;
            mNewDb = newDb;
        }

        public void MigrateWords()
        {
            int counter = 0;
            foreach (var oldWord in mOldDb.Words)
            {
                var newWord = new New.Word();
                newWord.Name = oldWord.Name.Trim();
                PartGenus partGenus;
                string plural;
                ParseAndFillPartGenusAndPlural(oldWord.Id, oldWord.Part, out partGenus, out plural);
                newWord.PartGenus = (int)partGenus;
                newWord.Plural = plural;
                mNewDb.Words.Add(newWord);

                counter++;
                if (counter == 25000)
                {
                    counter = 0;
                    mNewDb.SaveChanges();
                    mNewDb.Dispose();
                    mNewDb = new New.RuDeDictContext();
                    System.Console.WriteLine(oldWord.Id);
                }
            }
            mNewDb.SaveChanges();
        }

        public void MigrateCategoryNames()
        {
            foreach (var oldCategoryName in mOldDb.CategoryNames)
            {
                var newCategoryName = new New.CategoryName();
                newCategoryName.Name = oldCategoryName.Name;
                mNewDb.CategoryNames.Add(newCategoryName);
                mNewDb.SaveChanges();
                System.Diagnostics.Debug.Assert(oldCategoryName.Id == newCategoryName.IdCategoryName);
            }
        }

        public void MigrateWordCategories()
        {
            int fakeNewWordCategoryId = 0;

            int counter = 0;
            var oldWordCategoryQuery =
                from wc in mOldDb.WordCategories
                join w in mOldDb.Words on wc.IdWord equals w.Id
                select new { IdCategory = wc.IdCategory, IdWord = wc.IdWord, Part = w.Part, WordName = w.Name };

            foreach (var oldWordCategory in oldWordCategoryQuery)
            {
                string decryptedIdCategory = System.Text.Encoding.ASCII.GetString(mCipher.Decrypt(oldWordCategory.IdCategory));

                int oldParsedIdCategory = int.Parse(decryptedIdCategory);
                //SELECT c.id, cn.name from category c join categorynamen cn on c.nameid=cn.id where c.id=
                var oldCategoryQuery =
                    from c in mOldDb.Categories
                    where c.Id == oldParsedIdCategory
                    select new { Id = c.Id, CategoryNameId = c.NameId };

                if (oldCategoryQuery.Count() != 1)
                {
                    System.Console.WriteLine("Error: oldCategoryQuery.Count() != 1 " + oldParsedIdCategory + " " + oldWordCategory.IdCategory);
                }
                var oldCategory = oldCategoryQuery.First();

                var newWord = FindNewWord(oldWordCategory.IdWord, oldWordCategory.Part, oldWordCategory.WordName);

                var newWordCategory = new New.WordCategory();
                fakeNewWordCategoryId++;
                newWordCategory.IdCategory = fakeNewWordCategoryId;
                newWordCategory.IdCategoryName = oldCategory.CategoryNameId;
                newWordCategory.IdWord = newWord.IdWord;
                mNewDb.WordCategories.Add(newWordCategory);
                //mNewDb.SaveChanges();

                var oldCategoryWordQuery =
                    from c in mOldDb.CategoryWords
                    join w in mOldDb.Words on c.IdWord equals w.Id
                    where c.IdCategory == oldCategory.Id
                    select new { Definition = c.Definition, Description = c.Description, IdWord = w.Id, WordName = w.Name, Part = w.Part };


                foreach (var oldCategoryWord in oldCategoryWordQuery)
                {
                    var newTranslatedWord = FindNewWord(oldCategoryWord.IdWord, oldCategoryWord.Part, oldCategoryWord.WordName);

                    var newCategoryWord = new New.CategoryWord();
                    newCategoryWord.IdWord = newTranslatedWord.IdWord;
                    newCategoryWord.IdCategory = newWordCategory.IdCategory;

                    string oldCategoryWordDefinition = oldCategoryWord.Definition.Trim();
                    if (oldCategoryWordDefinition == "m" ||
                        oldCategoryWordDefinition == "f" ||
                        oldCategoryWordDefinition == "n")
                    {
                        newCategoryWord.Definition = string.Empty;
                    }
                    else
                    {
                        newCategoryWord.Definition = oldCategoryWordDefinition;
                    }
                    newCategoryWord.Description = oldCategoryWord.Description.Trim();

                    mNewDb.CategoryWords.Add(newCategoryWord);
                }
                counter++;
                if (counter == 5000)
                {
                    counter = 0;
                    mNewDb.SaveChanges();
                    if (newWordCategory.IdCategory != fakeNewWordCategoryId)
                    {
                        System.Console.WriteLine($"Error: fake word category id: {newWordCategory.IdCategory} != {fakeNewWordCategoryId}");
                    }
                    mNewDb.Dispose();
                    mNewDb = new New.RuDeDictContext();
                    System.Console.WriteLine(oldParsedIdCategory);
                }
            }
        }

        private New.Word FindNewWord(int oldIdWord, string oldWordPart, string oldWordName)
        {
            PartGenus partGenus;
            string plural;
            ParseAndFillPartGenusAndPlural(oldIdWord, oldWordPart, out partGenus, out plural);

            string oldCategoryWordName = oldWordName;
            var newWord = mNewDb.Words.Where(word => word.Name == oldCategoryWordName).FirstOrDefault();
            if (newWord == null || newWord.PartGenus != (int)partGenus || newWord.Plural != plural)
            {
                newWord = mNewDb.Words.SingleOrDefault(
                    word =>
                    (word.Name == oldCategoryWordName &&
                     word.PartGenus == (int)partGenus &&
                     word.Plural == plural));
            }
            if (newWord == null)
            {
                System.Console.WriteLine("Error: new word null!!! " + oldCategoryWordName);
            }
            return newWord;
        }

        private void ParseAndFillPartGenusAndPlural(int oldWordId, string oldWordPart, out PartGenus partGenus, out string plural)
        {
            string old = oldWordPart.Trim();

            partGenus = PartGenus.NoValue;
            plural = string.Empty;
            if (old.StartsWith("сущ. f"))
            {
                partGenus = PartGenus.NounFeminine;
                plural = old.Replace("сущ. f", string.Empty).Trim();
            }
            else if (old.StartsWith("сущ. m"))
            {
                partGenus = PartGenus.NounMasculine;
                plural = old.Replace("сущ. m", string.Empty).Trim();
            }
            else if (old.StartsWith("сущ. n"))
            {
                partGenus = PartGenus.NounNeuter;
                plural = old.Replace("сущ. n", string.Empty).Trim();
            }
            else if (old.StartsWith("сущ."))
            {
                partGenus = PartGenus.Noun;
                plural = old.Replace("сущ.", string.Empty).Trim();
            }
            else if (old.StartsWith("гл."))
            {
                partGenus = PartGenus.Verb;
            }
            else if (old.StartsWith("прил."))
            {
                partGenus = PartGenus.Adjective;
            }
            else if (old.StartsWith("нареч."))
            {
                partGenus = PartGenus.Adverb;
            }
            else if (old.StartsWith("сокр."))
            {
                partGenus = PartGenus.Abbreviation;
            }
            else if (old.StartsWith("мест."))
            {
                partGenus = PartGenus.Pronoun;
                plural = old.Replace("мест.", string.Empty).Trim();
            }
            else if (old.StartsWith("межд."))
            {
                partGenus = PartGenus.Interjection;
            }
            else if (old.StartsWith("предл."))
            {
                partGenus = PartGenus.Preposition;
            }
            else if (old.StartsWith("союз"))
            {
                partGenus = PartGenus.Joinder;
            }
            else if (old.StartsWith("числ."))
            {
                partGenus = PartGenus.Numeral;
            }
            else if (string.IsNullOrEmpty(old))
            {
                partGenus = PartGenus.NoValue;
                plural = string.Empty;
            }
            else
            {
                System.Console.WriteLine("Error ParseAndFillPartGenusAndPlural, word id: " + oldWordId);
            }
        }
    }
}
