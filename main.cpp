#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

// ------------------------------------------------ STACK ------------------------------------------------

struct node
{
    string info = "";
    node* next = nullptr;
};

class stack
{
private:
    node* topNode;

public:
    //Default contructor
    stack()
    {
        topNode = nullptr;
    }

    bool isEmpty()
    {
        if (topNode == nullptr)
        {
            return true;
        }

        return false;
    }

    void push(string newStr)
    {
        node* temp = new node;
        temp->info = newStr;

        temp->next = topNode;
        topNode = temp;
    }

    string top()
    {
        //Check if the stack is empty
        if (!isEmpty())
        {
            return topNode->info;
        }
        else
        {
            cout << "Stack is empty." << endl;
        }
    }

    void pop()
    {
        if (!isEmpty())
        {
            node* temp = new node;
            temp = topNode;

            topNode = topNode->next;
            delete temp;
        }
        else
        {
            cout << "Stack is empty." << endl;
        }
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
    for (unsigned int i = 0; i < line.length(); i++)
    {
        if (line[i] == '(')
        {
            return true;
        }
    }

    return false;
}

//Create a function to convert prefix to postfix
void prefixToPostfix(string& expression)
{
    stack st;
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
    stack st;
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

    expression* getTail()
    {
        return tail;
    }

    int getSize()
    {
        return size;
    }

    // -------------------------------------------------- ADD FUNCTION ----------------------------------- 
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

    // -------------------------------------------------- REMOVE FUNCTION ------------------------------------------
    void removeAtBeg()
    {
        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (size == 0)
        {
            return;
        }

        else if (size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }

        else if (size > 1)
        {
            temp = head;
            head = head->next;
            head->prev = nullptr;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;
    }

    void removeAtMid(int pos)
    {
        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (size == 0)
        {
            return;
        }

        //Invailid position
        if (pos >= size)
        {
            return;
        }

        if (pos <= 0)
        {
            removeAtBeg();
            return;
        }
        else if (pos == size - 1)
        {
            removeAtEnd();
            return;
        }
        else
        {
            expression* previous = new expression;
            previous = head;

            for (int i = 0; i < pos - 1; i++)
            {
                previous = previous->next;
            }

            temp = previous->next;
            previous->next = temp->next;
            temp->next->prev = previous;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;
    }

    void removeAtEnd()
    {
        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (size == 0)
        {
            return;
        }

        else if (size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }

        else if (size > 1)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;
    }

    // -----------------------------------------------------SEARCH FUNCTION ---------------------------------

    int searchExpression(string condition, istringstream& inSS)
    {
        int counter = 0;
        string bin;
        string type;

        expression* temp = new expression;
        temp = head;

        while (temp != nullptr)
        {
            bin = temp->info;
            inSS.clear();
            inSS.str(bin);

            getline(inSS, type, ':');

            if (type == condition)
            {
                counter++;
            }

            temp = temp->next;
        }

        return counter;
    }

    // -------------------------------------------------- OTHER FUNCTIONALITY ----------------------------------

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

    //Task 2: removeList
    void removeList(string condition, istringstream& inSS)
    {
        if (condition == "prefix" || condition == "postfix")
        {
            expression* temp = new expression();
            temp = head;

            string bin;
            string type;
            int index = 0;

            while (temp != nullptr)
            {
                bin = temp->info;
                inSS.clear();
                inSS.str(bin);

                getline(inSS, type, ':');

                if (type == condition)
                {
                    removeAtMid(index);
                    break;
                }

                temp = temp->next;
                index++;
            }
        } 
        else if (condition == "all")
        {
            removeAtEnd();
        }
        else
        {
            int position = stoi(condition);
            removeAtMid(position);
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
        int numOfRemoval = 0;

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

                //Task 1: convertList()
                if (commandType == "convertList ")
                {
                    EList.convertList(commandObject, inSS);
                }

                //Task 2: removeList()
                else if (commandType == "removeList ")
                {
                    //Detemine the number of 
                    if (commandObject == "prefix" || commandObject == "postfix")
                    {
                        numOfRemoval = EList.searchExpression(commandObject, inSS);
                    }
                    else if (commandObject == "all")
                    {
                        numOfRemoval = EList.getSize();
                    }
                    else
                    {
                        numOfRemoval = 1;
                    }

                    for (int i = 0; i < numOfRemoval; i++)
                    {
                        EList.removeList(commandObject, inSS);
                    }
                }






            }
            else
            {
                //Task 3: printList()
                if (commandLine == "printList")
                {
                    EList.printList(outFS);
                }

                //Task 4: printListBackwards()
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

        cout << endl;

        EList.removeAtMid(3);

        //Testing purpose
        temp = EList.getTail();

        while (temp != nullptr)
        {
            cout << temp->info << endl;
            temp = temp->prev;
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