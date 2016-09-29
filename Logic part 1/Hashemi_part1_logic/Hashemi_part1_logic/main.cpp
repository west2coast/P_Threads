    //
    //  main.cpp
    //  Hashemi_part1_logic
    //
    //  Created by Chris West on 9/26/16.
    //  Copyright © 2016 Chris West. All rights reserved.
    //
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
    //#include <uninstd>
#include <vector>
using namespace std;
vector <char> message;
    char alphabet [26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K','L','M','N','O','P','Q','R','S','T','U', 'V','W','X','Y','Z'};
int main()
{
    std::string source = "J QFN F YZAP RZZOWFNV"; // rzzowfnv
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
    std::cout << source << std::endl;
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
