#include "collections.h"
typedef char* string;	

typedef struct{
	char author[50];
	char title[50];
	char publisher[50];
	char price[20];
	char isbn[25];
}Book;

typedef struct{
	char tag[100];
	char tagIsbn[25];
}Tag;

typedef struct{
	int count;
	Book *books;
	Tag *tags;
}BookCatalog;



BookCatalog createCatalog(int count);
void clearCatalog(BookCatalog catalog);
int count_total_number_of_books(string Filename);
void reduceExtraNewlineCharacter();
BookCatalog readTheTagsFromFile(BookCatalog catalog);

int areEqual(const string a, const string b);
string copyString(const string a, const string b);
void provideHelp(int numberOfArguments);
void giveExcuse();
void checkNumberOfArguments(int numberOfArguments);
void checkNumberOfArgumentsForSearch(int numberOfArguments);
void isFileNull(string fileName);
void correctFormatForAdd();
string reduceBlanks(string text);
void fieldAreEmptyForAdd();
void checkLastCharacter(string updatedBook);
string upper(char *str1);
string* allocateMemoryFor_result(string *result);
int isBookPersent(string isbn, BookCatalog catalog);
void isFormatOfStringCorrect(string addBook,string option);
void writeBookInFile(string book_to_be_added,BookCatalog catalog);
string decideFieldForSearch(BookCatalog catalog, string searching_option, int i, int argument);	
void printSearchedData(Book *result,int j);
void findThematches(BookCatalog catalog, Book *result, string searching_option, int argument, string fileldToBeSearched, string search_string);
void matchFields(string search_string, BookCatalog catalog, Book *result, string searching_option, int argument);
string* filterTheFileContents(BookCatalog catalog, string isbnNo,string fileName,string* storedLines);
void writeTheFilteredContents(string fileName, string* storedLines);
void putSemicollon();

BookCatalog read_contents_of_file(BookCatalog catalog);
int count_lines_of_file();
void addBook(string book_to_be_added, int argc, BookCatalog catalog);
void search_books_using_diffrent_fields(string searching_option,string search_string,BookCatalog catalog, int argument);
void copyFields(BookCatalog catalog, Book *result,int i);
void isBookPersentToDelete(string isbnNo,BookCatalog catalog);
void checkForTheIsbn(string option);
void delete_the_book_using_isbn(string option,string isbnNo, BookCatalog catalog, int argc);
void showListOfBooks(BookCatalog catalog, int argc);
void printAllBooks(BookCatalog catalog);
void checkNumberOfArgumentsOfList(int numberOfArguments);

void updateBook(string updatedBook,BookCatalog catalog, int argc);
Book updateTheFieldOfBook(string*bookPart,string*mainString,Book book1,int i);
string breakUptoCollon(string* bookPart,int i);
void formatOfUpdateBook();
void fieldsAreEmptyForUpdate();
int	numberOfGivenFields(string updatedBook);
void checkNumberOfArgumentsForUpdate(int numberOfArguments);
void checkNumberOfArgumentsForAddBook_and_updateBook(int numberOfArguments);
void checkNumberOfArgumentsForDelete(int numberOfArguments);

void addTag(string tagToBeAdded,BookCatalog catalog, int numberOfArguments);
void deleteTag(string tag_string,BookCatalog catalog,int numberOfArguments);
Tag copyDataInStructure(string* bookPart,string* mainString, Tag tag1,int i,BookCatalog catalog);



void deleteTagline(string tagToBeAdded,BookCatalog catalog, int numberOfArguments);
void deleteTag(string tagToBeAdded,BookCatalog catalog, int numberOfArguments);\
void checkNumberOfArgumentsForTag(int numberOfArguments);