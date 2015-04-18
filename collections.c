#include <string.h>
#include "bookCatalog.h"

int findAll(MatchFunction* match, const void* searchPart, const void* source, unsigned int numberOfElements, unsigned int elementSize, void* result){

	const void *current = source;
	void *currentResult = result;
	int i;
	for (i = 0; i < numberOfElements; ++i)
	{
		if(match(searchPart,current)){
			memcpy(currentResult,current,elementSize);
			currentResult += elementSize;
		}
		current += elementSize;
	}
	return (currentResult - result)/elementSize;
}

void map(const void* source, int No_of_Elements, unsigned int SizeOfElement, Convertor* convert, void *result){
	const void* current = source;
	void* currentresult = result;
	int i=0;
	for (i = 0; i < No_of_Elements; i++)
	{
		if(convert(current, currentresult)){
			currentresult += SizeOfElement;
		}
		current += SizeOfElement;
	}
}

void* reduce(const void* source, unsigned int numberOfElements, unsigned int sizeOfElement, reducer* reducefunction){
	int i=0;
	const void *current = source;
	void* currentresult;
	currentresult = NULL;
	if(numberOfElements == 0) return NULL; 
	for (i = 0; i < numberOfElements; i++){
		currentresult = reducefunction(current, currentresult);
		current += sizeOfElement;
	}
	return currentresult;
}