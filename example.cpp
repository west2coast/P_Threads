#include <pthread>
.
.
.
int main()
pthread_t	thread_id;
void* threadPointer;
int result;
char *message ="";
result = pthread_create(&thread_id, null, hill,(void*), message); // equal zero or 1
result= pthread_join(thread_id,&threadpointer);

void *hill(char *section1)