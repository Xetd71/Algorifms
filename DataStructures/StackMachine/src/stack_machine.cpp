#include "stack_machine.h"
#include <algorithm>
#include <list>
#include <string>
#include <limits.h>

namespace xi {

#pragma region Helpers

    /**
    Returns a string list that contains the substrings in this instance that are delimited by symbol
    \param s dividend string
    \param symbol
    */
    std::list<std::string> split(const std::string& s, char symb)
    {
        std::list<std::string> chunks;
        std::string chunk = "";
        for(size_t i = 0; i < s.length(); i++) {
            if(s[i] == symb) {
                chunks.push_back(chunk);
                chunk = "";
            } else
                chunk += s[i];
        }
        chunks.push_back(chunk);
        return chunks;
    }

    /**string of digits*/
    const std::string digits = "0123456789";

    /**
    Determines is the given symbol is digit
    \param c given symbol
    */
    bool isDigit(char c)
    {
        for(size_t i = 0; i < digits.length(); i++)
            if(c == digits[i])
                return true;
        return false;
    }

    /**
    Converts the string representation of a number to its positive number equivalent.
    A return value indicates whether the operation succeeded.
    \param s converted string
    \param the number where string will be converted
    */
    bool parseToPositiveNumber(const std::string& s, int& numb)
    {
        if(s.length() == 0)
            return false;
        for(size_t i = 0; i < s.length(); i++)
            if(!isDigit(s[i]))
                return false;
        numb = std::atoi(s.c_str());
        return true;
    }

#pragma endregion

#pragma region Operations
#pragma region Plus

    int PlusOp::operation(char op, int a, int b, int c)
    {
        if(op != '+')
            throw std::logic_error("Operation other than Plus (+) are not supported");

        // here we just ignore unused operands
        return a + b;
    }

    IOperation::Arity PlusOp::getArity() const
    {
        return arDue;
    }

#pragma endregion
#pragma region Multiplication

    int MultiplicationOperation::operation(char op, int a, int b, int c)
    {
        return b * a;
    }

    IOperation::Arity MultiplicationOperation::getArity() const
    {
        return arDue;
    }

#pragma endregion
#pragma region Division

    int DivisionOperation::operation(char op, int a, int b, int c)
    {
        return a == 0 ? b > 0 ? INT_MAX : -INT_MAX : b / a;
    }

    IOperation::Arity DivisionOperation::getArity() const
    {
        return arDue;
    }

#pragma endregion
#pragma region Inverse

    int InverseOperation::operation(char op, int a, int b, int c)
    {
        return ~a;
    }

    IOperation::Arity InverseOperation::getArity() const
    {
        return arUno;
    }

#pragma endregion
#pragma endregion

    void StackMachine::registerOperation(char symb, IOperation* oper)
    {
        SymbolToOperMapConstIter iterator = _opers.find(symb);
        if(iterator != _opers.end())
            throw std::logic_error("An operation '" + std::string(1, symb) + "' is already registered");
        _opers[symb] = oper;
    }

    IOperation* StackMachine::getOperation(char symb)
    {
        SymbolToOperMapConstIter iterator = _opers.find(symb);
        return iterator != _opers.end() ? iterator->second : nullptr;
    }

    int StackMachine::calculate(const std::string& expr, bool clearStack)
    {
        if(clearStack)
            _s.clear();
        std::list<std::string> operations = split(expr, ' ');
        for(std::list<std::string>::const_iterator i = operations.begin(); i != operations.end(); i++) {
            std::string chunk = *i;
            int n;
            if(parseToPositiveNumber(chunk, n))
                _s.push(n);
            else if(chunk.length() == 1) {
                char operationSymbol = chunk[0];
                IOperation* operation = this->getOperation(operationSymbol);
                if(operation == nullptr)
                    throw std::logic_error("An operation '" + std::string(1, operationSymbol) + "' is undefined");

                int arguments[3] = {0, 0, 0};
                for(int i = 0; i < operation->getArity() + 1; i++)
                    arguments[i] = _s.pop();
                _s.push(operation->operation(operationSymbol, arguments[0], arguments[1], arguments[2]));
            } else
                throw std::logic_error("The expression is not valid");
        }
        return _s.top();
    }
} // namespace xi
