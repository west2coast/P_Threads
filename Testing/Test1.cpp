#include <algorithm>
#include <ctype.h>
#include <fstream> 
#include <iostream>
#include <math.h>
#include <numeric>
#include <pthread.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <uninstd.h>
#include <vector>
using namespace std;
void* decoder(void* message); // divides the message into 3 parts
void* sifter (void*); // takes user input; message must be valid
void* substitute (void* input); // part 1
void* hill (void* input); // part 2
void* pinnacol (void* input); // part 3

 int main (){
    pthread_t thinker;
    string message;
    int result = pthread_create(&thinker, NULL, thinkers, NULL);

    if (result){
        printf("Error - pthread_create() return code: %d\n", result);
        exit(EXIT_FAILURE);
    }
    pthread_join(thinker, NULL);
    exit(EXIT_SUCCESS);
}