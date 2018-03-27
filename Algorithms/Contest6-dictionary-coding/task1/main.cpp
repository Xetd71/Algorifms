#include "ReadWriter.h"
//в ReadWriter.h все подключено (Node.h, string, vector, iostream...)
using namespace std;

// s — исходная строка
// res - вектор троек (offs, len, ch)
// histBufMax, prevBufMax - Макс длины буферов истории и предпросмотра
// функция возвращает список блоков
void encodeLZ77(string& s, vector<Node>& res, int histBufMax, int prevBufMax)
{
    Node match;
    for(int i = 0; i < s.length(); i += match.len + 1)
    {
        int len = 0, pos = i;
        for(int p = i < histBufMax ? 0 : i - histBufMax; p < i; ++p)
        {
            int k = 0;
            for(; s[p + k] == s[i + k] && k <= prevBufMax; ++k);
            if(k > len)
            {
                len = k;
                pos = p;
            }
        }

        match = Node(i - pos, len, s[i + len]);
        res.emplace_back(match);
    }
}

int main(int argc, const char* argv[])
{
    //Здесь предлагается задать размер окна в байтах (отдельно буфера предыстории и предпросмотра)
    //В сумме должны образовывать столько, сколько надо в задании
    //history buffer 3 kb
    int histBufMax = 4 * 1024;
    //preview buffer 1 kb
    int prevBufMax = 5 * 1024;

    ReadWriter rw;
    string s = "";
    rw.readString(s);

    //Основной структурой выбран вектор, так как заранее неизвестно какое количество элементов будет записано
    vector<Node> v;

    encodeLZ77(s, v, histBufMax, prevBufMax);

    rw.writeCode(v);
    return 0;
}