/*
 * main.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: Chris West
 */
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
void* dissectors(void* message);
void* thinkers (void*);
void* part1 (void* input);
void* part2 (void* input);
void* part3 (void* input);
/*
 * Main Method
 */
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
/*
 * Thinker Method
 */
 void* thinkers (void*){
    pthread_t dissector;
    int fails = 0, star = 0, starCount = 0, x = 0, tempStar = 0, star1 = 0, star2 = 0, star3 = 0; // starCount is total # of stars; star is just to send the right information to certain areas
    bool exit1 = false; //starCheck = false;
    string input;
    cout << "Enter a character string: ";
    while(getline(cin, input) && (fails < 3)){

    if(input.empty()){
        exit1 = true;
        fails++;
    }
    while (exit1 != true && fails < 3){

        for (int x = 0; x <= input.size(); x++){
            star = 0;
            while (input[x] == '*'){ // Find stars
              star++;
              x++;
          }
            bool notNULL = true, breakOUT = false;
          if (star > 0){
            int m = x;

            while ((isspace(input[m]) || input[m]== '*') && breakOUT != true){
                         
                if(m >= input.size()){
                    breakOUT = true;
                    notNULL = false;
                }
                else if(input[m] == '*'){
                    breakOUT = true;
                    notNULL = false;
                }
                m++;  
            }
            
            if (notNULL != false){
                
            if(star == 1 && star1 != 1){
                starCount++;
                star1 = 1;
            }
            else if (star == 2 && star2 != 1){
                starCount++;
                star2 = 1;
            }

            else if (star == 3 && star3 != 1){
                starCount++;
                star3 = 1;
            }
            else{
                fails++;
                input.clear();
            } 
            } 
            else{
                fails++;
                input.clear();
            }
        }
        else if(x == input.size() && starCount < 3){
                            fails++;
                input.clear();
        }

        } // exit for loop
        
        exit1 = true;    

    } // leave while loops
    
    
    if (fails == 3){
        exit(EXIT_FAILURE);
    }
    if(starCount == 3){
    int result = pthread_create(&dissector, NULL, &dissectors, &input);
    if(result){
        printf("Error - pthread creation failed, return code is: %d\n", result);
        exit(EXIT_FAILURE);
    } 
    
    pthread_join(dissector, NULL);
}
    starCount = 0;
    star1 = star2 = star3 = 0;
    exit1 = false;
}
    return 0;
}
/*
 * Dissector Method
 */
 void* dissectors(void* message){
    pthread_t part1T, part2T, part3T;
    string *inputOLD = static_cast<string*>(message);
    string input = *inputOLD, part1S, part2S, part3S;
    int x = 0, star = 0, tempStar = 0, storeLoc[3], storeLocEnd[3];
    /** Finds Starting Location of the Stars substring and then adds + 1 to make sure it's not the star location **/
    for(int t = 0; t <= input.size(); t++){
        star = 0;
            while (input[t] == '*'){ // Find stars
              tempStar = t; // temp. location of star
              star++;
              t++;
          }
          storeLoc[star-1] = tempStar + 1; // subtract from star to store in array and temp. + 1 to store pass the place of the star to begin
      }
    /** Finds Stopping Location of the Starting Star **/
    for (int m = 0; m < 3; m++){ // Stars
        x = storeLoc[m]; // starting location of each star
        
        for (int y = x; y <= input.size(); y++){ // Goes through string
            if (input[y] == '*'){
                storeLocEnd[m] = y;
                break;
            }
            else if(y == input.size()){
                storeLocEnd[m] = y;
                break;
            }
        }
    }

    for (int q = 0; q < 3; q++){
        int r = storeLoc[q];
        int s = storeLocEnd[q];
        if (q == 0){
            s = s - r;
            part1S = input.substr(r, s);
        }
        else if(q == 1){
            s = s - r;
            part2S = input.substr(r, s);
        }
        else if(q == 2){
            s = s - r;
            part3S = input.substr(r, s);
        }
    }

    int result = pthread_create(&part1T, NULL, &part1, &part1S); 
    if (result){
      printf("Error - pthread_create() return code: %d\n", result);
      exit(EXIT_FAILURE);
    }
    pthread_join(part1T, NULL);
    int result2 = pthread_create(&part2T, NULL, &part2, &part2S); 
    if (result2){
      printf("Error - pthread_create() return code: %d\n", result2);
      exit(EXIT_FAILURE);
    }
    pthread_join(part2T, NULL);

    int result3 = pthread_create(&part3T, NULL, &part3, &part3S); 

    if (result3){
      printf("Error - pthread_create() return code: %d\n", result3);
      exit(EXIT_FAILURE);
    }
    pthread_join(part3T, NULL);
    pthread_exit(NULL);
}
/*
 * Part 1 of Dissector
 */
 void* part1 (void* message){ 
    string *inputOLD = static_cast<string*>(message);
    string input = *inputOLD, first = "", middle = "", last = "", birth = "", month, day, year;
    char letter[4] =  {'F', 'M', 'L', 'B'};
    string inputNEWC = input;
    inputNEWC.c_str();
    bool firstCAP = false, notAlpha = false, f = false, l = false, m = false, b = false;
    int temp = -1, count = 0;
    time_t theTime = time(NULL);
    struct tm *time1 = localtime(&theTime);
    for (int y = 0; y < 4; y++){ // Goes through four letter points
        notAlpha = false;
        for (int x = 0; x < input.size(); x++){ // Goes 

            if ((inputNEWC[x] == letter[y]) && (firstCAP != true)){
                temp = x;
                firstCAP = true;
            }

            while((temp >= 0) && !isspace(inputNEWC[x])){
                count++;
                x++;
            }

            if(isspace(inputNEWC[x]) && (temp >= 0) && count > 0){
                string sub = input.substr(temp, count);
                string sub2 = input.substr(temp + 1, count);
                int i = 0, p = 0;
                
                while (sub[i] && (sub[0] == 'F' ||sub[0] == 'M' ||sub[0] == 'L')){
                    if (i != 0)
                    if (!isalpha(sub[i]))
                        notAlpha = true; 
                      
                    i++;
                }
                
                while (sub[p] && (sub[0] == 'B')){
                    
                    if (p != 0)
                    if (!isdigit(sub[p])){
                        notAlpha = true; // 1 True or 0 False
                      
                    }  
                    p++;
                }
                
                if (notAlpha == false){
                    sub = sub2;
                if(letter[y] == 'F' && f != true){
                    first = sub;
                    f = true;
                }
                else if(letter[y] == 'M' && m != true){
                    middle = sub;
                    m = true;
                }
                else if(letter[y] == 'L' && l != true){
                    last = sub;
                    l = true;
                }
                else if(letter[y] == 'B' && b != true){
                    int temp2 = 0; // starting location for birth string
                    b = true;
                    month = sub.substr(temp2, 2); 
                    day = sub.substr(temp2 + 2, 2);
                    year = sub.substr(temp2 + 4 , 2);
                    int valueM = atoi(month.c_str()), valueD = atoi(day.c_str()), valueY = atoi(year.c_str()) ; // string convert: month, day, & year value to int
                    int currentM = time1->tm_mday, currentD = time1->tm_mon + 1, currentY = time1->tm_year + 1900; // Current: Month, Day, Year
                    if (valueY <= 15){
                        valueY += 2000;
                    }
                    else {
                        valueY += 1900;
                    }

                    if (valueM <= currentM){
                        if(valueD <= currentD){
                            valueY += 0; // don't change
                        }
                        else{
                           valueY -= 1; // subtract 1 from year 
                       }
                   }
                   else {
                        valueY -= 1; // subtract 1 from year
                    }
                    currentY -= valueY;
                    birth = to_string(currentY);
                }
            }
                        
            }
            temp = -1;
            count = 0;
            firstCAP = false;
        } // End of inner for loop
    } // End of outter for loop
    for (int x = 0; x < 4; x++){
        if(first.empty()){
            first = "missing value";
        }
        else if(middle.empty()){
            middle = "missing value";
        }
        else if(last.empty()){
            last = "missing value";
        }
        else if(birth.empty()){
            birth = "missing value";
        } 
    } 

    printf("Name: \n%s\n%s\n%s\n" "Age: \n%s\n", last.c_str(), first.c_str(), middle.c_str(), birth.c_str());

    return 0;
}


