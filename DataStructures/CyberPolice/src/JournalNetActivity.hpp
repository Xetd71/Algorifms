/*
 * \file
 * \brief реализация класса JournalNetActivity
 * \author Чуев Иван БПИ163
 * \date 12.11.2017
 *              Дописана реализация метода outputSuspiciousActivities
 */

#include "JournalNetActivity.h"

#include <fstream>

template<int numLevels>
JournalNetActivity<numLevels>::JournalNetActivity(void)
{
}

template<int numLevels>
JournalNetActivity<numLevels>::~JournalNetActivity(void) {}

// Read the whole log from the file on fullpath
template<int numLevels>
void JournalNetActivity<numLevels>::parseLog(string fullpath)
{
    ifstream fin(fullpath); // opens the file

    TimeStamp timestamp; // dummy
    NetActivity netactivity; // dummy

    while(fin) {
        fin >> timestamp;
        if(!fin) break;
        fin >> netactivity.m_user;
        if(!fin) break;
        fin >> netactivity.m_host;
        if(!fin) break;

        m_Journal.insert(netactivity, timestamp);
    }
}

// Just dumps the whole journal to the out stream
template<int numLevels>
void JournalNetActivity<numLevels>::dumpJournal(ostream& out)
{
    typename TypeList::TypeNode* prehead, * run;
    prehead = m_Journal.getPreHead();
    run = prehead;

    // prehead is placed before the first and after the last element
    // So it serves two roles.
    while(run->m_next != prehead) {
        run = run->m_next;
        out << run->m_key;
        out << " ";
        out << run->m_value;
    }
}

// Outputs all net activity between from and to
template<int numLevels>
void JournalNetActivity<numLevels>::outputSuspiciousActivities(string hostSuspicious, const TimeStamp& timeFrom,
                                                               const TimeStamp& timeTo) const
{
    //Если интервал времени не правильно задан метод ничего не выводит
    if(timeTo < timeFrom)
        return;

    //Находим первую запись в списке в заданом интервале
    NodeSkipList<NetActivity, TimeStamp, numLevels>* cNode = m_Journal.findLastLessThan(timeFrom);
    cNode = cNode->m_next;

    //проходимся по интервалу и выводим найденные записи в консоль
    while(cNode->m_key <= timeTo && cNode != m_Journal.getPreHead()) {
        if(cNode->m_value.m_host == hostSuspicious)
            std::cout << cNode->m_value << std::endl;

        cNode = cNode->m_next;
    }
}
