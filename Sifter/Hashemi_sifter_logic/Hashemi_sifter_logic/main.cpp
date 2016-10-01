//
//  main.cpp
//  Hashemi_sifter_logic
//
//  Created by Chris West on 9/30/16.
//  Copyright © 2016 Chris West. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <ctype.h>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <sstream>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[]) {
   
    
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
//                       cout << "star locations " << x << endl;
//                        cout << "fuck";
//                        cout << star;
                        
                        while ((x < input.size()) && breakOUT != true){
                            char value = input[x];
//                            cout << value << endl;
                            if (isalnum(value) && (x >! input.size() || x != input.size())){
                                breakOUT = true;
//                                cout << "dog" << " Count" << star << endl;
                            }else if(value == '*'){
                                breakOUT = true;
                                notNULL = false;
//                                cout << "BITCH";
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
                            //cout << "DAM and " << starTHREE << starTWO << starONE << " " << x << endl ;
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
                cout << "FUCK YEA" << fails;
            }
            starONE = starTWO = starTHREE = 0;
            inputFAIL = false;
//    cout << fails ;
    
return 0;
}


