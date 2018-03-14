/*
 * \file
 * \brief код программы SpellChecking
 * \author Чуев Иван БПИ163
 * \date 19.11.2017
 *              Дописана реализация метода checkSpelling
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>

#include <set>

#include "dictionary.h"

using namespace std;

void lower(string& s);

string stripPunct(const string& s);

void checkSpelling(ifstream& in, Dictionary& dict);


int main(int argc, char* argv[])
{
    // Output usage message if improper command line args were given.
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
        return EXIT_FAILURE;
    }

    ifstream inf(argv[2]);
    if(!inf) {
        cerr << "Could not open " << argv[2] << "\n";
        return EXIT_FAILURE;
    }

    // Read dictionary, but let user know what we are working on.
    cout << "Loading dictionary, this may take awhile...\n";

    Dictionary d(argv[1]);

    checkSpelling(inf, d);

    inf.close();

    return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict)
{
    int line_number = 0;

    while(in) {
        //Считаем порядковый номер строки
        ++line_number;

        //Считываем следующую строку
        std::string line;
        getline(in, line);

        //Создаем итерируемую последовательность по строке
        stringstream ss(stringstream::in | stringstream::out);
        ss << line;

        //Выводим рекомендации для каждого не правильного слова в строке
        std::string word;
        while(ss >> word) {
            //Удаляем посторонние символы из слова и приводим его к нижнему регистру
            word = stripPunct(word);
            lower(word);
            //Если слово находится в словаре, то переходим к следующему
            if(dict.search(word) || word.empty())
                continue;

            //Находим коллекцию возможных исправлений слова
            std::string changedWord;
            std::set<std::string> changedWords;
            for(std::size_t i = 0; i < word.length(); i++) {
                //Замена мест двух рядом стоящих букв (Случай 1)
                if(i < word.length() - 1) {
                    changedWord = word;
                    changedWord[i] = word[i + 1];
                    changedWord[i + 1] = word[i];
                    changedWords.insert(changedWord);
                }

                //Удаление одного символа из строки  (Случай 2)
                changedWords.insert(word.substr(0, i) + word.substr(i + 1));

                for(char c = 'a'; c <= 'z'; c++) {
                    //Изменение одного символа  (Случай 3)
                    changedWord = word;
                    changedWord[i] = c;
                    changedWords.insert(changedWord);

                    //Добавление символа в строку  (Случай 4)
                    changedWords.insert(word.substr(0, i) + c + word.substr(i));
                }
            }

            //Добавление символа в конец строки  (Случай 4)
            for(char c = 'a'; c <= 'z'; c++)
                changedWords.insert(word + c);

            //Вывод рекомендаций для слова
            std::cout << "Line " << line_number << ": '" << word << "'" << std::endl;
            std::cout << "\tsuggestions:" << std::endl;

            //Проходимся по списку всех возможных исправлений,
            //и если исправление найдется в словаре, то выводим его на экран
            std::set<std::string>::const_iterator it = changedWords.begin();
            for(; it != changedWords.end(); it++)
                if(dict.search(*it))
                    std::cout << "\t\t" + *it << std::endl;
        }
    }
}

void lower(string& s)
{
    // Ensures that a word is lowercase
    for(int i = 0; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }
}

string stripPunct(const string& s)
{
    // Remove any single trailing
    // punctuation character from a word.
    if(ispunct(s[s.length() - 1]))
        return s.substr(0, s.length() - 1);

    return s;
}
