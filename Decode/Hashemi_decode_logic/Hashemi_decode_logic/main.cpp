    //
    //  main.cpp
    //  Hashemi_decode_logic
    //
    //  Created by Chris West on 10/1/16.
    //  Copyright © 2016 Chris West. All rights reserved.
    //

#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
int main(int argc, const char * argv[]) {
    int count = 1, stars = 0, start = 0;
    char asterisk = 42;
    string message = "** MWUULNGXAP 12 15 7 6  ***GHYTRKL MNP 1 0 0 -1 2 3  12* CDM UYKOOKPIRQQN    ";
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
    cout << messageSub << endl;
    cout << messageHil << endl;
    cout << messagePin << endl;
    return 0;
}
