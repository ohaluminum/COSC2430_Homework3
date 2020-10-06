#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "ArgumentManager.h"
using namespace std;

//Create a function to convert prefix to postfix
void prefixToPostfix(string& expression)
{
    stack<string> st;
    string operand;
    string first;
    string second;
    string newStr;

    //Parsing the string from right to left
    for (int i = expression.length() - 1; i >= 0; i--)
    {
        //If prefix[i] is operand (A-Z/a-z)
        if (isalpha(expression[i]))
        {
            operand = "";
            operand += expression[i];

            st.push(operand);
        }

        //If the prefix[i] is operator (+ - * /)
        else
        {
            first = st.top();
            st.pop();

            second = st.top();
            st.pop();

            newStr = first + second + expression[i];
            st.push(newStr);
        }
    }

    expression = st.top();
}

//Create a function to convert postfix to prefix
void postfixToPrefix(string& expression)
{
    stack<string> st;
    string operand;
    string first;
    string second;
    string newStr;

    for (unsigned int i = 0; i < expression.length(); i++)
    {
        //If prefix[i] is operand (A-Z/a-z)
        if (isalpha(expression[i]))
        {
            operand = "";
            operand += expression[i];

            st.push(operand);
        }

        //If the prefix[i] is operator (+ - * /)
        else
        {
            second = st.top();
            st.pop();

            first = st.top();
            st.pop();

            newStr = expression[i] + first + second;
            st.push(newStr);
        }
    }

    expression = st.top();
}

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

    //Task 1: convertList
    void convertList(string condition, istringstream& inSS)
    {
        expression* temp = new expression();
        temp = head;

        string bin;
        string type; 
        string expression;

        if (condition == "prefix")
        {
            while (temp != nullptr)
            {
                bin = temp->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');
                getline(inSS, expression);
                
                if (type == "prefix")
                {
                    prefixToPostfix(expression);
                    temp->info = "postfix:" + expression;
                }

                temp = temp->next;
            }
        }
        else if (condition == "postfix")
        {
            while (temp != nullptr)
            {
                bin = temp->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');
                getline(inSS, expression);

                if (type == "postfix")
                {
                    postfixToPrefix(expression);
                    temp->info = "prefix:" + expression;
                }

                temp = temp->next;
            }
        }
        else if (condition == "all")
        {
            while (temp != nullptr)
            {
                bin = temp->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');
                getline(inSS, expression);

                if (type == "prefix")
                {
                    prefixToPostfix(expression);
                    temp->info = "postfix:" + expression;
                }

                else if (type == "postfix")
                {
                    postfixToPrefix(expression);
                    temp->info = "prefix:" + expression;
                }

                temp = temp->next;
            }
        }
        else
        {
            int position = stoi(condition);

            //Change the first node
            if (position <= 0)
            {
                bin = head->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');
                getline(inSS, expression);

                if (type == "prefix")
                {
                    prefixToPostfix(expression);
                    head->info = "postfix:" + expression;
                }
                else if (type == "postfix")
                {
                    postfixToPrefix(expression);
                    head->info = "prefix:" + expression;
                }
            }
            else if (position > 0 && position < size)
            {
                //Move to the correct position
                for (int i = 0; i < position; i++)
                {
                    temp = temp->next;
                }

                bin = temp->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');
                getline(inSS, expression);

                if (type == "prefix")
                {
                    prefixToPostfix(expression);
                    temp->info = "postfix:" + expression;
                }
                else if (type == "postfix")
                {
                    postfixToPrefix(expression);
                    head->info = "prefix:" + expression;
                }
            }
        }
    }

    //Task 3: printList
    void printList(ofstream& outFS)
    {
        outFS << "List:" << endl;

        if (size == 0)
        {
            outFS << "EMPTY" << endl;
        }
        else if (size > 0)
        {
            expression* temp = new expression();
            temp = head;

            while (temp != nullptr)
            {
                outFS << temp->info << endl;
                temp = temp->next;
            }
        }

        outFS << endl;
    }

    //Task 4: printListBackwards
    void printListBackwards(ofstream& outFS)
    {
        outFS << "Reversed List:" << endl;

        if (size == 0)
        {
            outFS << "EMPTY" << endl;
        }
        else if (size > 0)
        {
            expression* temp = new expression();
            temp = tail;

            while (temp != nullptr)
            {
                outFS << temp->info << endl;
                temp = temp->prev;
            }
        }

        outFS << endl;
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

//Check if the command line contains parenthese
bool hasParentheses(string line)
{
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '(')
        {
            return true;
        }
    }

    return false;
}




//MUNUALLY IMPLEMENT STACK



// --------------------------------------------- MAIN FUNCTION --------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    //string input = am.get("input");
    //string output = am.get("output");
    //string command = am.get("command");

    //Test
    string input = "input30.txt";
    string output = "output31.txt";
    string command = "command30.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    try
    {
        //Open input file and output file  
        inFS.open(input);
        outFS.open(output);

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

        //Close input file
        inFS.close();

        //Open command file
        inFS.open(command);

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

        string commandLine;
        string commandType;
        string commandObject;
        bool hasMoreCommand;

        while (getline(inFS, commandLine))
        {
            //Check if the line is empty
            if (commandLine.empty())
            {
                continue;
            }

            hasMoreCommand = hasParentheses(commandLine);

            if (hasMoreCommand)
            {
                inSS.clear();
                inSS.str(commandLine);

                getline(inSS, commandType, '(');
                getline(inSS, commandObject, ')');

                //Task 1
                if (commandType == "convertList ")
                {
                    EList.convertList(commandObject, inSS);
                }



            }
            else
            {
                //Task 3
                if (commandLine == "printList")
                {
                    EList.printList(outFS);
                }

                //Task 4
                else if (commandLine == "printListBackwards")
                {
                    EList.printListBackwards(outFS);
                }

            }

            

            

            
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