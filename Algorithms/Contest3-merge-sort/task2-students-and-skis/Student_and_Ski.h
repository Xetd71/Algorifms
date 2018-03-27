class Student; //it is important line

class Ski
{
    //this code let us compare student and ski by their private fields
    friend int compare(Student& stud, Ski& ski);
    friend class ReadWriter;

//private:
public:
    int length;

public:
    int id;
};

class Student
{
    //this code let us compare student and ski by their private fields
    friend int compare(Student& stud, Ski& ski);
    friend class ReadWriter;

//private:
public:
    int height;

public:
    int id;
};

/*
Compare student's height and ski's length
Return:
1 if Ski is longer then Student need
0 if Ski is enough for this Student
-1 if Ski is shorter then Student need
*/
int compare(Student& stud, Ski& ski)
{
    int result = 0;

    if (ski.length > stud.height + 5)
        result = 1;

    if (ski.length < stud.height + 5)
        result = -1;

    return result;
}