void* part2 (void* input){
    string *inputOLD = static_cast<string*>(input); 
    string inputNEW = *inputOLD;
    int x = 0, sum = 0, count = 0;
    double total = 0, e = 0, average, inverse, standardD, m;
    vector<double> scores;

    while (x < inputNEW.size()){
        if(isdigit(inputNEW[x])){
            count++;
        }
        else{
            if(count > 0){
                scores.push_back(stoi(inputNEW.substr(x - count, count)));
            }
            count = 0;  
        }
        x++;
    }
   if(scores.size() > 0){
    x = 0;
    sum = accumulate(scores.begin(), scores.end(), 0);
    average = sum / 4;
    inverse = 1.0 / static_cast<double>(scores.size());

    while (x < scores.size()){
        m = static_cast<double>(scores.at(x) - average);
        e += m * m;
        x++;
    }
    standardD = sqrt(inverse * e);

    string stringD = static_cast<ostringstream*>( &(ostringstream() << standardD) )->str();
    string stringA = static_cast<ostringstream*>( &(ostringstream() << average) )->str();

    printf("Score Average: %s\nStandard Deviation: %s\n", stringA.c_str(), stringD.c_str());
}
else{
    cout << "Score Average: \ninvalid" << "\nStandard Deviation: \ninvalid" << endl;
}
    return 0;
}

