#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

struct expression
{
    string info;
    expression* prev;
    expression* next;
};

class expList
{
private:
    expression* head;
    expression* tail;
    int size;

public:
    //Default constructor
    class expList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void addAtEnd(string info)
    {
        //1.Create a temp expression
        expression* temp = new expression();

        //2.Fill the data
        temp->info = info;
        temp->next = nullptr;

        //3.Update the pointer
        if (size = 0)
        {
            temp->prev = nullptr;
            head = temp;
            tail = temp;
        }
        else if (size > 0)
        {
            tail->next = temp;
            temp->prev = tail;

            tail = temp;
        }

        //4.Update the size
        size++;
    }



};


//MUNUALLY IMPLEMENT STACK

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