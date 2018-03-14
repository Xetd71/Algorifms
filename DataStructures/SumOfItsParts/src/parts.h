/**
 *  \file
 *  \brief реализация классов Part и NameContainer
 *  \author Чуев Иван БПИ163
 *  \date 30.11.2017
 *              Написана реализация класса Part, добавлен метод на *(count_howmanyUp).
 *              Добавлен вспомогательный метод addSubPart для удобной поддержки метода на *.
 *              К классу Part написаны тесты, которые находятся в файле: tests\Part_Student_Tests.cpp
 *
 *              Написана реализация класса NameContainer, добавлена большая тройка
 *              К классу NameContainer написаны тесты, которые находятся в файле: tests\NameContainet_Student_Tests.cpp
 */

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

//**************** Part ****************
class Part {
public:

    /** \brief Имя части*/
    std::string name;

    /** \brief Ссылка на родительский объект, если он есть*/
    Part* parent;

    /** \brief Колекция объектов с соответстующим им колличеством */
    std::map<Part const*, int> subparts;

    /** \brief Конструктор, создающий объект
     *  \param n - Имя обекта
     */
    Part(std::string const& n) : name(n), parent(nullptr) {};

    /** \brief Метод, выводящий информацию об объекте в консоль */
    void describe();

    /** \brief Метод, рекурсивно подсчитывающий колличество объектов p
     *  \param p - объект, колличество которого надо подсчитать
     *  \return колличество объектов p
     */
    int count_howmany(Part const* p) const;

    /** \brief Метод, подсчитывающий колличество объектов p, используя ссылку на parent
     *  \param p - объект, колличество которого надо подсчитать
     *  \return колличество объектов p
     */
    int count_howmanyUp(Part const* p) const;

    /** \brief Добавляет объект p в _subparts, указывая колличество p
     *  \param p - добавляемый объект
     *  \param q - колличество объектов p
     */
    void addSubPart(Part* p, int q);
};

//**************** NameContainer ****************
class NameContainer {
public:
    /** \brief  Конструктор по умолчанию */
    NameContainer() {};

    /** \brief  Деструктор */
    ~NameContainer();

    /** \brief Конструктор копирования */
    NameContainer(const NameContainer& obj);

    /** \brief Оператор копирования */
    NameContainer& operator=(const NameContainer& obj);

    /** \brief Метод поиска части, если честь не найдена,
     *          то она создается и добавляется в name_part
     *  \param name - имя части
     *  \return найденная часть
     */
    Part* lookup(std::string const& name);

    /** \brief Метод, добавления элеимента в контейнер
     *  \param x - имя части
     *  \param y - имя подчасти
     *  \param q - колличество объектов y
     */
    void add_part(std::string const& x, int q, std::string const& y);

    /** \brief Меняет содержимое объектов местами
     *  \param first - первый объект
     *  \param second - второй объект
     */
    friend void swap(NameContainer& first, NameContainer& second);

private:
    /** \brief Коллекция имен частей с соответствующими им частями*/
    std::map<std::string, Part*> name_map;
};

#endif
