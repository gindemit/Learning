using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DotNetCoreProject.Model.New
{
    public sealed class RuDeDictContext : DbContext
    {
        public DbSet<AndroidMetaData> AndroidMetaDatas { get; set; }
        public DbSet<Category> Categories { get; set; }
        public DbSet<CategoryName> CategoryNames { get; set; }
        public DbSet<CategoryWord> CategoryWords { get; set; }
        public DbSet<Word> Words { get; set; }
        public DbSet<WordCategory> WordCategories { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Data Source=ru_de_dict.db");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Entity<CategoryWord>().HasKey(c => new { c.IdWord, c.IdCategory });
        }
    }

    [Table("word")]
    public class Word
    {
        [Key]
        [Column("idWord")]
        public int IdWord { get; set; }
        [Column("name")]
        public string Name { get; set; }
        [Column("partGenus")]
        public int PartGenus { get; set; }
        [Column("plural")]
        public string Plural { get; set; }

        public override string ToString()
        {
            return $"IdWord: {IdWord}, Name: {Name}, PartGenus: {PartGenus}, Plural: {Plural}";
        }
    }

    [Table("categoryName")]
    public class CategoryName
    {
        [Key]
        [Column("idCategoryName")]
        public int IdCategoryName { get; set; }

        [Column("name")]
        public string Name { get; set; }
    }

    [Table("wordCategory")]
    public class WordCategory
    {
        [Key]
        [Column("idCategory")]
        public int IdCategory { get; set; }
        [Column("idWord")]
        public int IdWord { get; set; }
        [Column("idCategoryName")]
        public int IdCategoryName { get; set; }
    }

    [Table("categoryWord")]
    public class CategoryWord
    {
        [Column("idWord")]
        public int IdWord { get; set; }
        [Column("idCategory")]
        public int IdCategory { get; set; }
        [Column("definition")]
        public string Definition { get; set; }
        [Column("description")]
        public string Description { get; set; }
    }
}
