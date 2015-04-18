void incrementTestCount();
void incrementPassCount();
void testFailed();
void testStarted(const char* name);

#define ASSERT(expr) \
	testStarted(__FUNCTION__);\
	if(expr){\
		incrementPassCount();\
	} else{\
		testFailed();\
	}\
	incrementTestCount()
