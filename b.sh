gcc -c collections.c bookCatalog.c bookshop.c
gcc -o bookshop.exe bookshop.o bookCatalog.o collections.o
gcc -c bookCatalogTest.c collectionsTest.c