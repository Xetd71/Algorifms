#include <gtest/gtest.h>

#include <climits>   // INT_MAX

#include "../src/stack_machine.h"


/// Fixture class for testing stack machine
class StackMachineTest : public testing::Test {


protected:

    /// Invoked before each test
    virtual void SetUp()
    {


        // TODO: register all necessay operations here

        _sm.registerOperation('+', &_plusop);
        _sm.registerOperation('*', &_multiply);
        _sm.registerOperation('/', &_divide);
        _sm.registerOperation('~', &_inverse);
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() { }

protected:
    xi::StackMachine _sm;           // stack machine itself

    // TODO: add here all operation to be registered for a specific instance of the stack machine,
    // it depends on the individual assignment
    xi::PlusOp _plusop;
    xi::MultiplicationOperation _multiply;
    xi::DivisionOperation _divide;
    xi::InverseOperation _inverse;


}; // class TestMachineTest



TEST(StackMachine, simplest)
{
    using namespace xi;

    xi::StackMachine sm;
}


// tests with the fixture class
TEST_F(StackMachineTest, plusOp1)
{
    int res = _sm.calculate("7 8 10 + +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}


TEST_F(StackMachineTest, plusOp2)
{
    int res = _sm.calculate("8 10 + 7 +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}


TEST_F(StackMachineTest, undefOper1)
{
    // for undefined operation (let it be >) must raise an exception
    EXPECT_THROW(_sm.calculate("10 8 >"), std::logic_error);
}



// TODO: a skeleton for testing operation '-' (minus)
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, minusOp1)
//{
//    int res = _sm.calculate("10 8 -");      // x = 10, y = 8
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 2);
//    EXPECT_EQ(r1, 2);
//}

// TODO: a skeleton for testing operation '*' (multiplication)
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, multiOp1)
{
    int res = _sm.calculate("2 3 *");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 6);
    EXPECT_EQ(r1, 6);
}

// TODO: a skeleton for testing operation '/' (dividing)
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, divOp1)
{
    int res = _sm.calculate("10 2 /");      // x = 10, y = 2
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 5);
    EXPECT_EQ(r1, 5);


    res = _sm.calculate("10 0 /");      // x = 10, y = 0 (see definition!)
    r1 = _sm.getStack().top();
    EXPECT_EQ(res, INT_MAX);            // !! there was a typo in the task definition !!
    EXPECT_EQ(r1, INT_MAX);


}

// TODO: a skeleton for testing operation '?'
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, choiceOp1)
//{
//    int res = _sm.calculate("1 2 3 ?");     // x = 1, y = 2, z = 3
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 2);
//    EXPECT_EQ(r1, 2);
//
//    res = _sm.calculate("0 2 3 ?");         // x = 0, y = 2, z = 3
//    r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 3);
//    EXPECT_EQ(r1, 3);
//}


// TODO: a skeleton for testing operation '='
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, assOp1)
//{
//
//    // note here an operand must be poped from a stack and the result pushed to the stack back
//    // it can be checked in the further tests
//
//    int res = _sm.calculate("1 =");     
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 1);
//    EXPECT_EQ(r1, 1);
//}


// TODO: a skeleton for testing operation '!' 
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, sigChangeOp1)
//{
//
//    int res = _sm.calculate("1 !");
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, -1);
//    EXPECT_EQ(r1, -1);
//}


// TODO: a skeleton for testing operation '~' 
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, inverOp1)
{

    int res = _sm.calculate("0 ~");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, ~0);
    EXPECT_EQ(r1, ~0);                  // real inversion operator
}


// TODO: a skeleton for testing operation '&' 
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, andOp1)
//{
//
//    int res = _sm.calculate("1 3 &");
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 1 & 3);
//    EXPECT_EQ(r1, 1 & 3);                  
//}

// TODO: a skeleton for testing operation '|' 
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, orOp1)
//{
//
//    int res = _sm.calculate("1 3 |");
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 1 | 3);
//    EXPECT_EQ(r1, 1 | 3);
//}


// TODO: a skeleton for testing operation '^' 
// will produce std::logic_error("No operation defined" for undefined operation
//TEST_F(StackMachineTest, powOp1)
//{
//
//    int res = _sm.calculate("2 3 ^");
//    int r1 = _sm.getStack().top();
//    EXPECT_EQ(res, 8);
//    EXPECT_EQ(r1, 8);
//}


