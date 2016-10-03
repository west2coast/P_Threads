    //
    //  main.cpp
    //  Hashemi_Hill_Logic
    //
    //  Created by Chris West on 10/1/16.
    //  Copyright © 2016 Chris West. All rights reserved.
    //

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
int mod2lus (int value, int number);

int main(int argc, const char * argv[]) {
    int count = 0, start = 0, count2, start2 = 0, countSECT1 = 0, begin = 0, end = 0;
    int m = 0,n = 0,o = 0,p = 0;
    
    map<char,int> alphabet = {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'G',6},{'H',7},{'I',8},{'J',9},{'K',10},{'L',11},
    {'M',12},{'N',13},{'O',14},{'P',15},{'Q',16},{'R',17},{'S',18},{'T',19},{'U',20},{'V',21},{'W',22},{'X',23},{'Y',24},{'Z',25}};
    map<int,char> numAlpha = {{0,'A'},{1,'B'},{2,'C'},{3,'D'},{4,'E'},{5,'F'},{6,'G'},{7,'H'},{8,'I'},{9,'J'},{10,'K'},{11,'L'},{12,'M'},
        {13,'N'},{14,'O'},{15,'P'},{16,'Q'},{17,'R'},{18,'S'},{19,'T'},{20,'U'},{21,'V'},{22,'W'},{23,'X'},{24,'Y'},{25,'Z'}};
    string message = "MWUULNGXAP 12 -15 7 6", sectionONE, sectionTWO, values; // MWUULNGXAP 12 -15 7 6  PQLG 4 3 2 7
    vector<string> numbers, newMessage;
    bool sectionFOUND = false, section2FOUND = false, sectONEFAIL = false, sectTWOFAIL = false;
    for(int x = 0; x < message.size(); x++){
        if(isspace(message[x]) && sectionFOUND != true){
            sectionFOUND = true;
        } else if (sectionFOUND != true){
            if (count == 0){
                count++;
                start = 0;
            }else{
                count++;
            }
            
        } else {
            if(isspace(message[x]) && section2FOUND != true){
                
            }else if (section2FOUND != true){
                section2FOUND = true;
                count2++;
                start2 = x;
            }else{
                count2++;
            }
        }
    }
    sectionONE = message.substr(start, count);
    sectionTWO = message.substr(start2, count2);
    for (int x = 0; x < sectionONE.size(); x++){
        if (isalpha(sectionONE[x])){
            countSECT1++;
        }else{
            sectONEFAIL = true;
        }
    }
    if (countSECT1 % 2 != 0){ // one is odd and zero is even
        sectONEFAIL = true;
    }
    for (int y = 0; y < sectionTWO.size(); y++){
        if (isdigit(sectionTWO[y]) || sectionTWO[y] == '-' || isspace(sectionTWO[y])){
            
        }else{
            sectONEFAIL = true;
        }
    }
    if(!sectONEFAIL && !sectTWOFAIL){
        for (int z = 0; z < sectionTWO.size(); z++){
            if(isdigit(sectionTWO[z]) || sectionTWO[z] == '-'){
                
                if (end == 0){
                    begin = z;
                    end++;
                }else{
                    end++;
                }
            }else{
                if (end > 0){
                    values = sectionTWO.substr(begin,end);
                    numbers.push_back(values);
                    end = 0;
                }
            }

        }
        if (end > 0){
            values = sectionTWO.substr(begin,end);
            numbers.push_back(values);
            end = 0;
        }
 
    }

    if (numbers.size() != 4){
        sectTWOFAIL = true;
    }
    if(!sectONEFAIL && !sectTWOFAIL){
        m = stoi(numbers.at(0));
        n = stoi(numbers.at(1));
        o = stoi(numbers.at(2));
        p = stoi(numbers.at(3));
        for (int t = 0; t < sectionONE.size(); t++){
            char a = sectionONE.at(t);
            int temp = t+1;
            char b = sectionONE.at(temp);
            int aValue = alphabet.at(a);
            int bValue = alphabet.at(b);
            

                cout << m << " " << n << " " << o << " " << p << endl;
            int Avalue = (m * aValue) + (n * bValue);
            int Bvalue = (o * aValue) + (p * bValue);
            cout << aValue << " " << bValue << endl;
            Avalue = mod2lus(Avalue,26);
            Bvalue  = mod2lus(Bvalue ,26);
            
            a = numAlpha.at(Avalue);
            b = numAlpha.at(Bvalue );
            cout << a << " " << b << endl;
//            sectionONE.replace(t,0,&a);
//            sectionONE.replace(temp,0,&b);
            cout << a << " " << b << endl;
                t+= 1;
            
        }
        
    }else{
        cout << "The Hl fails" << endl;
    }
  
    cout << sectionONE << endl;
    cout << sectionTWO << endl;
    return 0;
}
int mod2lus (int value, int number){
    if (number < 0){
        return mod2lus(value, -number);
    }
    int number2 = value % number;
    if (number2 < 0){
        number2 += number;
    }
    return number2;
}
