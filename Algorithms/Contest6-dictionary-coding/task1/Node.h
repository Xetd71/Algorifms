//block look like:  <offs,len,ch> example: <3,2,d>
class Node
{
public:
    //everything public
    int offs;
    int len;
    char ch;

    Node(int o, int l, char c) : offs(o), len(l), ch(c)
    {};

    Node()
    {};

};