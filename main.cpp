#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");
    //string command = am.get("command");

    //Test
    string input = "input31.txt";
    string output = "output31.txt";
    string command = "command31.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    //Open input file
    inFS.open(input);
    outFS.open(output);




    //Close files
    inFS.close();
    outFS.close();

    return 0;
}