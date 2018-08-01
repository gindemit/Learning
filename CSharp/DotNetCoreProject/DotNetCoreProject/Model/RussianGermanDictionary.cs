using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DotNetCoreProject.Model
{
    public sealed class RussianGermanDictionaryContext : DbContext
    {
        public DbSet<AndroidMetaData> AndroidMetaDatas { get; set; }
        public DbSet<Category> Categories { get; set; }
        public DbSet<CategoryName> CategoryNames { get; set; }
        public DbSet<CategoryWord> CategoryWords { get; set; }
        public DbSet<Word> Words { get; set; }
        public DbSet<WordCategory> WordCategories { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=ru_de_pro_dict.db");
        }
    }

    [Table("android_metadata")]
    public class AndroidMetaData
    {
        [Column("id")]
        public int Id { get; set; }
        [Column("locale")]
        public string Locale { get; set; }
    }

    [Table("category")]
    public class Category
    {
        [Key]
        [Column("id")]
        public int Id { get; set; }

        [Column("nameId")]
        public int NameId { get; set; }
    }

    [Table("categorynamen")]
    public class CategoryName
    {
        [Key]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; }
    }

    [Table("categorywoord")]
    public class CategoryWord
    {
        [Column("idWoord")]
        public int IdWord { get; set; }
        [Key]
        [Column("idCategory")]
        public int IdCategory { get; set; }
        [Column("Omschrijving")]
        public string Definition { get; set; }
        [Column("vooromschrijving")]
        public string Description { get; set; }
    }

    [Table("woord")]
    public class Word
    {
        [Key]
        [Column("id")]
        public int Id { get; set; }
        [Column("name")]
        public string Name { get; set; }
        [Column("deel")]
        public string Part { get; set; }

        public override string ToString()
        {
            return $"Id: {Id}, Name: {Name}, Part: {Part}";
        }
    }

    [Table("woordcategory")]
    public class WordCategory
    {
        [Key]
        [Column("idWoord")]
        public int IdWord { get; set; }
        [Column("idCategory")]
        public string IdCategory { get; set; }
    }
}
