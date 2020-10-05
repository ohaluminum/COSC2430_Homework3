#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

struct expression
{
    string info = "";
    expression* prev = nullptr;
    expression* next = nullptr;
};

class expressionList
{
private:
    expression* head;
    expression* tail;
    int size;

public:
    //Default constructor
    class expressionList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    //Getter
    expression* getHead()
    {
        return head;
    }

    void addAtEnd(string info)
    {
        //1.Create a temp expression
        expression* temp = new expression();

        //2.Fill the data
        temp->info = info;
        temp->next = nullptr;

        //3.Update the pointer
        if (size == 0)
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

//Remove space from a string
string removeSpace(string line)
{
    string newStr = "";

    for (unsigned int i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            newStr += line[i];
        }
    }

    return newStr;
}


//MUNUALLY IMPLEMENT STACK

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");
    //string command = am.get("command");

    //Test
    string input = "input33.txt";
    string output = "output31.txt";
    string command = "command31.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    //Open input file
    inFS.open(input);
    outFS.open(output);

    try
    {
        //Throw exception if the file doesn't exist
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        //Throw exception if the file is empty
        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        string originalLine = "";
        string newLine = "";

        expressionList EList;

        // --------------------------------------------- ADD EXPRESSION -------------------------------------

        while (getline(inFS, originalLine))
        {
            //Check if the line is empty
            if (originalLine.empty())
            {
                continue;
            }

            newLine = removeSpace(originalLine);

            EList.addAtEnd(newLine);
        }



        //Testing purpose
        expression* temp = EList.getHead();

        while (temp != nullptr)
        {
            cout << temp->info << endl;
            temp = temp->next;
        }

    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    //Close files
    inFS.close();
    outFS.close();

    return 0;
}