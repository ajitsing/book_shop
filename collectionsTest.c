#include "SampletestUtils.h"
#include "bookCatalog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed


             /*test for Integer*/


void printSum(const void* result){
	printf("%d",*(int*)result);
}

void* minimum_for_int(const void* source, const void* result){
	int* current = (int*)source;
	int* Result = (int*)result;
	int *minimum;
	if(Result==NULL){
		minimum=(int*)malloc(sizeof(int));
	 	*minimum = *current;
	 	return minimum;
	}
	if(*Result>*current)
		*minimum = *current;
	return minimum;
}

void* maximum_for_int(const void* source, const void* result){
	int* current = (int*)source;
	int* Result = (int*)result;
	int *maximum;
	if(Result==NULL){
		maximum=(int*)malloc(sizeof(int));
	 	*maximum = *current;
	 	return maximum;
	}
	if(*Result<*current)
		*maximum = *current;
	return maximum;

}

void* IntsumOfSource(const void* source, const void* result){
	int* current = (int*)source;
	int* Result = (int*)result;
	int *sum;
	if(Result==NULL){
		sum=(int*)malloc(sizeof(int));
	 	*sum = *current;
	 	return sum;
	}
	*sum += *current;
	return sum;
}

void test_sum_of_source_is_28(){
	int source[] = {1,2,3,4,5,6,7};
	int *result;
	result = reduce(source, 7, sizeof(int), IntsumOfSource);
	ASSERT(*result==28);
}

void test_sum_of_33_source_is_33(){
	int source[] = {33};
	int *result;
	result = reduce(source, 1, sizeof(int), IntsumOfSource);
	ASSERT(*result==33);
}

void test_sum_of_1_m2_3_4_m5_6_m7_is_0(){
	int source[] = {1,-2,3,4,-5,6,-7};
	int *result;
	result = reduce(source, 7, sizeof(int), IntsumOfSource);
	ASSERT(*result==0);
}

void test_sum_of_0_is_0(){
	int source[] = {0};
	int *result;
	result = reduce(source, 1, sizeof(int), IntsumOfSource);
	ASSERT(*result==0);
}

void test_sum_of_source_is_0(){
	int source[] = {0,0,0,0,0,0,0};
	int *result;
	result = reduce(source, 7, sizeof(int), IntsumOfSource);
	ASSERT(*result==0);
}

void test_minimum_number_is_1(){
	int source[] = {4,8,3,4,2,1,5};
	int *result;
	result = reduce(source, 7, sizeof(int), minimum_for_int);
	ASSERT(*result==1);
}

void test_maximum_number_is_8(){
	int source[] = {4,8,3,4,2,1,5};
	int *result;
	result = reduce(source, 7, sizeof(int), maximum_for_int);
	ASSERT(*result==8);
}



			/*test for float*/



void printFloatSum(const void* result){
	printf("%f",*(float*)result);
}

void* FloatsumOfSource(const void* source, const void* result){
	float* current = (float*)source;
	float* Result = (float*)result;
	float *sum;
	if(Result==NULL){
		sum=(float*)malloc(sizeof(float));
	 	*sum = *current;
	 	return sum;
	}
	*sum += *current;
	return sum;
}

void* minimum_for_float(const void* source, const void* result){
	float* current = (float*)source;
	float* Result = (float*)result;
	float *minimum;
	if(Result==NULL){
		minimum=(float*)malloc(sizeof(float));
	 	*minimum = *current;
	 	return minimum;
	}
	if(*Result>*current)
		*minimum = *current;
	return minimum;
}

void* maximum_for_float(const void* source, const void* result){
	float* current = (float*)source;
	float* Result = (float*)result;
	float *maximum;
	if(Result==NULL){
		maximum=(float*)malloc(sizeof(float));
	 	*maximum = *current;
	 	return maximum;
	}
	if(*Result<*current)
		*maximum = *current;
	return maximum;
}

void test_sum_of_float_source_is_28point000000(){
	float source[] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
	float *result;
	result = reduce(source, 7, sizeof(float), FloatsumOfSource);
	ASSERT(*result==28.000000);
}