void* part3 (void* message){
    string *inputOLD = static_cast<string*>(message);
    string input = *inputOLD;
    string inputNEWC = input, password = " ", digit = " ";
    inputNEWC.c_str();
    int temp = 0, count = 0, checkpoint = 0;
    string wordNum[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int x = 0; x < input.size(); x++){
        temp = x;
        while(!isspace(inputNEWC[x])){
            count++;
            x++;
        }
        if(isspace(inputNEWC[x]) && (temp >= 0) && count > 0){
            string sub = input.substr(temp, count);
            int m = 0;
            bool notWord = true;
            while(m < sub.size()){
                if(!isalpha(sub[m])){
                    notWord = false;}
                    m++;
            }

            if(notWord != false){ 
                for(int s = 0; s < sizeof(wordNum); s++){ // Checks for a word that is a number then 
                    if(sub == wordNum[s]){
                        digit = to_string(s);
                        password += digit;
                        checkpoint = 1;
                    }

                }
                if(checkpoint != 1){
                    char dub = sub[0];
                    if(islower(dub))
                        password += dub;
                }
            }
                
            } 
            checkpoint = 0; 
            count = 0;

        }
        temp = 0;
        string validity = " ";  
        bool valid = false, checkpoint2 = false;
        if(password.size() > 6){
            for (int j = 0; j < password.length(); j++){
                if(isdigit(password[j])){
                    checkpoint = 1;
                }
                count++;
                if(j == 5 && checkpoint == 1 && checkpoint2 == false){
                    string newPass = password.substr(temp, count);
                    validity = "Valid";
                    valid = true;
                } else if (j == 5 && checkpoint != 1 && checkpoint2 == false){ // this is checkpoint2
                    temp = password.length() - j;
                    j = temp;
                    count = 0;
                    checkpoint2 = true;
                } else if(j == (password.length() -1) && checkpoint == 1){
                    string newPass = password.substr(temp, count);
                    validity = "Valid";
                }else if(j == (password.length() -1) && checkpoint != 1){
                    validity = "Not Valid";
                }

            }
        }
        else{
            validity = "Not Valid";
        }

        printf("Password: \n%s\n", validity.c_str());

        return(0);
    }