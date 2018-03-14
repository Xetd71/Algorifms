#include <iostream>
#include <assert.h>
#include <stdexcept>
#include <string>


#include "int_stack.h"
#include "stack_machine.h"


using namespace std;

void testStack()
{
    xi::IntStack s;

    s.push(42);
    //int a = s.pop();
    assert(s.top() == 42);            // EXPECT_EQ()
    assert(s.pop() == 42);            // EXPECT_EQ()

    // an exception should be thrown
    bool exc = false;
    try {
        s.pop();
    } catch(std::logic_error& /*e*/) {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    // test for overflow
    for(int i = 0; i < xi::IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try {
        s.push(43);
    } catch(std::logic_error& /*e*/) {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    //int b = 0;
}

void testStackMachine()
{
    xi::StackMachine sm;
    xi::PlusOp plusop;
    sm.registerOperation('+', &plusop);

    //int res = sm.calculate("15 10 +");
    int res = sm.calculate("7 8 10 + +");
    int r1 = sm.getStack().top();
    assert(res == 25);
    assert(r1 == 25);

}

static void writeDescription()
{
    cout << "Here is a stack machine program\nYou can use:"
         << "\n\t'+' - Binary plus operation\n\t'/' - Binary division operation"
         << "\n\t'*' - Binary multiclication operation\n\t'~' - Unary inverse operation"
         << "\nIf you want to save results in stack: write 'sr'"
         << "\nIf you don't want to save results in stack: write 'dsr'" << "\nIf you want to exit: write 'exit'" << endl
         << endl;
}

static std::string readExpression()
{
    cout << "Input: ";
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int main()
{
    //cout << "Hello, World!" << endl;
    //testStack();
    //testStackMachine();

    xi::StackMachine sm;
    xi::PlusOp plus;
    xi::DivisionOperation division;
    xi::MultiplicationOperation multiplication;
    xi::InverseOperation inverse;
    sm.registerOperation('+', &plus);
    sm.registerOperation('/', &division);
    sm.registerOperation('*', &multiplication);
    sm.registerOperation('~', &inverse);
    writeDescription();

    std::string input = readExpression();
    bool cleanStack = input != "sr" && input == "dsr";
    while(input != "exit") {
        try {
            if(input == "sr")
                cleanStack = false;
            else if(input == "dsr")
                cleanStack = true;
            else
                cout << "Result: " << sm.calculate(input, cleanStack) << endl;
            cout << endl;
        } catch(std::logic_error err) {
            cout << err.what() << endl;
        }
        input = readExpression();
    }

    return 0;
}