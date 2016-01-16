//Name: Keyan Raahemifar, Austin Jabari
//Date: May 21, 2014
//Course: ICS 3UI
//Exercise: Summative
#include <iostream>

#include "Header.h"
    char place[6][7];
    int counter[7];
    
int main()
{
    char choice = ' ';
    game TheOne (0);
    while (choice!='n')
    {

        TheOne.RunGame();
        cout << "Continue to game(y or n)" << endl;
        cin >> choice;
        system("cls");
    }
    cout << "Chuck Norris wishes you a good day!" << endl;

}
