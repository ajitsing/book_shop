#include "sampletestUtils.h"
#include "bookCatalog.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

BookCatalog catalog;
const string Filename = "testInventory.txt";

void setup(){
	catalog = createCatalog(11);
	read_contents_of_file(catalog);
}

void tearDown(){
	clearCatalog(catalog);
}

void test_book_Invetory_created(){
	ASSERT(catalog.count==11);
}

void test_number_of_lines_in_file_is_7(){
	int numberOfLines=0;
	numberOfLines = count_lines_of_file();
	ASSERT(numberOfLines == 7);
}

void test_addBook_isbn_1234567890_price_333_author_chetanBhagat_title_twoStates_publisher_universalPublication(){
	int totalLinesAfterAdd;
	addBook("isbn:1234567890;price:333;author:chetan Bhagat;title: two state; publisher: universal Publication",3,catalog);
	totalLinesAfterAdd=count_lines_of_file();
	ASSERT(totalLinesAfterAdd == 7);
}

void test_addBook_isbn_0571283071_price_374_author_JeetThayil_title_Narcopolis_publisher_faber(){
	int totalLinesAfterAdd;
	addBook("isbn:0571283071;price:374;author:Jeet Thayil;title:Narcopolis;publisher:Faber & Faber",3,catalog);
	totalLinesAfterAdd=count_lines_of_file();
	ASSERT(totalLinesAfterAdd == 7);
}


void test_addBook_isbn_140870420X_price_570_author_JKRowling_title_CasualVacancy_publisher_BrownBookGroup(){
	int totalLinesAfterAdd;
	addBook("isbn:140870420X;price:570;author:J. K. Rowling;title:The Casual Vacancy;publisher:Little, Brown Book Group",3,catalog);
	totalLinesAfterAdd=count_lines_of_file();
	ASSERT(totalLinesAfterAdd == 7);
}

void test_addBook_isbn_3745869701_price_170_author_Narayan_title_The_Bachler_Of_Arts_publisher_universalPublication(){
	int totalLinesAfterAdd;
	addBook("isbn:3745869701;price:170;author:Narayan;title:The Bachler Of Arts;publisher:universal Publication",3,catalog);
	totalLinesAfterAdd=count_lines_of_file();
	ASSERT(totalLinesAfterAdd == 7);
}

void test_addBook_isbn_818400298X_price_287_author_Yuvraj_title_DiffrentForm_publisher_Ebury(){
	int totalLinesAfterAdd;
	addBook("isbn:818400298X;price:287;author:Yuvraj Singh;title:In Different Form;publisher:Ebury Press",3,catalog);
	totalLinesAfterAdd=count_lines_of_file();
	ASSERT(totalLinesAfterAdd == 7);
}

void test_string_ajit_and_ajit_areEqual(){
	string first = "ajit";
	string second = "ajit";
	ASSERT(areEqual(first,second));
}

void test_string_ajit_and_Singh_are_not_Equal(){
	string first = "ajit";
	string second = "Singh";
	ASSERT(!areEqual(first,second));
}

void test_string_ajit_copied_in_second_string(){
	string first = "ajit";
	char second[10];
	copyString(second,first);
	ASSERT(areEqual(first,second));
}

void test_string_ajit_is_not_copied_in_second_string(){
	char first[10] = "ajit";
	char second[10] = "Singh";
	copyString(first,second);
	ASSERT(areEqual(first,second));
}

void test_number_of_collons_in_the_string_is_5(){
	string book = "isbn:140870420X;price:570;author:J. K. Rowling;title:The Casual Vacancy;publisher:Little, Brown Book Group";
	ASSERT(numberOfGivenFields(book) == 5); 	
}

void test_number_of_argumentes_for_add_is_3(){
	checkNumberOfArgumentsForAddBook_and_updateBook(3);
	ASSERT(1);
}

void test_number_of_argumentes_for_delete_is_3(){
	checkNumberOfArgumentsForAddBook_and_updateBook(3);
	ASSERT(1);
}