#pragma once
typedef unsigned int word;

word atom(char* ch);	// Transform string into binary number
char* mtoa(word num);	// Transform binary number into string
word madd(word m, word n); // Addition 
word msub(word m, word n); // Substraction 
word mmul(word m, word n); // Multiplication
word mdiv(word m, word n); // Division
word mmod(word m, word n); // Modulus