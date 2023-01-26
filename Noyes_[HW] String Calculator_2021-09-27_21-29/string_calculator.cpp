#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    if (digit != '0' && digit != '1' && digit != '2' && digit != '3' && digit != '4' && digit != '5' && digit != '6' && digit != '7' && digit != '8' && digit != '9') {
        throw std::invalid_argument("not a single digit");
    }
    int decimal = digit - '0';
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    if (decimal >= 10) {
        throw std::invalid_argument("out of range");
    }
    char digit = decimal + '0';
    return digit;
}

string trim_leading_zeros(string num) {
    int j = num.size();
    bool test = false;
    for (int i = 0; i < j; i++) {
        if (num.at(0) == '0') {
            num.replace(0, 1, "");
        }
        else if (num.at(0) == '-') {
            num.replace(0, 1, "");
            test = true;
        }
        else if (num.at(0) != '0') {
            if (test) {
                num.insert(0, "-");
            }
            return num;
        }
    }
    return "0";
}

string add(string lhs, string rhs) {

    // variables kept outside loop
    int j;
    string final;
    char hold_1st_digit;
    int lhs_length = lhs.size();
    int rhs_length = rhs.size();
    bool carry = false;
    bool lhs_neg = false;
    bool rhs_neg = false;

    // strip any leading zeroes
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    // test for negatives
    if (lhs.at(0) == '-') {
        lhs.replace(0, 1, "");
        lhs_length = lhs.size();
        lhs_neg = true;
    }
    if (rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
        rhs_length = rhs.size();
        rhs_neg = true;
    }

    // test for longer string
    if (lhs_length > rhs_length) {
        j = lhs_length;
    }
    else if (rhs_length >= lhs_length) {
        j = rhs_length;
    }

    // main addition function
    for (int i = 0; i < j; i++) {
        string hold = "";
        lhs_length = lhs.size();
        rhs_length = rhs.size();
        if (rhs_length == 0 && lhs_length > 0) {
            j = lhs_length;
            for (int k = 0; k < j; k++) {
                hold = "";
                lhs_length = lhs.size();
                int a = digit_to_decimal(lhs.at(lhs_length - 1));
                if (carry) {
                    a += 1;
                    carry = false;
                }
                if (a >= 10) {
                    hold_1st_digit = decimal_to_digit(a - 10);
                    carry = true;
                }
                else {
                    hold_1st_digit = decimal_to_digit(a);
                }
                hold += hold_1st_digit;
                final.insert(0, hold);
                if (carry && lhs_length == 1) {
                    final.insert(0, "1");
                }
                lhs.replace(lhs_length - 1, 1, "");
            }
            if (lhs_neg == true && rhs_neg == true) {
                final.insert(0, 1, '-');
            }
            return final;
        }
        if (lhs_length == 0 && rhs_length > 0) {
            j = rhs_length;
            for (int k = 0; k < j; k++) {
                hold = "";
                rhs_length = rhs.size();
                int a = digit_to_decimal(rhs.at(rhs_length - 1));
                if (carry) {
                    a += 1;
                    carry = false;
                }
                if (a >= 10) {
                    hold_1st_digit = decimal_to_digit(a - 10);
                    carry = true;
                }
                else {
                    hold_1st_digit = decimal_to_digit(a);
                }
                hold += hold_1st_digit;
                final.insert(0, hold);
                if (carry && rhs_length == 1) {
                    final.insert(0, "1");
                }
                rhs.replace(rhs_length - 1, 1, "");
            }
            if (lhs_neg == true && rhs_neg == true) {
                final.insert(0, 1, '-');
            }
            return final;
        }
        int a = digit_to_decimal(lhs.at(lhs_length - 1));
        int b = digit_to_decimal(rhs.at(rhs_length - 1));
        int hold_sum = a + b;
        if (carry) {
            hold_sum += 1;
            carry = false;
        }

        // check if a 1 needs to be carried over
        if (hold_sum >= 10) {
            hold_1st_digit = decimal_to_digit(hold_sum - 10);
            carry = true;
        }
        else {
            hold_1st_digit = decimal_to_digit(hold_sum);
        }
        hold += hold_1st_digit;
        final.insert(0, hold);
        if (carry && (lhs_length == 1 && rhs_length == 1)) {
            final.insert(0, "1");
        }
        lhs.replace(lhs_length - 1, 1,  "");
        rhs.replace(rhs_length - 1, 1,  "");
    }
    if (lhs_neg == true && rhs_neg == true) {
        final.insert(0, 1, '-');
    }
    return final;
}