void test_sum_of_float_source_is_0point000000(){
	float source[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	float *result;
	result = reduce(source, 7, sizeof(float), FloatsumOfSource);
	ASSERT(*result==0.000000);
}

void test_sum_of_empty_float_source_is_0point000000(){
	float source[] = {};
	float *result;
	result = reduce(source, 0, sizeof(float), FloatsumOfSource);
	ASSERT(result==NULL);
}

void test_minimum_of_float_number_is_1point000000(){
	float source[] = {4.0,8.0,3.0,4.0,2.0,1.0,5.0};
	float *result;
	result = reduce(source, 7, sizeof(float), minimum_for_float);
	ASSERT(*result==1.000000);
}

void test_maximum_of_float_number_is_8point000000(){
	float source[] = {4.0,8.0,3.0,4.0,2.0,1.0,5.0};
	float *result;
	result = reduce(source, 7, sizeof(float), maximum_for_float);
	ASSERT(*result==8.000000);
}



			/*test for collection of names*/


typedef struct{
	char first[20];
	char middle[20];
	char last[20];
}Name;

void* numberOfCharacters(const void* source, const void* result){

	Name* current = (Name*)source;
	char fullName[100];
	int *totalCharacters=(void*)result;
	if(totalCharacters==NULL){
		totalCharacters=(int*)malloc(sizeof(int));
		sprintf(fullName,"%s%s%s",current->first,current->middle,current->last);
		*totalCharacters=strlen(fullName);
	 	return totalCharacters;
	}
	sprintf(fullName,"%s%s%s",current->first,current->middle,current->last);
	*totalCharacters += (strlen(fullName));
	return totalCharacters;
}

void test_number_of_character_of_the_name_structure_is_10(){
	Name source[] = {{"Ajit", "Singh", "Saroya"}, {"Aj", "it", "Saroya"}, {"Ajit", "Singh", "Saroya"}};
	int *result=0;
	result = reduce(source, 3, sizeof(Name), numberOfCharacters);
	ASSERT(*result == 40);
}

int integerToString(const void* source, void* result){
	sprintf(*(char**)result, "%d", *(int*)source);
	return 1;
}


int square(const void* source, void* result){
	int * IntSource=(int*)source;
	*(int*)result=((*IntSource)*(*IntSource));
	return 1; 
}

int intTofloat(const void* source, void* result){
	float* Result = (float*)result;
	*Result = *(int*)source;
	return 1; 
}

int everything(const void* source, void* result){
	int* IntSource = (int*)source;
	*(int*)result = *IntSource;
	return 1;
}


void test_convert_integer_to_float(){
	int source[]={1,2,3,4,5,6,7};
	float result[7];
	map(source, 7, sizeof(float), intTofloat, result);
	ASSERT(result[1]==2.000000 && result[6]==7.000000);
}

void test_square_the_source_values(){
	int source[]={1,2,3,4,5,6,7};
	int result[7];
	map(source, 7, sizeof(int), square, result);
	ASSERT(result[0]==1 && result[6]==49);
}


void test_convert_integer_to_string(){
	int i,source[]={100,20,3000000,4,5,6,7};
	// char result[7][20];
	char** result = (char**)malloc(sizeof(char*)*30);

	for (i = 0; i < 7; ++i){
		result[i]=(char*)malloc(sizeof(char)*20);
	}
	map(source, 7, sizeof(int), integerToString, result);
	ASSERT(strcmp(result[2],"3000000")==0);
	free(result);
}

void test_print_everything(){
	int source[]={1,2,3,4,5,6,7};
	int result[7];
	map(source, 7, sizeof(int), everything, result);
	ASSERT(result[6]==7 && result[3]==4);
}

typedef struct{
	char first[20];
	char middle[20];
	char last[20];
}name;

int firstAndLast(const void* source, void* result){
	int i=0;
	name *structSource = (name*)source;
	char** Result = (char**)result;
	for (i = 0; i < 2; ++i){
		sprintf(Result[i],"%s %s",structSource[i].first,structSource[i].last);
	}
	return 1;
}

void test_join_first_and_last_name(){
	name source[] = {{"Majnu","Nalla","Paiyya"}, {"Ajit","Singh","Saroya"}};
	int i;
	char** result = (char**)malloc(sizeof(char*)*30);

	for (i = 0; i < 7; ++i){
		result[i]=(char*)malloc(sizeof(char)*20);
	}
	map(source, 2, sizeof(name), firstAndLast, result);
	ASSERT(areEqual(result[1],"Ajit Saroya"));
	free(result);
}
