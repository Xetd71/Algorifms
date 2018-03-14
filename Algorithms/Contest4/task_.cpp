//#include <fstream>
//#include <stdlib.h>
//#include <vector>
//#include <queue>
//using namespace std;
//​
//struct HuffNode
//{
//public:
//    int index;
//    int freq;
//    ​
//    HuffNode *left, *right;
//    ​
//    HuffNode(int ind, int fr)
//    {
//        left = right = nullptr;
//        index = ind;
//        freq = fr;
//    }
//};
//​
//struct compare {
//    ​
//    bool operator()(HuffNode* l, HuffNode* r)
//    {
//        if(l->freq == r->freq)
//        {
//            if(l->index < 0 && r->index >= 0)
//                return false;
//            if(l->index >= 0 && r->index < 0)
//                return true;
//            if(l->index < 0 && r->index < 0)
//                return l->index > r->index;
//            return l->index < r->index;
//        }
//        return (l->freq > r->freq);
//    }
//};
//​
//class Huffman
//{
//public:
//​
//    void build()
//    {
//        // запускает алгоритм (после того как были добавлены все элементы)
//        huff(n);
//    }
//    void addChance (int chance)
//    {
//        codes.emplace_back("");
//        min_heap.push(new HuffNode(n, chance));
//​
//​
//        n++;
//        // добавляет элемент в список (дерево, все зависит от реализации)
//    }
//
//    string get (int i)
//    {
//        return codes[i];
//    }
//​
//    void setCodes(HuffNode *top, string code)
//    {
//        int index = top->index;
//        if(index >= 0)
//        codes[index] = code;
//        else
//        {
//            setCodes(top->left, code + "0");
//            setCodes(top->right, code + "1");
//        }
//    }
//​
//    void huff(int n)
//    {
//        HuffNode *left, *right, *top;
//        while (min_heap.size() != 1)
//        {
//            left = min_heap.top();
//            min_heap.pop();
//            ​
//            right = min_heap.top();
//            min_heap.pop();
//            top = new HuffNode(--curr_pair, left->freq + right->freq);
//            ​
//            top->left = left;
//            top->right = right;
//
//            min_heap.push(top);
//        }
//
//        setCodes(min_heap.top(), "");
//    }
//
//    priority_queue<HuffNode*, vector<HuffNode*>, compare> min_heap;
//    vector<string> codes;
//    int n = 0;
//    int curr_pair = 0;
//};
//
//int main() {
//
//    int n;
//    Huffman * huff = new Huffman();
//    fstream fin;
//    fin.open("input.txt",ios::in);
//    if(fin.is_open()) {
//        fin >> n;
//        for (int i = 0; i < n; i++) {
//            int x;
//            fin >> x;
//            huff->addChance (x);
//        }
//
//        fin.close();
//
//        huff->build();
//        fstream fout;
//        fout.open("output.txt",ios::out);
//        for (int i = 0; i < n; i++){
//            fout << huff->get(i) << (i==n-1?"":" ");
//        }
//        fout.close();
//        delete huff;
//
//    }
//
//    return 0;
//
//}
