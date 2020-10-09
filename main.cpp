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
    int size;

public:
    //Default contructor
    stack()
    {
        topNode = nullptr;
        size = 0;
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

        size++;
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
            exit(1);
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

            size--;
        }
        else
        {
            exit(1);
        }
    }

    //Task 8: printReserveSize()
    void printReserveSize(ofstream& outFS)
    {
        outFS << "Reserve Size: " << size << endl << endl;
    }

    //Task 10: printReserveTop()
    void printReserveTop(ofstream& outFS)
    {
        if (topNode == nullptr)
        {
            outFS << "Top of Reserve: EMPTY" << endl << endl;
        }
        else
        {
            outFS << "Top of Reserve: " << top() << endl << endl;
        }
    }
};

// ----------------------------------------------- HELPER FUNCTION ------------------------------------------

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

//Task 9: convertReserve()
void convertReserve(stack st, istringstream& inSS)
{
    string bin;
    string type;
    string expression;

    bin = st.top();
    st.pop();
    inSS.clear();
    inSS.str(bin);

    getline(inSS, type, ':');
    getline(inSS, expression);

    if (type == "prefix")
    {
        prefixToPostfix(expression);
        st.push("postfix:" + expression);
    }

    else if (type == "postfix")
    {
        postfixToPrefix(expression);
        st.push("prefix:" + expression);
    }
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
    void addAtBeg(string info)
    {
        //1.Create a temp expression
        expression* temp = new expression;

        //2.Fill the data
        temp->info = info;
        temp->prev = nullptr;

        //3.Update the pointer
        if (size = 0)
        {
            temp->next = nullptr;
            head = temp;
            tail = temp;
        }
        else if (size > 0)
        {
            head->prev = temp;
            temp->next = head;

            head = temp;
        }

        //4.Update the size
        size++;
    }

    void addAtMid(string info, int pos)
    {
        if (pos <= 0)
        {
            addAtBeg(info);
            return;
        }

        else if (pos >= size)
        {
            addAtEnd(info);
            return;
        }

        else
        {
            //1.Create a temp expression
            expression* temp = new expression;
            temp = head;

            //2.Fill the data
            temp->info = info;

            //3.Update the pointer
            expression* previous = new expression;
            previous = head;

            for (int i = 0; i < pos - 1; i++)
            {
                previous = previous->next;
            }

            temp->next = previous->next;
            previous->next = temp;

            temp->prev = previous;
            temp->next->prev = temp;
        }
        size++;
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

    // -------------------------------------------------- REMOVE FUNCTION ------------------------------------------
    string removeAtBeg()
    {
        string deletedStr = "";

        if (size == 0)
        {
            return deletedStr;
        }

        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (size == 1)
        {
            //Store info
            deletedStr = head->info;
            head = nullptr;
            tail = nullptr;
        }

        else if (size > 1)
        {
            temp = head;
            deletedStr = temp->info;

            head = head->next;
            head->prev = nullptr;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;

        return deletedStr;
    }

    string removeAtMid(int pos)
    {
        string deletedStr = "";

        if (size == 0)
        {
            return deletedStr;
        }

        //Invailid position
        if (pos >= size)
        {
            return deletedStr;
        }

        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (pos <= 0)
        {
            return removeAtBeg();
        }
        else if (pos == size - 1)
        {
            return removeAtEnd();
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
            deletedStr = temp->info;

            previous->next = temp->next;
            temp->next->prev = previous;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;

        return deletedStr;
    }

    string removeAtEnd()
    {
        string deletedStr = "";

        if (size == 0)
        {
            return deletedStr;
        }

        //1.Create a temp expression
        expression* temp = new expression;

        //2.Update the pointer
        if (size == 1)
        {
            //Store info
            deletedStr = head->info;

            head = nullptr;
            tail = nullptr;
        }

        else if (size > 1)
        {
            temp = tail;
            deletedStr = tail->info;

            tail = tail->prev;
            tail->next = nullptr;
        }

        //3.Delete the temp expression
        delete temp;

        //4.Update the size
        size--;

        return deletedStr;
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
    string removeList(string condition, istringstream& inSS)
    {
        string deletedStr = "";

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
                    return removeAtMid(index);
                }

                temp = temp->next;
                index++;
            }
        } 
        else if (condition == "all")
        {
            return removeAtBeg();
        }
        else
        {
            int position = stoi(condition);
            return removeAtMid(position);
        }

        //Make sure something retured
        return deletedStr;
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
        stack ReservedStack;

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
        string deletedExp;
        int insertPosition = 0;

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
                    //Detemine the number of deleted expression
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
                        deletedExp = EList.removeList(commandObject, inSS);
                    }
                }

                //Task 5: pushReserve()
                else if (commandType == "pushReserve ")
                {
                    //Detemine the number of deleted expression
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
                        deletedExp = EList.removeList(commandObject, inSS);

                        //Check if delete an expression
                        if (deletedExp != "")
                        {
                            ReservedStack.push(deletedExp);
                        }
                    }
                }

                //Task 6: popReserve()
                else if (commandType == "popReserve ")
                {
                    insertPosition = stoi(commandObject);

                    if (!ReservedStack.isEmpty())
                    {
                        deletedExp = ReservedStack.top();
                        ReservedStack.pop();


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




                //Task 8: printReserveSize()
                else if (commandLine == "printReserveSize")
                {
                    ReservedStack.printReserveSize(outFS);
                }

                //Task 9: convertReserve()
                else if (commandLine == "convertReserve")
                {
                    convertReserve(ReservedStack, inSS);
                }

                //Task 10: printReserveTop()
                else if (commandLine == "printReserveTop")
                {
                    ReservedStack.printReserveTop(outFS);
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

        deletedExp = EList.removeAtMid(3);

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