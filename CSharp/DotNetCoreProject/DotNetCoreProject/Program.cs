using System;
using System.Linq;
using System.Diagnostics;
using System.Collections.Generic;

using ConsoleApp.SQLite;

namespace DotNetCoreProject
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var db = new BloggingContext())
            {
                db.Blogs.Add(new Blog { Url = "http://blogs.msdn.com/adonet" });
                var count = db.SaveChanges();
                Console.WriteLine("{0} records saved to database", count);

                Console.WriteLine();
                Console.WriteLine("All blogs in database:");
                foreach (var blog in db.Blogs)
                {
                    Console.WriteLine(" - {0}", blog.Url);
                }
            }

            int[] numbers = new int[7] { 0, 1, 2, 3, 4, 5, 6 };

            IEnumerable<int> query =
                from num in numbers
                where (num % 2) == 0
                select num;

            foreach (int num in query)
            {
                Console.Write("{0,1} ", num);
            }


            Console.ReadKey();
        }
    }
}
