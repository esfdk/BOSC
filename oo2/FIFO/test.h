#ifndef TEST_HEADER_FILE
#define TEST_HEADER_FILE

void nonThreadTest();
void threadTest();
void *threadOne(void *argument);
void *threadTwo(void *argument);
void *threadThree(void *argument);

#endif