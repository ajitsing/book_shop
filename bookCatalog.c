#include "bookCatalog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char fileName[] = "BooksInventory.txt";	//BooksInventory.txt  testInventory.txt

BookCatalog createCatalog(int count){
	BookCatalog* c = (BookCatalog*)malloc(sizeof(BookCatalog));
	c->count = count;
	c->books = (Book*)malloc(count*sizeof(Book));
	c->tags = (Tag*)malloc(countTheTaggedBooks()*sizeof(Tag));
	return *c;
}

void clearCatalog(BookCatalog catalog){
	free(catalog.books);
	catalog.books=NULL;
	catalog.count = 0;
}

int areEqual(const string a, const string b){
	return strcmp(a,b) == 0;
}

string copyString(const string a, const string b){
	return strcpy(a,b);
}

void helpForAdd(){
	printf("CORRECT USE OF \"add\" FUNCTION IS\n________________________________\nbookshop add \"isbn:1234567890;price:200;author:chetan Baghat;title:Revolution 2020;publisher:Bharat Publication\"\nbookshop add \"isbn:1234567890\"\n***only ISBN is mandatory\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForSearch(){
	printf("CORRECT USE OF \"search\" FUNCTION IS\n__________________________________\navailable options are:-\n-isbn\n-author\n-title\n-publisher\n\nbookshop search <option> \"1234567890\"\nsearch without option===>\n\nbookshop search \"1234567890\"\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForList(){
	printf("CORRECT USE OF \"list\" FUNCTION IS\n__________________________________\nbookshop list\nit will show the list of available books\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForUpdate(){
	printf("CORRECT USE OF \"update\" FUNCTION IS\n__________________________________\nbookshop update \"isbn:1234567890;price:300;publisher:Bharat Publication\"\nit will update the price of the available book\n***ISBN is mandatory\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForDelete(){
	printf("CORRECT USE OF \"remove\" FUNCTION IS\n__________________________________\nbookshop remove -isbn \"1234567890\"\nit will delete the available book\n***can delete only using ISBN\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForAddTag(){
printf("CORRECT USE OF \"tags add\" FUNCTION IS\n______________________________________\nbookshop tags add \"isbn:1234567890;tag:story\"\nit will tag the book\n***ISBN  And Tag both are mandatory \n____><____\t\t\t  ____><____\t\t\t____><____\n\n");
}

void helpForRemoveTag(){
printf("CORRECT USE OF \"tags remove\" FUNCTION IS\n________________________________________\nbookshop tags remove \"isbn:1234567890;tag:story\"\nit will remove the tag of book\n***ISBN  And Tag both are mandatory\n____><____\t\t\t  ____><____\t\t\t____><____\n\n");	
}

void helpForTag(){
	printf("\nCORRECT USE OF \"tags\" FUNCTION IS\n__________________________________\n\n\n\n");
	helpForAddTag();   helpForRemoveTag();  exit(1);
}

void provideHelp(int numberOfArguments){
	if(numberOfArguments!=2){printf("===>Syntax is incorrect write bookshop --help");exit(1);}
	helpForAdd();  helpForUpdate();  helpForSearch();  helpForList();  helpForDelete(); helpForTag();
}

void formatForAddTag(){
	helpForAddTag();
	exit(1);
}

void giveExcuse(){
	printf("===>To learn the correct usage type bookshop --help\n");
}

void checkNumberOfArguments(int numberOfArguments){
	if(numberOfArguments == 1){ giveExcuse();  exit(1); }
}


				/*oprations*/


void addBook(string book_to_be_added, int argc, BookCatalog catalog){
	checkNumberOfArgumentsForAddBook_and_updateBook(argc);
	book_to_be_added = reduceBlanks(book_to_be_added);
	isFormatOfStringCorrect(book_to_be_added,"add");
	writeBookInFile(book_to_be_added,catalog);
	reduceExtraNewlineCharacter(fileName);
	printf("===>Book added sucessfully\n");
}

void search_books_using_diffrent_fields(string searching_option,string search_string,
	BookCatalog catalog, int argument){
	Book *result = (Book*)malloc( sizeof(Book));
	checkNumberOfArgumentsForSearch(argument);
	matchFields(search_string, catalog, result,searching_option, argument);
	free(result);	
}

void delete_the_book_using_isbn(string option, string isbnNo, BookCatalog catalog, int argc){
	int totalLines = count_lines_of_file();
	string storedLines[totalLines];
	checkNumberOfArgumentsForDelete(argc);
	checkForTheIsbn(option);
	isFileNull(fileName);
	isBookPersentToDelete(isbnNo,catalog);
	filterTheFileContents(catalog, isbnNo,fileName,storedLines);
	writeTheFilteredContents(fileName, storedLines);
	reduceExtraNewlineCharacter(fileName);
}

void showListOfBooks(BookCatalog catalog, int argc){
	checkNumberOfArgumentsOfList(argc);
	read_contents_of_file(catalog);
	printAllBooks(catalog);
}

void TagOperations(string operation,string tag_string,BookCatalog catalog,int numberOfArguments){
	checkNumberOfArgumentsForTag(numberOfArguments);
	if(areEqual(upper(operation),"ADD")){addTag(tag_string,catalog, numberOfArguments); printf("===>Book is tagged\n");}  
	else if(areEqual(upper(operation),"REMOVE")){deleteTag(tag_string,catalog,numberOfArguments); printf("===>Tag removed\n");}
	else helpForTag();
}




			/*fuctions used in oprations*/


			/*functions for addBook*/

void checkNumberOfArgumentsForAddBook_and_updateBook(int numberOfArguments){
	if(numberOfArguments != 3){ helpForAdd(); printf("===>Use --help for more help"); exit(1); }
}

string* allocateMemoryFor_result(string *result){
	int i=0;
	result = (string*)malloc(sizeof(string)*5);
	for (i = 0; i < 5; ++i){ result[i]=(string)malloc(sizeof(char)*100); }
	return result;
}

void freeTheResult(string *result){
	int i=0;
	for (i = 0; i < 5; ++i){ free(result[i]); }
	free(result);
}

string reduceBlanks(string text){
	char character,prev_character;
	string temp = (string)malloc(strlen(text));
	int i=0,spaces = 0,k=0;
	while(text[i] != '\0'){
		character=text[i];
		if(character != ' '){temp[k]=character;spaces = 0;k++;}
		else{if(spaces == 0 && prev_character!= ':' && prev_character!= ';' && prev_character!= ' '){temp[k]=' ';spaces++;k++;}}
		prev_character = character;
		i++;
	}
	temp[k] = '\0';
	copyString(text,temp);
	free(temp);
	return text;
}

void printCorrectFormat(string option){
	if (areEqual(option,"add"))correctFormatForAdd(); 
	else if(areEqual(option,"update")) formatOfUpdateBook();
	else if(areEqual(option,"tags add")){helpForAddTag(); exit(1);}
	else if(areEqual(option,"tags remove")){helpForRemoveTag(); exit(1);}
	else giveExcuse();
}

void isFormatOfStringCorrect(string addBook,string option){
	int semi_count=0,colon_count=0;
	int length = strlen(addBook);
	char prev_character,semicolon = ';',colon = ':';
	if(addBook[length-1] == semicolon)printCorrectFormat(option);
	while(*addBook != '\0'){
		if(*addBook == semicolon){	semi_count++; if(*addBook == prev_character)printCorrectFormat(option); }	
		if(*addBook == colon){	colon_count++; if(*addBook == prev_character)printCorrectFormat(option); }
		if((prev_character == semicolon) && (*addBook == colon))printCorrectFormat(option);
		prev_character = *addBook;
		addBook++;
	}
	if(colon_count != semi_count+1)printCorrectFormat(option);
}

int isBookPersent(string isbn, BookCatalog catalog){
	int i, lines= count_lines_of_file(); 
	read_contents_of_file(catalog);
	for (i = 0; i <= lines; i++){ if(areEqual(isbn, catalog.books[i].isbn))return 1; }
	return 0;
}

			/*functions for write the file*/

Book checkIsbnForAdd(Book book1, string* mainString, int i,BookCatalog catalog){
   if(areEqual(mainString[i]," ") || areEqual(mainString[i],"") || areEqual(mainString[i],"\t")){printf("===>Give correct value in isbn\n");exit(1);}
   if(isBookPersent(mainString[i], catalog)){printf("===>Book is already available\n");exit(1);}
   strcpy(book1.isbn,mainString[i]);strcat(book1.isbn,";");
   return book1;
}

Book copyDataInFields(string*mainString,string*bookPart,Book book1,int i){
    if(areEqual(mainString[i],""))fieldsAreEmptyForUpdate();
    if(strstr(bookPart[i],"price")){strcpy(book1.price,mainString[i]);}
	if(strstr(bookPart[i],"author")){strcpy(book1.author,mainString[i]);}
	if(strstr(bookPart[i],"title")){strcpy(book1.title,mainString[i]);}
	if(strstr(bookPart[i],"publisher")){strcpy(book1.publisher,mainString[i]);}
	return book1;
}

string* splitedString(string*mainString,string*bookPart,string result,string temp,int i){
	sscanf(result,"%[^;]",bookPart[i]);
	temp= strpbrk(bookPart[i],":");temp++;
	strcpy(mainString[i],temp);
	return mainString;
}

void checkForNullFieldsAndAddTheBook(Book book1){
	FILE*filepointer;
	filepointer = fopen(fileName,"a");
	if(areEqual(book1.isbn,"no")){printf("===>ISBN is missing\n");exit(1);}
	if(areEqual(book1.price, "no"))strcpy(book1.price," ;");else strcat(book1.price,";");
	if(areEqual(book1.author, "no"))strcpy(book1.author," ;");else strcat(book1.author,";");
	if(areEqual(book1.title, "no"))strcpy(book1.title," ;");else strcat(book1.title,";");
	if(areEqual(book1.publisher, "no"))strcpy(book1.publisher," ");
	fprintf(filepointer, "\n%s%s%s%s%s",book1.isbn,book1.price,book1.author,book1.title,book1.publisher);
	fclose(filepointer);
}

Book performOpretionOnbookToBeAdded(string result,string temp,string delims,string*mainString,string*bookPart,Book book1,BookCatalog catalog){
	int i=0;
	while( result != NULL ){
		mainString = splitedString(mainString,bookPart,result,temp,i);
    	result = strtok( NULL, delims );
		if(strstr(upper(bookPart[i]), "ISBN"))book1=checkIsbnForAdd(book1,mainString,i,catalog);    	
		book1 = updateTheFieldOfBook(bookPart,mainString,book1,i);  	
   		i++;
	}
	return book1;
}

void writeBookInFile(string book_to_be_added,BookCatalog catalog){
	int i=0,j=0,lines,numberOfFields = numberOfGivenFields(book_to_be_added); 	   
	Book book1 = {"no","no","no","no","no"};
	string *mainString,*bookPart,result = NULL,temp,delims = ";";
	mainString = allocateMemoryFor_result(mainString);
	bookPart = allocateMemoryFor_result(bookPart);
	result = strtok( book_to_be_added, delims);
	book1 = performOpretionOnbookToBeAdded(result,temp,delims,mainString,bookPart,book1,catalog);
	checkForNullFieldsAndAddTheBook(book1);
	freeTheResult(mainString);
	freeTheResult(bookPart);
}

void putSemicolon(){
	FILE* filepointer;
	filepointer = fopen(fileName,"a");
	fprintf(filepointer, "%c",';');
	fclose(filepointer);
}

void correctFormatForAdd(){
	helpForAdd();  printf("===>Use \"--help\" for more help");  exit(1);
}

void fieldAreEmptyForAdd(){
	printf("===>some of the fileds are empty\n");  exit(1);
}




			/*functions used for search*/



void checkNumberOfArgumentsForSearch(int numberOfArguments){
	if(numberOfArguments < 3 || numberOfArguments > 4){ helpForSearch();  exit(1); }
}

void checkNumberOfArgumentsForTag(int numberOfArguments){
	if( numberOfArguments < 3 )helpForTag();
}

string decideFieldForSearch(BookCatalog catalog, string searching_option, int i, int argument){
	string fileldToBeSearched,resultant;
	int j=0;
	if(areEqual(upper(searching_option),"-AUTHOR"))fileldToBeSearched = catalog.books[i].author;
	else if(areEqual(upper(searching_option),"-TITLE"))fileldToBeSearched = catalog.books[i].title; 
	else if(areEqual(upper(searching_option),"-PUBLISHER"))fileldToBeSearched = catalog.books[i].publisher;
	else if(areEqual(upper(searching_option),"-TAG")){}
	else if(areEqual(upper(searching_option),"-ISBN")){}
	else{helpForSearch();  exit(1); }
	return fileldToBeSearched;
}

void printSearchedDataWithTag(Tag *tagResult,BookCatalog catalog,int j,int i){
	printf("%-12s %-5s %-18s %-45s %-35s %-s\n",catalog.books[i].isbn,catalog.books[i].price,catalog.books[i].author,catalog.books[i].title,catalog.books[i].publisher,tagResult[j].tag );
}

void CheckTagAndPrintTheBook(BookCatalog catalog,string search_string,int i){
	int flag,j=0;
	for (j = 0; j < countTheTaggedBooks() ; j++){
		if(areEqual(catalog.tags[j].tagIsbn,search_string)){
			printSearchedDataWithTag(catalog.tags,catalog,j,i);
			flag = 1;
			break;
		}
		flag = 0;
	}
	if(flag == 0)printSearchedData(catalog.books,i);
}

void copyFields(BookCatalog catalog, Book *result,int i){
	int j=0;
	copyString(result[j].isbn,catalog.books[i].isbn);
	copyString(result[j].author,catalog.books[i].author);
	copyString(result[j].title,catalog.books[i].title);
	copyString(result[j].price,catalog.books[i].price);
	copyString(result[j].publisher,catalog.books[i].publisher);
	j++;
}

void matchByIsbn(BookCatalog catalog, string search_string){
	int i=0;
	for (i = 0; i < count_lines_of_file(); ++i){
		if(areEqual(catalog.books[i].isbn, search_string)){
			CheckTagAndPrintTheBook(catalog,search_string,i);
		}
	}
}

void matchByTags(BookCatalog catalog,string search_string){
	int i,flag=0;
	for (i = 0; i < countTheTaggedBooks() ; i++){
		if(areEqual(upper(strdup(catalog.tags[i].tag)),upper(search_string))){matchByIsbn(catalog,catalog.tags[i].tagIsbn); flag =1;}
	}
	if(flag == 0)exit(1);
}

void matchFields(string search_string, BookCatalog catalog, Book *result, string searching_option, int argument){
	int i=0;
	string fileldToBeSearched;
	read_contents_of_file(catalog);
	if(argument==4)decideFieldForSearch(catalog,searching_option,i,argument);
	printf("ISBN\t    Price\tAuthor\t\t\tTitle \t\t\t\t\tPublisher\t\t\tTag\n\n");
	if(argument==4 && areEqual(upper(searching_option),"-ISBN")){matchByIsbn(catalog,search_string); exit(1);}
	if(argument==4 && areEqual(upper(searching_option),"-TAG")){matchByTags(catalog,search_string); exit(1);}
	findThematches(catalog, result, searching_option, argument, fileldToBeSearched, search_string);
}

void mathByfieldOption(BookCatalog catalog, Book *result, string searching_option, int argument, string fileldToBeSearched, string search_string,int i,int j){
	fileldToBeSearched = decideFieldForSearch(catalog, searching_option, i, argument); 
	if(strstr(upper(strdup(fileldToBeSearched)),upper(search_string))){
		copyFields(catalog,result,i);
		CheckTagAndPrintTheBook(catalog,catalog.books[i].isbn,i);		
	}
}

void mathByAllFields(BookCatalog catalog, Book *result, string searching_option, string search_string,int i,int j){
	if(strstr(upper(strdup(catalog.books[i].author)),upper(searching_option)) || areEqual(upper(strdup(catalog.books[i].isbn)),upper(searching_option)) || 
		strstr(upper(strdup(catalog.books[i].title)),upper(searching_option)) || strstr(upper(strdup(catalog.books[i].publisher)),upper(searching_option))){
		copyFields(catalog,result,i);
		CheckTagAndPrintTheBook(catalog,catalog.books[i].isbn,i);		
	}
}

void findThematches(BookCatalog catalog, Book *result, string searching_option, int argument, string fileldToBeSearched, string search_string){
	int i,j=0,counter = count_lines_of_file();
	for (i = 0; i < counter; ++i){
		if(argument == 4)mathByfieldOption(catalog, result, searching_option, argument,fileldToBeSearched, search_string,i,j);
		else if(argument == 3)mathByAllFields(catalog, result, searching_option,search_string,i,j);
	}
	if(argument == 3)matchByTags(catalog,searching_option);
	else matchByIsbn(catalog,catalog.tags[i].tagIsbn); 
}

void printSearchedData(Book *result,int j){
	printf("%-12s %-5s %-18s %-45s %-35s\n",result[j].isbn,result[j].price,result[j].author,result[j].title,result[j].publisher);
}

string upper(char *str1){
	int i=0,length= strlen(str1);
	char *name = (string)malloc( sizeof(char)*length+1);
	while(i<length){
        str1[i] = toupper(str1[i]);          
   		i++;
    }
    str1[i+1] == '\0';
    strcpy(name,str1);
    return name;
}


			/*functions used for deleteBook*/

void checkNumberOfArgumentsForDelete(int numberOfArguments){
	if(numberOfArguments != 4){ helpForDelete(); exit(1); }
}

void isFileNull(string fileName){
	FILE* filepointer=fopen(fileName,"r");
	if ( filepointer == NULL ){ printf( "===>Could not open file\n" ); fclose(filepointer); exit(1); }
}

void checkForTheIsbn(string option){
	if(!areEqual(upper(option), "-ISBN")){ printf("===>The given field is not correct\nField should be  -isbn"); exit(1); }
}

void isBookPersentToDelete(string isbnNo,BookCatalog catalog){
	if(areEqual(isbnNo,"") || areEqual(isbnNo," ")){printf("===>Give a correct ISBN\n");exit(1);}
	if(!isBookPersent(isbnNo, catalog)){ printf("===>book is not available\n"); exit(1); }
}

string* filterTheFileContents(BookCatalog catalog, string isbnNo,string fileName,string* storedLines){
	char buffer[200],number[100];
	int i=0;
	FILE* filepointer = fopen(fileName,"r");
	while(!feof(filepointer)){
		read_contents_of_file(catalog);
		fgets(buffer, 150, filepointer);
		sscanf(buffer,"%[^;];",number);
		if(areEqual(number, isbnNo))copyString(buffer,"");
		storedLines[i]=(char*)malloc(sizeof(char)*strlen(buffer)+20);
		copyString(storedLines[i],buffer);
		i++;
	}		
	fclose(filepointer);	
	return storedLines;
}

void writeTheFilteredContents(string fileName, string* storedLines){
	FILE *filepointer;
	int j=0,totalLines = count_lines_of_file();
	filepointer = fopen(fileName,"w");
	for (j = 0; j < totalLines; j++){fprintf(filepointer,"%s", storedLines[j]);}
	fclose(filepointer);	
}



			/*functions for list*/

void checkNumberOfArgumentsOfList(int numberOfArguments){
	if(numberOfArguments != 2){	helpForList();  exit(1); }
}

void printAllBooks(BookCatalog catalog){
	int i,j,flag;
	printf("ISBN\t    Price\tAuthor\t\t\tTitle \t\t\t\t\tPublisher\t\t\tTag\n\n");
	for (i = 0; i < count_lines_of_file(); i++){
		read_contents_of_file(catalog);
		for (j = 0; j < countTheTaggedBooks(); j++){
			if(areEqual(catalog.books[i].isbn,catalog.tags[j].tagIsbn)){
				printf("%-12s %-5s %-18s %-45s %-35s %-s\n",catalog.books[i].isbn,catalog.books[i].price,catalog.books[i].author,
				catalog.books[i].title,catalog.books[i].publisher,catalog.tags[j].tag );
				flag = 0;
				break;
			}
			flag = 1;
		}
		if(flag == 1){
			printf("%-12s %-5s %-18s %-45s %-50s\n",catalog.books[i].isbn,catalog.books[i].price,catalog.books[i].author,
			catalog.books[i].title,catalog.books[i].publisher );
		}
	}
}



			/*common functions*/

int count_lines_of_file(){
	int counter=0;
	char character,temp[250];
	FILE *filepointer;
	filepointer=fopen(fileName,"r");
	while(!feof(filepointer)){ fgets(temp,200,filepointer); counter++; }
	fclose(filepointer);
	return counter;
}

BookCatalog read_contents_of_file(BookCatalog catalog){
	FILE*filepointer=fopen(fileName,"r");
	int i=0;
	char temp[100];
	isFileNull(fileName);
	catalog = readTheTagsFromFile(catalog);
	while(!feof(filepointer)){
		fscanf(filepointer," %[^;];%[^;];%[^;];%[^;];%[^\n]",catalog.books[i].isbn,catalog.books[i].price,
			catalog.books[i].author,catalog.books[i].title,catalog.books[i].publisher);
		i++;
	} 
	fclose(filepointer);
	return catalog;
}

		/*functions for update*/

string breakUptocolon(string* bookPart,int i){
	int k=0;
	string field = (string)malloc(strlen(bookPart[i]));
	while(*bookPart[i] != ':'){
		field[k] = *bookPart[i]; 
		*bookPart[i]++;
		k++;
	}
	field[k] = '\0';
	return field;
}

Book updateTheFieldOfBook(string*bookPart,string*mainString,Book book1,int i){
	if(areEqual(mainString[i],""))fieldsAreEmptyForUpdate();
	bookPart[i] = breakUptocolon(bookPart, i);
    if(areEqual(upper(bookPart[i]),"PRICE"))strcpy(book1.price,mainString[i]);
	else if(areEqual(upper(bookPart[i]),"AUTHOR"))strcpy(book1.author,mainString[i]);
	else if(areEqual(upper(bookPart[i]),"TITLE"))strcpy(book1.title,mainString[i]);
	else if(areEqual(upper(bookPart[i]),"PUBLISHER"))strcpy(book1.publisher,mainString[i]);
	else if(areEqual(upper(bookPart[i]),"ISBN")){}
	else{printf("===>Spelling of the given field [ %s ] is not correct\nuse bookshop --help for help",bookPart[i]);exit(1);}
	return book1;
}

void writeTheUpdatedDataInFile(string option,Book book1,BookCatalog catalog){
	FILE*filepointer;
	delete_the_book_using_isbn(option, book1.isbn, catalog, 4);
	filepointer = fopen(fileName,"a");
	fprintf(filepointer, "\n%s;%s;%s;%s;%s", book1.isbn,book1.price,book1.author,book1.title,book1.publisher);
	fclose(filepointer);
}

Book performOpretionOnFieldsToBeUpdated(string*mainString,string*bookPart,BookCatalog catalog,Book book1,string updatedBook){
	int i = 0;
	char delims[] = ";";
	string temp,result = NULL;
	result = strtok( updatedBook, delims );
	while( result != NULL ) {
		mainString = splitedString(mainString,bookPart,result,temp,i);
    	result = strtok( NULL, delims );
		book1 = updateTheFieldOfBook(bookPart,mainString,book1,i);
   		i++;
	}
	if(areEqual(book1.isbn,"")){helpForUpdate();exit(1);}
	return book1;
}

Book loadBook(BookCatalog catalog,Book book1,string temp){
	int j;
	for (j = 0; j < count_lines_of_file(); ++j){
		if(areEqual(catalog.books[j].isbn,temp)) {strcpy(book1.isbn,catalog.books[j].isbn); strcpy(book1.price,catalog.books[j].price); strcpy(book1.author,catalog.books[j].author); 
			strcpy(book1.title,catalog.books[j].title);  strcpy(book1.publisher,catalog.books[j].publisher);}
	}
	return book1;
}

Book checkIsbnAndLoadTheBookFromFile(string updatedBook,string*bookPart,string*mainString,BookCatalog catalog,Book book1){
	int j,i = 0;
	char delims[] = ";";
	string temp,result = NULL;
	result = strtok( updatedBook, delims );
	read_contents_of_file(catalog);
	mainString = allocateMemoryFor_result(mainString);
	bookPart = allocateMemoryFor_result(bookPart);
	while( result != NULL ){
		sscanf(result,"%[^;]",bookPart[i]);	
		temp= strpbrk(bookPart[i],":");temp++;
		strcpy(mainString[i],temp);
		bookPart[i] = breakUptocolon(bookPart, i);
		if(areEqual(upper(bookPart[i]),"ISBN"))book1 = loadBook(catalog,book1,temp);
		result = strtok( NULL, delims );
		i++;
	}	
	freeTheResult(mainString);
	if(areEqual(book1.isbn,"")){printf("===>book not found \nPlease check the ISBN\n");exit(1);}
	return book1;
}

void updateBook(string updatedBook,BookCatalog catalog, int argc){
	int numberOfFields;
	Book book1 = {}; 	   
	char option[] = "-isbn";
	string *mainString,*bookPart,duplicateBook = (string)malloc(strlen(updatedBook)+1);
	updatedBook = reduceBlanks(updatedBook);
	copyString(duplicateBook,updatedBook);
	checkNumberOfArgumentsForUpdate(argc);
	isFormatOfStringCorrect(updatedBook,"update");
	numberOfFields = numberOfGivenFields(updatedBook);	
	book1 = checkIsbnAndLoadTheBookFromFile(duplicateBook,bookPart,mainString,catalog,book1);
	mainString = allocateMemoryFor_result(mainString);
	bookPart = allocateMemoryFor_result(bookPart);
	book1 = performOpretionOnFieldsToBeUpdated(mainString,bookPart,catalog,book1,updatedBook);
	writeTheUpdatedDataInFile(option,book1,catalog);
	reduceExtraNewlineCharacter(fileName);
	freeTheResult(mainString);
	freeTheResult(bookPart);
	printf("\n===>Book is updated\n");
}

void checkNumberOfArgumentsForUpdate(int numberOfArguments){
	if(numberOfArguments != 3){helpForUpdate(); exit(1);}
}

void fieldsAreEmptyForUpdate(){
	printf("===>Some of the fields are empty\n"); exit(1);
}

int	numberOfGivenFields(string updatedBook){
	int i,colon = 0;
	for (i = 0;  *updatedBook!='\0' ; ++i){
		if(*updatedBook == ':')colon++;
		updatedBook++;
	}
	return colon;
}

void checkLastCharacter(string updatedBook){
	int length = strlen(updatedBook);
	if(updatedBook[length-1] == ';'){formatOfUpdateBook();}
}

void formatOfUpdateBook(){
	helpForUpdate();
	exit(1);
}

void reduceExtraNewlineCharacter(string fileName){
	char character;
	int newLine = 0;
	FILE* source_filepointer=fopen(fileName,"r");
	FILE* destination_filepointer=fopen("destination_file.txt","w");

	while((character=getc(source_filepointer))!=EOF){
		if(character != '\n'){fprintf(destination_filepointer, "%c",character);newLine = 0;}
		else{if(newLine == 0){fprintf(destination_filepointer, "\n");}newLine++;}
	}
	fclose(source_filepointer);
	fclose(destination_filepointer);
	source_filepointer=fopen(fileName,"w");
	destination_filepointer = fopen("destination_file.txt","r");
	while((character=getc(destination_filepointer))!=EOF) fprintf(source_filepointer, "%c",character);
	fclose(source_filepointer);
	fclose(destination_filepointer);
	remove ("destination_file.txt");
}


							/*functions for adding tag */


string* allocateMemoryFor_TagVariable(string *result){
	int i=0;
	result = (string*)malloc(sizeof(string)*2);
	for (i = 0; i < 2; ++i){ result[i]=(string)malloc(sizeof(char)*100); }
	return result;
}

void freeTheTagVariables(string *result){
	int i=0;
	for (i = 0; i < 2; ++i){ free(result[i]); }
	free(result);
}

int countTheTaggedBooks(){
	int counter=0;
	char character,temp[250];
	FILE *filepointer;
	filepointer=fopen("Tags.txt","r");
	while(!feof(filepointer)){ fgets(temp,200,filepointer); counter++; }
	fclose(filepointer);
	return counter;
}

BookCatalog readTheTagsFromFile(BookCatalog catalog){
	int i;
	FILE * filepointer = fopen("Tags.txt","r");
	for (i = 0; i < countTheTaggedBooks(); ++i){
		fscanf(filepointer,"%[^;];%[^\n]\n",catalog.tags[i].tagIsbn,catalog.tags[i].tag);
	}
	fclose(filepointer);
	return catalog;
}

int isBookAlreadyTagged(BookCatalog catalog,string * mainString,int i){
	int j;
	catalog = read_contents_of_file(catalog);
	for (j = 0; j < countTheTaggedBooks(); ++j){if (areEqual(mainString[i],catalog.tags[j].tagIsbn)) return 1;}
	return 0;
}

Tag copyDataInStructure(string* bookPart,string* mainString, Tag tag1,int i,BookCatalog catalog){
    if(areEqual(upper(bookPart[i]),"ISBN")){
    	

    	copyString(tag1.tagIsbn,mainString[i]);
    }
    else if(areEqual(upper(bookPart[i]),"TAG")){
    	copyString(tag1.tag,mainString[i]);
    }
    else {
    	printf("===> Please check the spelling of [%s]\n",bookPart[i] );  exit(1);
    }	
    return tag1;
}

void checkNumberOfArgumentsForAddTag(int numberOfArguments){
	if (numberOfArguments != 4)formatForAddTag();
}

int numberOfTags(string text){
	int comma = 1;	
	while(*text != '\0'){ 
		if(*text == ',')comma++;
		text++;
	}
	return comma;
}

string* breakTheTags(string text,string * tagArray){
	int i = 0,j;
	string result = NULL;
	char delims[] = ",";
	result = strtok( text, delims );
	while(result != NULL){
		tagArray[i]=(char*)malloc(sizeof(char)*strlen(result)+20);
		copyString(tagArray[i],result);
		i++;
		result = strtok( NULL, delims );
	}
	return tagArray;
}

string findAndBreakTheTagsOfFile(string isbnNo,BookCatalog catalog){
	int j;
	catalog = read_contents_of_file(catalog);
	for (j = 0; j < countTheTaggedBooks(); ++j){
		if (areEqual(isbnNo,catalog.tags[j].tagIsbn)){
			return catalog.tags[j].tag;
		}
	}
	return NULL;
}

Tag  decideTagToBeAdded(Tag tag1,string* tagArray,string* fileTagArray,string fileTag,string userTag){
	int i,j,flag = 1;
	for (j = 0; j < numberOfTags(fileTag); j++){
			strcat(tag1.tag,fileTagArray[j]);
			if(j != (numberOfTags(fileTag)-1))strcat(tag1.tag,",");
		}

	for (i = 0; i < numberOfTags(userTag); i++){
		flag = 0;	
		for (j = 0; j < numberOfTags(fileTag); j++){
			if(!areEqual(tagArray[i],fileTagArray[j])){flag++;}	
		}
		if(flag == numberOfTags(fileTag)){
			if(i != (numberOfTags(userTag))){
				strcat(tag1.tag,",");
			}
			strcat(tag1.tag,tagArray[i]);
		}
	}
	return tag1;
}

Tag  decideTagToDelete(Tag tag1,string* tagArray,string* fileTagArray,string fileTag,string userTag){
	int i,j,flag=0;
	for (i = 0; i < numberOfTags(fileTag); ++i)
	{
		flag=0;
		for (j = 0; j < numberOfTags(userTag); ++j)
		{
			if(areEqual(fileTagArray[i],tagArray[j]))flag++;
		}
		if(flag == 0){
			if(i != (numberOfTags(fileTag) - numberOfTags(userTag)))
			strcat(fileTagArray[i],",");
			strcat(tag1.tag,fileTagArray[i]);
		}
	}
	return tag1;
}

void addNewTagToFile(string result,string* mainString,string*bookPart,string temp,int i){
	FILE *filepointer;
	filepointer = fopen("Tags.txt","a");
	fprintf(filepointer, "\n%s;",mainString[i]);
    i++;
    sscanf(result,"%[^;]",bookPart[i]);
	temp= strpbrk(bookPart[i],":");temp++;
	fprintf(filepointer, "%s",temp);
	fclose(filepointer);
	printf("===>Book is tagged\n");
	exit(1);	
}

void freeTheMemoryOfAllPointers(string* mainString,string* bookPart,string* tagArray,string*fileTagArray){
	freeTheTagVariables(mainString);
    freeTheTagVariables(bookPart);
    freeTheTagVariables(tagArray);
    freeTheTagVariables(fileTagArray);
}

Tag separateTheUserAndFileTags(string option,string userTag,string* mainString,string* tagArray,string*fileTagArray,string fileTag1,Tag tag1,BookCatalog catalog,int i,string fileTag){
	int j;
	userTag = (string )malloc(strlen(mainString[i])+1);
	copyString(userTag,mainString[i]);
			
	tagArray = breakTheTags(mainString[i],tagArray);
	fileTag = findAndBreakTheTagsOfFile(tag1.tagIsbn,catalog);
	fileTag1 = (string )malloc(strlen(fileTag)+1);
	copyString(fileTag1,fileTag);

	fileTagArray = breakTheTags(fileTag,fileTagArray);
	if(areEqual(option,"deleteTag"))tag1 = decideTagToDelete(tag1,tagArray,fileTagArray,fileTag1,userTag);
	else if(areEqual(option,"addTag"))tag1 = decideTagToBeAdded(tag1,tagArray,fileTagArray,fileTag1,userTag);
	free(userTag);
	free(fileTag1);
	return tag1;
}

void addTheUpdatedTag(Tag tag1,string option){
	FILE *filepointer;
	filepointer = fopen("Tags.txt","a");
	fprintf(filepointer,"\n%s;%s",tag1.tagIsbn,tag1.tag);
	fclose(filepointer);
}

void checkIsbnValue(string* mainString,int i){
    if(areEqual(mainString[i]," ") || areEqual(mainString[i],"") || areEqual(mainString[i],"\t")){printf("===>Give correct value in isbn\n");exit(1);}
}

void checkTagValue(string* mainString,int i){
    if(areEqual(mainString[i]," ") || areEqual(mainString[i],"") || areEqual(mainString[i],"\t")){printf("===>Give correct value in tag\n");exit(1);}
}

void performOperationToAddTag(string option,string userTag,string* mainString,string* bookPart,int flag,string result,string temp,string tagToBeAdded,string* tagArray,string*fileTagArray,string fileTag1,Tag tag1,BookCatalog catalog,int i,string fileTag){
	char delims[] = ";";
	while( result != NULL ){
		sscanf(result,"%[^;]",bookPart[i]);
		temp= strpbrk(bookPart[i],":");temp++;
		strcpy(mainString[i],temp);
    	result = strtok( NULL, delims );
		bookPart[i] = breakUptocolon(bookPart, i);

    	if(areEqual(bookPart[i],"isbn")){
    		checkIsbnValue(mainString,i);
    		if(isBookAlreadyTagged(catalog,mainString,i)){ flag=1; copyString(tag1.tagIsbn,mainString[i]); }
    		else addNewTagToFile(result,mainString,bookPart,temp,i);
    	}
		else if(areEqual(bookPart[i],"tag")){
			checkIsbnValue(mainString,i);
			if(strstr(mainString[i]," ")){printf("===>Space is not allowed in tags use \",\" to saparate the tags\n"); exit(1);}
			tag1 = separateTheUserAndFileTags(option,userTag,mainString,tagArray,fileTagArray,fileTag1,tag1,catalog,i,fileTag);
			if(flag==1)deleteTagline(tagToBeAdded,catalog,4);
			addTheUpdatedTag(tag1,option);		
		}
		else formatForAddTag();
   		i++;
	}
    freeTheMemoryOfAllPointers(mainString,bookPart,tagArray,fileTagArray);
}

string reduceBlanksOfTag(string text){
	int i=0,j=0;
	string textWithoutBlanks = (string) malloc(strlen(text));
	while(text[i] != '\0'){
		if(text[i] != ' '){textWithoutBlanks[j] = text[i]; j++;}
		i++;
	}
	textWithoutBlanks[j] = '\0';
	copyString(text,textWithoutBlanks);
	free(textWithoutBlanks);
	return text;
}

void addTag(string tagToBeAdded,BookCatalog catalog, int numberOfArguments){
	int i=0,j,flag=0;  char delims[] = ";";   Tag tag1;  string option = (string)malloc(strlen("addTag")+5);
	string* mainString,*bookPart,*tagArray,*fileTagArray,result = NULL,temp,fileTag,userTag,fileTag1;
	checkNumberOfArgumentsForAddTag(numberOfArguments);
	copyString(option,"addTag");
	tagToBeAdded = reduceBlanksOfTag(tagToBeAdded);
	mainString = allocateMemoryFor_TagVariable(mainString);
	bookPart = allocateMemoryFor_TagVariable(bookPart);
	tagArray = allocateMemoryFor_TagVariable(tagArray);
	fileTagArray = allocateMemoryFor_TagVariable(fileTagArray);
	isFormatOfStringCorrect(tagToBeAdded,"tags add");
	if(strstr(tagToBeAdded,"tag:")==NULL)formatForAddTag();
	result = strtok( tagToBeAdded, delims );
	performOperationToAddTag(option,userTag,mainString,bookPart,flag,result,temp,tagToBeAdded,tagArray,fileTagArray,fileTag1,tag1,catalog,i,fileTag);
	reduceExtraNewlineCharacter("Tags.txt");
}

void freeTheStoredLines(string *storedLines,int j){
	int i;
	for (i = 0; i < j; ++i){
		free(storedLines[i]);
	}
}

void deleteTagline(string tag_string,BookCatalog catalog,int numberOfArguments){
	int i=0,j=0,count = countTheTaggedBooks();
	string storedLines[count];
	FILE*filepointer;
	string* mainString,*bookPart;
	string result = NULL,temp;
	char delims[] =  ";" ,buffer[100],number[20];
	Tag tag1;

	isFormatOfStringCorrect(tag_string,"tags remove");
	reduceBlanks(tag_string);
	mainString = allocateMemoryFor_TagVariable(mainString);
	bookPart = allocateMemoryFor_TagVariable(bookPart);
	catalog = readTheTagsFromFile(catalog);
	filepointer = fopen("Tags.txt","r");
	
	result = strtok( tag_string, delims );

	while( result != NULL ){
		sscanf(result,"%[^;]",bookPart[i]);
		temp= strpbrk(bookPart[i],":");temp++;
		strcpy(mainString[i],temp);
		bookPart[i] = breakUptocolon(bookPart, i);
    	result = strtok( NULL, delims );
    	if(i==0){
    		checkIsbnValue(mainString,i);
			if(isBookAlreadyTagged(catalog,mainString,i)==0){printf("===>Tag not exist\n");exit(1);}
		}
    	tag1 = copyDataInStructure(bookPart,mainString,tag1,i,catalog);
   		i++;
	}

	while(!feof(filepointer)){
		read_contents_of_file(catalog);
		fgets(buffer, 150, filepointer);
		sscanf(buffer,"%[^;];",number);
		if(areEqual(tag1.tagIsbn,number))copyString(buffer,"");
		storedLines[j]=(char*)malloc(sizeof(char)*strlen(buffer)+20);
		copyString(storedLines[j],buffer);
		j++;
	}
	fclose(filepointer);
	filepointer = fopen("Tags.txt","w");
	for (i = 0; i < count ; ++i){
		fprintf(filepointer,"%s\n",storedLines[i]);
	}
	fclose(filepointer);
	freeTheStoredLines(storedLines,j);
	reduceExtraNewlineCharacter("Tags.txt");
}

void deleteTag(string tagToBeAdded,BookCatalog catalog, int numberOfArguments){
	int i=0,j,flag=0;  char delims[] = ";";   Tag tag1; string option = (string)malloc(strlen("deleteTag")+5);
	string* mainString,*bookPart,*tagArray,*fileTagArray,result = NULL,temp,fileTag,userTag,fileTag1;
	copyString(option,"deleteTag");
	checkNumberOfArgumentsForAddTag(numberOfArguments);
	mainString = allocateMemoryFor_TagVariable(mainString);
	bookPart = allocateMemoryFor_TagVariable(bookPart);
	tagArray = allocateMemoryFor_TagVariable(tagArray);
	fileTagArray = allocateMemoryFor_TagVariable(fileTagArray);
	isFormatOfStringCorrect(tagToBeAdded,"tags add");
	tagToBeAdded = reduceBlanksOfTag(tagToBeAdded);
	if(strstr(tagToBeAdded,"tag:")==NULL)formatForAddTag();
	result = strtok( tagToBeAdded, delims );
	performOperationToAddTag(option,userTag,mainString,bookPart,flag,result,temp,tagToBeAdded,tagArray,fileTagArray,fileTag1,tag1,catalog,i,fileTag);
	reduceExtraNewlineCharacter("Tags.txt");
}