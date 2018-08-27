using System;
using System.Linq;
using System.Net.Http;
using System.Collections.Generic;
using DotNetCoreProject.Model.New;
using HtmlAgilityPack;

namespace DotNetCoreProject.NewDbFormat
{
    internal sealed class DudenWordChecker
    {
        private static readonly HttpClient mHttpClient = new HttpClient();
        private readonly RuDeDictContext mDb;

        public DudenWordChecker(RuDeDictContext db)
        {
            mDb = db;
        }

        public void CheckWord(string wordStr)
        {
            var queryWord =
                from word in mDb.Words
                where word.Name == wordStr
                select word;

            foreach (var word in queryWord)
            {
                RequestDudenWord(word.Name);
            }
        }

        private async void RequestDudenWord(string name)
        {
            var responseString = await mHttpClient.GetStringAsync("https://www.duden.de/suchen/dudenonline/" + name);

            var htmlDoc = new HtmlDocument();
            htmlDoc.LoadHtml(responseString);


            var stage = htmlDoc.GetElementbyId("stage");
            var page = stage.OwnerDocument.GetElementbyId("page");
            var main = page.OwnerDocument.GetElementbyId("main");
            var content = main.OwnerDocument.GetElementbyId("content");
            var block_duden_tiles_0 = content.OwnerDocument.GetElementbyId("block-duden-tiles-0");
            foreach (var result in block_duden_tiles_0.ChildNodes)
            {
                Console.WriteLine(result.ChildNodes.Count());
                foreach (var resultChild in result.ChildNodes)
                {
                    Console.WriteLine("\t" + resultChild.ChildNodes.Count());
                }
            }
        }

        private async void Post()
        {
            var values = new Dictionary<string, string>
            {
               { "thing1", "hello" }
            };

            var content = new FormUrlEncodedContent(values);

            var response = await mHttpClient.PostAsync("http://www.example.com/recepticle.aspx", content);

            var responseString = await response.Content.ReadAsStringAsync();
        }

    }
}
