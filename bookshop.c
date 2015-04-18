#include <stdio.h>
#include "bookCatalog.h"

int main(int argc, char *argv[]){
	BookCatalog catalog;
	string operation=argv[1];
	checkNumberOfArguments(argc);
	catalog = createCatalog(count_lines_of_file());
	
	if(areEqual(upper(operation),"TAGS"))TagOperations(argv[2],argv[3],catalog,argc);
	else if(areEqual(upper(operation),"ADD"))addBook(argv[2], argc, catalog);
	else if(areEqual(upper(operation), "LIST"))showListOfBooks(catalog, argc);
	else if(areEqual(upper(operation),"SEARCH"))search_books_using_diffrent_fields(argv[2], argv[3], catalog, argc);
	else if(areEqual(upper(operation),"REMOVE")){delete_the_book_using_isbn( argv[2],argv[3], catalog, argc);printf("book is deleted\n");}
	else if(areEqual(upper(operation), "UPDATE"))updateBook(argv[2], catalog, argc);
	else if(areEqual(upper(operation), "--HELP"))provideHelp(argc);
	else giveExcuse();
	clearCatalog(catalog);
	return 0;
}