#include <stdio.h>

int testCount=0;
int passCount=0;

void setup();
void tearDown();

void fixtureSetup();
void fixtureTearDown();

void testStarted(char* name){
	printf("\t%s\n",name);
}

void resetTestCount(){
	testCount=0;
	passCount=0;
	printf("********* Starting tests\n\n");
}

void summarizeTestCount(){
	printf("\n********* Ran %d tests passed %d failed %d\n",testCount,passCount,testCount-passCount);
}

void incrementTestCount(){
	testCount++;
}

void incrementPassCount(){
	passCount++;
}

void testFailed(){
	printf("\t\t*** failed\n");
}

int main(){
	fixtureSetup();
	resetTestCount();

	setup();
		test_book_Invetory_created();
	tearDown();

	setup();
		test_number_of_lines_in_file_is_7();
	tearDown();

	setup();
		test_addBook_isbn_1234567890_price_333_author_chetanBhagat_title_twoStates_publisher_universalPublication();
	tearDown();

	setup();
		test_addBook_isbn_0571283071_price_374_author_JeetThayil_title_Narcopolis_publisher_faber();
	tearDown();

	setup();
		test_addBook_isbn_140870420X_price_570_author_JKRowling_title_CasualVacancy_publisher_BrownBookGroup();
	tearDown();

	setup();
		test_addBook_isbn_3745869701_price_170_author_Narayan_title_The_Bachler_Of_Arts_publisher_universalPublication();
	tearDown();

	setup();
		test_addBook_isbn_818400298X_price_287_author_Yuvraj_title_DiffrentForm_publisher_Ebury();
	tearDown();

	setup();
		test_string_ajit_and_ajit_areEqual();
	tearDown();

	setup();
		test_string_ajit_and_Singh_are_not_Equal();
	tearDown();

	setup();
		test_string_ajit_copied_in_second_string();
	tearDown();

	setup();
		test_string_ajit_is_not_copied_in_second_string();
	tearDown();

	setup();
		test_number_of_collons_in_the_string_is_5();
	tearDown();

	setup();
		test_number_of_argumentes_for_add_is_3();
	tearDown();

	setup();
		test_number_of_argumentes_for_delete_is_3();
	tearDown();


	summarizeTestCount();
	fixtureTearDown();
	return 0;
}

void fixtureSetup(){}

void fixtureTearDown(){}
