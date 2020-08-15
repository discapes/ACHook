#pragma once
#include <iostream>
#include <string> 
using namespace std;

inline void printHex(string name, long value) {
	cout << name << ": 0x" << hex << uppercase << value << endl;
}

inline void printDec(string name, long value) {
	cout << name << ": " << dec << value << endl;
}