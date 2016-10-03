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
//#include <uninstd.h>
#include <vector>
using namespace std;
void* decoder(void* message); // divides the message into 3 parts
void* sifter(void*); // takes user input; message must be valid
void* substitute (void* input); // part 1
void* hill (void* input); // part 2
void* pinnacol (void* input); // part 3

int main (){
	pthread_t sifters;
	string message;
	int result = pthread_create(&sifters, NULL, sifter, NULL);

	if (result){
		printf("Error - pthread_create() return code: %d\n", result);
		exit(EXIT_FAILURE);
	}
	pthread_join(sifters, NULL);
	exit(EXIT_SUCCESS);
}
void* sifter(void*){
	pthread_t decoders;

        int fails = 0, star = 0, starONE = 0, starTWO = 0, starTHREE = 0; // starCount is total # of stars; star is just to send the right information to certain areas
        bool inputFAIL = false, inputPASS = false, starMORE = false, stringRESTARTED = false; //starCheck = false;
        string input;
        cout << "Enter a character string: ";
        while((getline(cin, input) && (fails < 3)) && (inputPASS != true)){
        	inputFAIL = false;
            if(input.empty()){ // checks to see if string is empty
            	inputFAIL = true;
            	fails++;
            }
            
            while (inputFAIL != true && inputPASS != true){ // checks string: approves or fails

            	for (int x = 0; x < input.size(); x++){
            		star = 0;

                    while (input[x] == '*'){ // Find stars
                    	star++;
                    	x++;
                    }
                    
                    bool notNULL = true, breakOUT = false;
                    if (star > 0){

                    	while ((x < input.size()) && breakOUT != true){
                    		char value = input[x];

                    		if (isalnum(value) && (x >! input.size() || x != input.size())){
                    			breakOUT = true;

                    		}else if(value == '*'){
                    			breakOUT = true;
                    			notNULL = false;

                    		}else if(x >= input.size()){
                    			breakOUT = true;
                    			notNULL = false;
                    		}
                    		x++;

                    	}

                    	if (notNULL != false){

                    		if(star == 1){
                    			starONE++;
                    		}
                    		else if (star == 2){
                    			starTWO++;
                    		}
                    		else if (star == 3){
                    			starTHREE++;
                    		}
                    		else if (star > 3){
                    			starMORE = true;
                    		}
                    	}
                    	else if (stringRESTARTED != true){
                    		fails++;
                    		inputFAIL = true;
                    		input.clear();
                    	}

                    }
                        // if there were no stars in the string or if it's finished and all stars don't equal 1
                    

                    
                }
                if((starONE != 1 && 1 != starTWO && 1 != starTHREE)){
                	fails++;
                	inputFAIL = true;
                	input.clear();

                }else if ((starONE == 1) && (1 == starTWO) && (1 == starTHREE)){
                    inputPASS = true;// approves message and exits loops
                }
                
                } // exit for loop
                
                inputFAIL = true; // make exit true to leave loop
                
            } // leave while loops
            
            
            if (!inputPASS){
            	exit(EXIT_FAILURE);
            }
            if(inputPASS){
            	int result = pthread_create(&decoders, NULL, &decoder, &input);
            	if(result){
            		printf("Error - pthread creation failed, return code is: %d\n", result);
            		exit(EXIT_FAILURE);
            	} 

            	pthread_join(decoders, NULL);
            }
            starONE = starTWO = starTHREE = 0;
            inputFAIL = false;
            return 0;

        }
        void* decoder(void* messages){
        	pthread_t substitute1T, hill1T, pinnacol1T;
        	string *mess = static_cast<string*>(messages);
        	int count = 1, stars = 0, start = 0;
        	char asterisk = 42;
        	string message = *mess;
        	string messageSub, messageHil, messagePin;
        	for (int x = 0; x < message.size(); x++){
        		bool charFOUND = false;
        		stars = 0, count =0;
        		while (message[x] == '*'){
        			stars++;
        			x++;
        		}
        		if (stars > 0 && stars < 4){
            while (message[x] != asterisk && (x < message.size())){ // Future reminder Thread 1: Exc_bad_access remember to make x < size
            	if (isspace(message[x]) && charFOUND != true){
            		x++;
            	}else if (charFOUND != true){
            		start = x;
            		charFOUND = true;
            		count++;
            		x++;

            	}else {
            		count++;
            		x++;
            	}
            }
            if (stars == 1){
            	messageSub = message.substr(start,count);

            }else if (stars == 2){
            	messageHil = message.substr(start,count);
            }else{
            	messagePin = message.substr(start,count);
            }
            --x;
        }
    }
    int result = pthread_create(&substitute1T, NULL, &substitute, &messageSub); 
    if (result){
    	printf("Error - pthread_create() return code: %d\n", result);
    	exit(EXIT_FAILURE);
    }
    pthread_join(substitute1T, NULL);
    // int result2 = pthread_create(&hill1T, NULL, &hill, &messageHil); 
    // if (result2){
    // 	printf("Error - pthread_create() return code: %d\n", result2);
    // 	exit(EXIT_FAILURE);
    // }
    // pthread_join(hill1T, NULL);

    // int result3 = pthread_create(&pinnacol1T, NULL, &pinnacol, &messagePin); 

    // if (result3){
    // 	printf("Error - pthread_create() return code: %d\n", result3);
    // 	exit(EXIT_FAILURE);
    // }
    // pthread_join(pinnacol1T, NULL);
    pthread_exit(NULL);
}
void* substitute (void* input){
	string *inputOLD = static_cast<string*>(input);
	vector <char> message;
    char alphabet [26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K','L','M','N','O','P','Q','R','S','T','U', 'V','W','X','Y','Z'};
	string source = *inputOLD;
    int key = 0, placeOfKey = 0, count = 0;
    bool keyFound = false;
    for(int h = 0; h < source.size(); h++){
        
        if (isalpha(source.at(h)) && keyFound != true){
            for(int n = 0; n < 25; n++){
                if(source.at(h) == alphabet[n]){
                    key = count;
                    placeOfKey = h+1;
                }
                count++;
            }
            keyFound = true;
            
        }
        
    }
    for(int i = placeOfKey; i < source.size(); i++){
        char l = source.at(i);
        message.push_back(l);
    }
    bool failed_part1 = false;
    for(int k=0; k < message.size(); k++)
    {
        char alpha = message.at(k);
        if ((isspace(alpha) || isalpha(alpha)) && failed_part1 != true){
           failed_part1 = false;
        }
        else{
            failed_part1 = true;
        }
        
    }
   
    if (failed_part1 == false){
        
        key = (key % 10 + 2);
        int letterNum = 0;
        
        for(int k=0; k < message.size(); k++)
        {
           
            char alpha = message.at(k);
            
            if (!isspace(alpha)){
      
            letterNum = toupper(alpha) - key;
                if( letterNum < 'A' ){
                    letterNum = letterNum + 26;
                }
                
            alpha = letterNum;
                    cout << letterNum << " " << alpha << endl;
            message.at(k) = alpha;
            }
        }
        
        for (int m = 0; m < message.size(); m ++){
            char kim = message.at(m);
            cout << kim;
        }
    }
    else{
        cout << "This fails";
    }
 return 0;
}
