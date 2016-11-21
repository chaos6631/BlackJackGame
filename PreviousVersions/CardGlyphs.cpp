/*
* Project Name: Lab ?:
* Author: Chris Calder #100601097
* Date: 
*
* Description:  A C++ program that ....
*				
*/

#include <iostream>
#include <iomanip> 					// for output formatting
#include <string>					// for string
#include <sstream>					// for stringstream
#include <cstdlib>					// for system()
#include <clocale>
#include <cstdio>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

#pragma execution_character_set( "utf-8" )
//#include "TempTrackerFunctions.h"	// for external file

using namespace std;


int main()
{
    SetConsoleOutputCP(65001);
    _setmode(_fileno(stdout), _O_WTEXT);
        
    const wchar_t wclubs[] = L"\u2663";
    
    wcout << wclubs << endl;
    //cout << wclubs << endl;
    wcout << L"\u2663"; //Clubs
    wcout << L"\u2665"; //Hearts
    wcout << L"\u2660"; //Spades
    wcout << L"\u2666"; //Diamonds
    return 0;
}

