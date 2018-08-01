using Microsoft.EntityFrameworkCore.Migrations;

namespace DotNetCoreProject.Migrations
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
                name: "categorynamen",
                columns: table => new
                {
                    id = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    name = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_categorynamen", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "categorywoord",
                columns: table => new
                {
                    idWoord = table.Column<int>(nullable: false),
                    idCategory = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Omschrijving = table.Column<string>(nullable: true),
                    vooromschrijving = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_categorywoord", x => x.idCategory);
                });

            migrationBuilder.CreateTable(
                name: "woord",
                columns: table => new
                {
                    id = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    name = table.Column<string>(nullable: true),
                    deel = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_woord", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "woordcategory",
                columns: table => new
                {
                    idWoord = table.Column<int>(nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    idCategory = table.Column<string>(nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_woordcategory", x => x.idWoord);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "android_metadata");

            migrationBuilder.DropTable(
                name: "category");

            migrationBuilder.DropTable(
                name: "categorynamen");

            migrationBuilder.DropTable(
                name: "categorywoord");

            migrationBuilder.DropTable(
                name: "woord");

            migrationBuilder.DropTable(
                name: "woordcategory");
        }
    }
}
