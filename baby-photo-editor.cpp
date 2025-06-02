// FCAI – Structured Programming – 2024 - Assignment 2


// Program Description: The fraction calculator allows the user to input two fractions,the calculator takes these inputs
//                      and carries out basic mathematical operations like addition, subtraction, multiplication and division.

// Last Modification Date: 17/3/2024

// Author1 and ID and Group: Zyad Ashraf El-Sayed    Group A
// Author2 and ID and Group: Nourhan Adel Mohamed    Group A
// Author3 and ID and Group: Mariam Medhat Shawky    Group A

// Emails:  Email Author1: ziadashraf950@gmail.com
//          Email Author2: nourhan.adel.eg@gmail.com
//          Email Author3: medhatmariiam@gmail.com

// Teaching Assistant: Ahmed Fouad Lotfy

// Who did what: Zyad Ashraf El-Sayed : Regex , simplification of fractions , multiplication and Division operations .
//               Nourhan Adel Mohamed : Input Validation and Addition operation.
//               Mariam Medhat Shawky : Input Validation and Subtraction operation.

// Pseudocode of the fraction calculator: https://drive.google.com/file/d/1lxOyEST6WScp9qd1ey0X4HvDWR8mTV9c/view?usp=drive_link

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <limits>
using namespace std;

// Function to print simplified fraction
void printSimplified(long long numerator, long long denominator){
    // calculate the greatest divisor
    long long gcd = __gcd(numerator, denominator);

    denominator = denominator / gcd;            // Simplify the denominator
    numerator = numerator / gcd;                // Simplify the numerator

    // checks if the denominator is one
    if(denominator == 1){
        cout << numerator << endl;
    }

    // check if both numerator and denominator are equal
    else if(denominator == numerator){
        cout  << "1" << endl;
    }

    // checks if the numerator is divisible by the denominator
    else if(numerator % denominator == 0) {
        cout << numerator / denominator << endl;
    }

    // checks if both denominator and numerator are negative, if both are negative flip the sign
    else if(numerator < 0 && denominator < 0 ) {
        cout  << -1 * numerator << "/" << -1 * denominator << endl;
    }
    else {
        cout << numerator << "/" << denominator << endl;
    }
}



