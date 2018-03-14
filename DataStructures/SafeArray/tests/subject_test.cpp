#include <gtest/gtest.h>

#include <fstream>

#include "../src/subject.h"


// TODO: укажите здесь абсолютный путь к файлу с описанием предметов
static const char* TEST_FNAME = "../../subjects.txt";

// число описаний курсов в файле
static const int SUBS_NUM = 10;


// для gcc нужно явно определять создание объекта, когда для MSVC и без этого прокатит:
// ошибке redefinition; multiple initialization
// http://www.stroustrup.com/bs_faq2.html#in-class
// Определение (создание) объекта должно встречаться строго только в одном модуле трансляции.
const int xi::Subject::MAX_LINES;


// Вспомогательный метод, загружающий список предметов из текстового файла, имя
// которого передается параметром
// Список загружается в передаваемый по ссылке объект ar
// Использование передачи объектов по значению в данном случае является дорогим и нерациональным
void loadSubjects(const char* fn, xi::SafeArray<xi::Subject>& subjs)
{
    using namespace std;

    // пытаемся открыть файл для чтения
    ifstream inf(fn);
    bool fileNotOpen = !inf;
    ASSERT_FALSE(fileNotOpen);

    // пытаемся вычитать текстовый файл строку за строкой
    try {
        for(int i = 0; i < SUBS_NUM; i++) {
            inf >> subjs[i];
        }
    } catch(out_of_range e) {
        cerr << "Error reading file" << fn << endl;
    }

    inf.close();
}

TEST(Subject, simplest)
{
    using namespace xi;

    Subject s;
}


TEST(Subject, OpenDemoFile)
{
    using namespace xi;

    xi::SafeArray<xi::Subject> subjs(SUBS_NUM);
    loadSubjects(TEST_FNAME, subjs);
}


TEST(Subject, DemoFile1)
{
    using namespace xi;

    xi::SafeArray<xi::Subject> subjs(SUBS_NUM);
    loadSubjects(TEST_FNAME, subjs);

    EXPECT_EQ(subjs[1].name, "SSD2");
    EXPECT_EQ(subjs[1].title, "Introduction to Computer Systems");

    // след. две строки эквивалентны
    EXPECT_EQ(subjs[1].description.getCapacity(), subjs[1].MAX_LINES);
    EXPECT_EQ(subjs[1].description.getCapacity(), xi::Subject::MAX_LINES);
}