string multiply(string lhs, string rhs) {

    // variables kept outside loop
    string final;
    string final_add;
    string final_hold;
    string hold_string;
    string string_carry1;
    string string_mult;
    int j = 0;
    int k = 0;
    int lhs_length = lhs.size();
    int rhs_length = rhs.size();
    int hold_mult;
    int carry = 0;
    int added = 0;
    int hold_int;
    char hold_1st;
    bool carry_exists = false;
    bool lhs_neg = false;
    bool rhs_neg = false;
    
    // strip any leading zeroes
    lhs = trim_leading_zeros(lhs);
    lhs_length = lhs.size();
    rhs = trim_leading_zeros(rhs);
    rhs_length = rhs.size();

    // check for negatives
    if (lhs.at(0) == '-') {
        lhs.replace(0, 1, "");
        lhs_length = lhs.size();
        lhs_neg = true;
    }
    if (rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
        rhs_length = rhs.size();
        rhs_neg = true;
    }

    // test for longer string and main multiplication
    if (lhs_length >= rhs_length) {
        j = rhs_length;
        k = lhs_length;
        for (int i = 0; i < j; i++) {
            final = "";
            int a = digit_to_decimal(rhs.at(rhs.size() - 1 - i));
            for (int l = 0; l < k; l++) {
                int b = digit_to_decimal(lhs.at(lhs.size() - 1 - l));
                hold_mult = a * b;
                added = 0;

                if (l == 0 && hold_mult >= 10) {
                    hold_string = "";
                    carry = hold_mult / 10;
                    carry_exists = true;
                    hold_int = hold_mult % 10;
                    hold_1st = decimal_to_digit(hold_int);
                    hold_string += hold_1st;
                    final.insert(0, hold_string);
                }

                else if (hold_mult >= 10 && l != 0) {
                    if (carry_exists) {
                        carry_exists = false;
                        added = hold_mult + carry;
                        carry = 0;
                        if (added >= 10) {
                            hold_string = "";
                            carry = added / 10;
                            carry_exists = true;
                            hold_1st = decimal_to_digit(added % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                        else if (added < 10 && added != 0) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(added);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }
                    else if (!carry_exists) {
                        if (hold_mult >= 10) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(hold_mult % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                            carry_exists = true;
                            carry = hold_mult / 10;
                        }
                        else if (hold_mult < 10) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(hold_mult % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }                
                }

                else if (hold_mult < 10) {
                    if (carry_exists) {
                        carry_exists = false;
                        added = hold_mult + carry;
                        carry = 0;
                        if (added >= 10) {
                            hold_string = "";
                            carry = added / 10;
                            carry_exists = true;
                            hold_1st = decimal_to_digit(added % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                        else if (added < 10 && added != 0) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(added);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }
                    else if (!carry_exists) {
                        hold_string = "";
                        hold_1st = decimal_to_digit(hold_mult);
                        hold_string += hold_1st;
                        final.insert(0, hold_string);
                    }   
                }
            }
            if (carry_exists) {
                hold_string = "";
                hold_1st = decimal_to_digit(carry);
                hold_string += hold_1st;
                final.insert(0, hold_string);
                carry_exists = false;
            }
            if (i == 0) {
                final = trim_leading_zeros(final);
                if (final == "0") {
                    final_add.insert(0, "");
                }
                else if (final != "0") {
                    final_add.insert(0, final);
                }
            }
            else if (i > 0) {
                for (int x = 0; x < i; x++) {
                    final.push_back('0');
                }
                final_hold = add(final, final_add);
                final_add = "";
                final_add.insert(0, final_hold);
            }
        }
        if ((lhs_neg && !rhs_neg) || (!lhs_neg && rhs_neg)) {
            final_add.insert(0, 1, '-');
        }
        return final_add;
    }

    if (rhs_length > lhs_length) {
        j = lhs_length;
        k = rhs_length;
        for (int i = 0; i < j; i++) {
            final = "";
            int a = digit_to_decimal(lhs.at(lhs.size() - 1 - i));

            for (int l = 0; l < k; l++) {

                int b = digit_to_decimal(rhs.at(rhs.size() - 1 - l));
                hold_mult = a * b;
                added = 0;

                if (l == 0 && hold_mult >= 10) {
                    hold_string = "";
                    carry = hold_mult / 10;
                    carry_exists = true;
                    hold_int = hold_mult % 10;
                    hold_1st = decimal_to_digit(hold_int);
                    hold_string += hold_1st;
                    final.insert(0, hold_string);
                }

                else if (hold_mult >= 10 && l != 0) {
                    if (carry_exists) {
                        carry_exists = false;
                        added = hold_mult + carry;
                        carry = 0;
                        if (added >= 10) {
                            hold_string = "";
                            carry = added / 10;
                            carry_exists = true;
                            hold_1st = decimal_to_digit(added % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                        else if (added < 10 && added != 0) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(added);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }
                    else if (!carry_exists) {
                        if (hold_mult >= 10) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(hold_mult % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                            carry_exists = true;
                            carry = hold_mult / 10;
                        }
                        else if (hold_mult < 10) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(hold_mult % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }                
                }

                else if (hold_mult < 10) {
                    if (carry_exists) {
                        carry_exists = false;
                        added = hold_mult + carry;
                        carry = 0;
                        if (added >= 10) {
                            hold_string = "";
                            carry = added / 10;
                            carry_exists = true;
                            hold_1st = decimal_to_digit(added % 10);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                        else if (added < 10 && added != 0) {
                            hold_string = "";
                            hold_1st = decimal_to_digit(added);
                            hold_string += hold_1st;
                            final.insert(0, hold_string);
                        }
                    }
                    else if (!carry_exists) {
                        hold_string = "";
                        hold_1st = decimal_to_digit(hold_mult);
                        hold_string += hold_1st;
                        final.insert(0, hold_string);
                    }   
                }
            }
            if (carry_exists) {
                hold_string = "";
                hold_1st = decimal_to_digit(carry);
                hold_string += hold_1st;
                final.insert(0, hold_string);
                carry_exists = false;
            }
            if (i == 0) {
                final = trim_leading_zeros(final);
                if (final == "0") {
                    final_add.insert(0, "");
                }
                else if (final != "0") {
                    final_add.insert(0, final);
                }
            }
            else if (i > 0) {
                for (int x = 0; x < i; x++) {
                    final.push_back('0');
                }
                final_hold = add(final, final_add);
                final_add = "";
                final_add.insert(0, final_hold);
            }
        }
        if ((lhs_neg && !rhs_neg) || (!lhs_neg && rhs_neg)) {
            final_add.insert(0, 1, '-');
        }
        return final_add;
    }
    return "";
}
