#include "subject.h"


namespace xi {


    std::ostream& operator<<(std::ostream& outs, const Subject& subj)
    {
        outs << subj.name << ": " << subj.title << "\n";

        int index = 0;
        int maxSubj = subj.description.getCapacity();               // добавочка по наводке Данила Кашина

        while(index < maxSubj && subj.description[index] != "")
            outs << subj.description[index++] << "\n";

        return outs;
    }

    /*
    returns true, if current string is endline
    \param str - current string
    */
    inline bool isEndLine(const std::string& str)
    {
        return str == "" || str == "\n" || str == "\r" || str == "\n\r";        //detect is 'str' is end of line
    }


    std::istream& operator>>(std::istream& ins, Subject& subj)
    {
        std::getline(ins, subj.name);                       //assign name and title
        std::getline(ins, subj.title);                      //

        int index = 0;
        int maxSubj = subj.description.getCapacity();

        std::string input;
        std::getline(ins, input);
        while(index < maxSubj && !isEndLine(input)) {       //assign description
            subj.description[index++] = input;
            std::getline(ins, input);
        }

        return ins;
    }


} // namespace xi

