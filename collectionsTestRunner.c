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
		test_sum_of_source_is_28();
	tearDown();

	setup();
		test_sum_of_33_source_is_33();
	tearDown();

	setup();
		test_sum_of_1_m2_3_4_m5_6_m7_is_0();
	tearDown();

	setup();
		test_sum_of_0_is_0();
	tearDown();

	setup();
		test_sum_of_source_is_0();
	tearDown();

	setup();
		test_minimum_number_is_1();
	tearDown();

	setup();
		test_maximum_number_is_8();
	tearDown();

	setup();
		test_sum_of_float_source_is_28point000000();
	tearDown();

	setup();
		test_sum_of_float_source_is_0point000000();
	tearDown();

	setup();
		test_sum_of_empty_float_source_is_0point000000();
	tearDown();

	setup();
		test_minimum_of_float_number_is_1point000000();
	tearDown();

	setup();
		test_maximum_of_float_number_is_8point000000();
	tearDown();

	setup();
		test_number_of_character_of_the_name_structure_is_10();
	tearDown();

	setup();
		test_convert_integer_to_float();
	tearDown();

	setup();
		test_square_the_source_values();
	tearDown();

	setup();
		test_convert_integer_to_string();
	tearDown();

	setup();
		test_print_everything();
	tearDown();

	setup();
		test_join_first_and_last_name();
	tearDown();


	summarizeTestCount();
	fixtureTearDown();
	return 0;
}

void setup(){}

void tearDown(){}

void fixtureSetup(){}

void fixtureTearDown(){}
