typedef int MatchFunction(const void* searchPart, const void* sourceItem);
typedef  int Convertor(const void* source, void* result);
typedef void* reducer(const void* source, const void* result);

int findAll(MatchFunction* match, const void* searchPart, const void* source, unsigned int numberOfElements, unsigned int elementSize, void* result);
void map(const void* source, int No_of_Elements, unsigned int SizeOfElement, Convertor* convert, void *result);
void* reduce(const void* source, unsigned int numberOfElements, unsigned int sizeOfElement,reducer* reduce);