using Microsoft.EntityFrameworkCore.Migrations;

namespace DotNetCoreProject.Migrations.RuDeDict
{
    public partial class InitialCreate : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "android_metadata",
                columns: table => new
                {
                    id = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    locale = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_android_metadata", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "category",
                columns: table => new
                {
                    id = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    nameId = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_category", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "categoryName",
                columns: table => new
                {
                    idCategoryName = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    name = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_categoryName", x => x.idCategoryName);
                });

            migrationBuilder.CreateTable(
                name: "categoryWord",
                columns: table => new
                {
                    idWord = table.Column<int>(nullable: false),
                    idCategory = table.Column<int>(nullable: false),
                    definition = table.Column<string>(nullable: true),
                    description = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_categoryWord", x => new { x.idWord, x.idCategory });
                });

            migrationBuilder.CreateTable(
                name: "word",
                columns: table => new
                {
                    idWord = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    name = table.Column<string>(nullable: true),
                    partGenus = table.Column<int>(nullable: false),
                    plural = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_word", x => x.idWord);
                });

            migrationBuilder.CreateTable(
                name: "wordCategory",
                columns: table => new
                {
                    idCategory = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    idWord = table.Column<int>(nullable: false),
                    idCategoryName = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_wordCategory", x => x.idCategory);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "android_metadata");

            migrationBuilder.DropTable(
                name: "category");

            migrationBuilder.DropTable(
                name: "categoryName");

            migrationBuilder.DropTable(
                name: "categoryWord");

            migrationBuilder.DropTable(
                name: "word");

            migrationBuilder.DropTable(
                name: "wordCategory");
        }
    }
}
