/**
 *  \file
 *  \brief реализация методов классов Part и NameContainer
 *  \author Чуев Иван БПИ163
 *  \date 30.11.2017
 *              Написана реализация класса Part, добавлен метод на *.
 *              К классу Part написаны тесты в файле: tests\Part_Student_Tests.cpp
 *
 *              Написана реализация класса NameContainer, добавлена большая тройка
 *
 */


#include <iostream>     //cout
#include "parts.h"
#include "algorithm"    //swap

void Part::describe()
{
    //Выводим информацию о самом объекте
    std::cout << "Part " << name << " subparts are:" << std::endl;

    //Выводим информациЮ об чатях объекта
    std::map<Part const*, int>::const_iterator it = subparts.begin();
    if(it == subparts.end())
        std::cout << "\tIt has no subparts." << std::endl;
    for(; it != subparts.end(); it++)
        std::cout << "\t" << it->second << " " << it->first->name << std::endl;
}

int Part::count_howmany(Part const* p) const
{
    //Если объект соответствует  переданному, то возвращается еденица
    if(name == p->name)
        return 1;

    //Подсчитывается колличество подобъектов
    int sum = 0;
    std::map<Part const*, int>::const_iterator it = subparts.begin();
    for(; it != subparts.end(); it++)
        sum += it->second * it->first->count_howmany(p);
    return sum;
}

void Part::addSubPart(Part* p, int q)
{
    //Объект добавляется в подобъекты
    subparts[p] = q;
    //Запоминается родитель
    p->parent = this;
}

int Part::count_howmanyUp(Part const* p) const
{
    //Проходясь вверх до конца цепочки и находим общее колличество объектов p
    int sum = 1;
    for(; p != this && p != nullptr; p = p->parent)
        sum *= p->parent->subparts[p];
    return p == nullptr ? 0 : sum;
}

Part* NameContainer::lookup(std::string const& name)
{
    //наодим элемент с именем name
    std::map<std::string, Part*>::const_iterator it = name_map.find(name);
    //если элемент не найден, то создаем его и добавляем в name_map
    Part* p = it == name_map.end() ? new Part(name) : it->second;
    if(it == name_map.end())
        name_map[name] = p;
    //возвращаем ссылку на элемент
    return p;
}

void NameContainer::add_part(std::string const& x, int q, std::string const& y)
{
    //Находим элемент с именем x и добавляем к нему элемент с именем y, указывая размер q
    lookup(x)->addSubPart(lookup(y), q);
}

NameContainer::~NameContainer()
{
    //Удаляем все объекты Part из name_map, хранящиеся в куче
    std::map<std::string, Part*>::iterator it = name_map.begin();
    for(; it != name_map.end(); it++)
        delete it->second;
}

NameContainer::NameContainer(const NameContainer& obj)
{
    //Проходимся по всем Part-ам в нашем объекте
    std::map<std::string, Part*>::const_iterator obj_it = obj.name_map.begin();
    for(; obj_it != obj.name_map.end(); obj_it++) {
        //Проходимся по всем SubPart-ам и добавляем свзяь Part->SubPart через функцию add_part
        std::map<Part const*, int> subparts = obj_it->second->subparts;
        std::map<Part const*, int>::const_iterator subpart_it = subparts.begin();
        for(; subpart_it != subparts.end(); subpart_it++)
            add_part(obj_it->first, subpart_it->second, subpart_it->first->name);
    }
}

NameContainer& NameContainer::operator=(const NameContainer& obj)
{
    NameContainer temp(obj);
    swap(temp, *this);

    return *this;
}

void swap(NameContainer& first, NameContainer& second)
{
    std::swap(first.name_map, second.name_map);
}
