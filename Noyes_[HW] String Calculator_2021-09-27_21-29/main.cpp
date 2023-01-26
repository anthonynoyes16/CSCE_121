#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    // main code
    string user_input = "";
    cout << ">> ";
    getline(cin, user_input);
    while (user_input != "q" && user_input != "quit") {
        int req_add = 0;
        int req_mult = 0;
        string a = "";
        string b = "";
        req_add = user_input.find('+');
        req_mult = user_input.find('*');
        if (req_add >= 0) {
            a = user_input.substr(0, req_add - 1);
            b = user_input.substr(req_add + 2, user_input.size() - 1);
            cout << endl;
            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << add(a, b) << endl;
            cout << endl;
        }
        if (req_mult >= 0) {
            a = user_input.substr(0, req_mult - 1);
            b = user_input.substr(req_mult + 2, user_input.size() - 1);
            cout << endl;
            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << multiply(a, b) << endl;
            cout << endl;
        }
        cout << ">> ";
        getline(cin, user_input);
    }
    cout << "farvel!" << endl;

}

