# Creates a myfile.c source file, myfileTest.c test file and testUtils.h header file
# ./createScaffold.sh mymath.c
#

source=$1
testHeader='sampletestUtils.h'
header=`echo $source |sed -e s/.c$/.h/`
testSource=`echo $source |sed -e s/.c$/Test.c/`
touch $header
cat > $source <<END_OF_SOURCE
#include "$header"
END_OF_SOURCE
cat > $testSource <<END_OF_TESTSOURCE
#include "$testHeader"
#include "$header"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

void test_fail(){
	ASSERT(0);
}
END_OF_TESTSOURCE
cat > $testHeader <<END_OF_TEST_HEADER
void incrementTestCount();
void incrementPassCount();
void testFailed();
void testStarted(const char* name);

#define ASSERT(expr) \\
	testStarted(__FUNCTION__);\\
	if(expr){\\
		incrementPassCount();\\
	} else{\\
		testFailed();\\
	}\\
	incrementTestCount()
END_OF_TEST_HEADER