// function to perform mathematical operations
void calculator(){
    string equation;              // stores the input entered by the user
    string number = "";           // Only stores the numbers entered by the user

    bool plus_flag;
    bool minus_flag;
    bool multi_flag;
    bool div_flag;

    vector<long long> list;
    long long den_multi;
    long long num_sum;
    long long n_multi;

    // loop iterates until the user enters a valid input
    while (true) {
        cout << "Please enter the two fractions in the form of a/b and c/d and the operator you want between these two fractions " << endl;
        cout << "and separate between each operand and the operator with one space: " << endl;
        getline(cin, equation);


        bool wrg_inp = false;        // Flag to indicate invalid inputs
        bool found_dig = false;      // Flag that checks the presence of numbers

        // Check if the input matches the required format
        if(!regex_match(equation, regex("([+-]?[0-9]+([/]{1}[+-]?[0-9]+)?[ ]{1}[\\+\\-\\*/]{1}[ ]{1}[+-]?[0-9]+([/]{1}[+-]?[0-9]+)?)")
        )){
            cout << "Error, please try again" << endl;
            continue;
        }

        // Reset the flag after each iteration
        plus_flag = false;
        minus_flag = false;
        multi_flag = false;
        div_flag = false;

        for (int i = 0; i < equation.size() ; ++i) {
            // Adding each digit and '-' to the number string
            if (isdigit(equation[i]) || equation[i] == '-') {
                if (equation[i] == '-' && (i == 0 || isdigit(equation[i+1])  || equation[i - 1] == '/')) {
                    number += equation[i];
                }else if (isdigit(equation[i])) {
                    number += equation[i];
                }

            } else {
                if (!number.empty()) {
                    for (char digit : number) {
                        if (isdigit(digit)) {
                            found_dig = true;
                        }
                    }
                    //convert the string to digit, adding it to the list
                    if (found_dig){
                        list.push_back(stoi(number));
                        number = "";               // Reset the number string
                    }
                    number= "";
                }
                // Identify the presence of a space
                if (isspace(equation[i])) {
                    if (list.size() == 0){
                        wrg_inp = true;
                    }
                    // Checks if the number entered is integer or fraction
                    if (list.size() == 1){
                        list.push_back(1);
                    }
                    // Determine the type of operation
                    if (equation[i+1] == '+'){
                        if (minus_flag){
                            plus_flag = false;
                        }
                        else if (multi_flag){
                            plus_flag = false;
                        }
                        else if (div_flag){
                            plus_flag = false;
                        }
                        else {
                            plus_flag = true;
                        }
                    }
                    else if (equation[i+1] == '-'){
                        if (plus_flag){
                            minus_flag = false;
                        }
                        else if (multi_flag){
                            minus_flag = false;
                        }
                        else if (div_flag){
                            minus_flag = false;
                        }
                        else {
                            minus_flag = true;
                        }
                    }
                    else if (equation[i+1] == '*'){
                        multi_flag = true;
                    }
                    else if (equation[i+1] == '/'){
                        div_flag = true;
                    }
                }
            }
        }
        if (wrg_inp){
            cout <<"Error!!"<<endl;            // Display error message
            continue;
        }
        if (!number.empty()) {
            for (char digit : number) {
                if (isdigit(digit)) {
                    found_dig = true;
                }
            }
            if (found_dig){
                list.push_back(stoi(number));
                number = "";
            }
            number= "";
        }

        // Ensure that the list contains only four numbers
        if (list.size() != 4) {
            list.push_back(1);            // set denominator to one if the user enters integers
        }

        if (list.size() != 4) {
            cout << "Error!" << endl;
            list.clear();                // clear the list after each iteration
            number = "";
            continue;
        }
        // check for the division over zero
        if (list[1] == 0 || list[3] == 0) {
            cout << "Error! denominator cannot be zero" << endl;        // Display error message if the denominator is zero
            list.clear();
            number = "";
            continue;
        }
        if (div_flag && list[2] == 0){
            cout <<"Error! denominator cannot be zero"<<endl;
            list.clear();
            number = "";
            continue;
        }
        break;              // Break the loop if the user input is valid
    }

    // If there is addition operation
    if (plus_flag){
        den_multi = list[1] * list[3];                             // Calculate the common denominator
        num_sum = (list[3] * list[0]) + (list[1] * list[2]);       // Calculate the numerator addition
        cout << "The result of addition = ";
        printSimplified(num_sum,den_multi);   // simplify the result
    }

    // If there is subtraction operation
    if (minus_flag){
        den_multi = list[1] * list[3];
        num_sum = (list[3] * list[0]) - (list[1] * list[2]);        // Calculate the numerator difference
        cout << "The result of subtraction = ";
        printSimplified(num_sum,den_multi);
    }

    // If there is multiplication operation
    if (multi_flag){
        // Calculate both numerator and denominator product
        n_multi = list[0] * list[2];
        den_multi = list[1]*list[3];
        cout << "The result of multiplication = ";
        printSimplified(n_multi,den_multi);
    }

    // If there is division operation
    if (div_flag){
        // Calculate both numerator and division
        n_multi = list[0] * list[3];
        den_multi = list[1] * list[2];
        cout << "The result of division = ";
        printSimplified(n_multi,den_multi);
    }

}

int main(){
    // Display welcome message
    cout << "Welcome to our Fraction Calculator!" << endl;

    // Loop that always iterate until the user choose to exit
    while (true) {
        cout << "Please choose an option : " << endl;
        cout << "1. Enter a rational number operation" << endl;
        cout << "2. Exit" << endl;
        cout << "Option 1 or 2 : " << endl;

        // Variable to store the choice of the user
        string option;
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check the validity of the user input
        if ( option != "1" && option != "2"){
            cout << "Invalid option." << endl;
            continue;
        }

        if ( option == "1" ){
            calculator();         // Call the function to perform operations
            continue;
        }

        if ( option == "2" ){
            cout << "Exiting" << endl;
            return 0;
        }
    }
}
