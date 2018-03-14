/*
 * \file
 * \brief реализация класса RailSystem
 * \author Чуев Иван БПИ163
 * \date 05.11.2017
 *       Класс представляет собой реализацию системы маршрутов.
 *       В класс добавлена реализация 'большой тройки'
 *       Также добавлен метод swap. Для более простой реализации оператора =
 *       Также к этому файлу прилогаются тесты в папке 'tests' файл rail_system_student_tests.cpp
 */

#ifndef _RAILSYSTEM_H_
#define _RAILSYSTEM_H_

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <queue>
#include <vector>
#include <assert.h>
#include <climits>


#include "service.h"
#include "city.h"

// плохая практика, поэтому закомментарировано (по сравнению с исходной версией)
// NB: возможно по коду модуля потребуется добавить префикс std:: самостоятельно
// к объектам из пространства имен стандартной библиотеки
// using namespace std;     

// компаратор, сравнивающий два "города" по критерию "стоимость доставки"
class Cheapest {
public:
    Cheapest() {}

    bool operator()(City* city1, City* city2)
    {
        return city1->total_fee < city2->total_fee;
    }

    bool operator()(const City& city1, const City& city2)
    {
        return city1.total_fee < city2.total_fee;
    }
};

// For test only 
struct Route {
    // в структурах частая практика поля не инкапсулировать
    std::string from;
    std::string to;
    int fee;
    int distance;

    Route(const std::string& f, const std::string& t, int fe, int d) : from(f), to(t), fee(fe), distance(d) {}

    bool operator==(const Route& rhs) const
    {
        if(rhs.from == this->from && rhs.to == this->to && rhs.fee == this->fee && rhs.distance == this->distance)
            return true;

        return false;
    }
};


class RailSystem {
public:
    RailSystem(const std::string& filename);

    RailSystem() {}

    ~RailSystem();

    RailSystem(const RailSystem& obj);

    RailSystem& operator=(const RailSystem& obj);

    void output_cheapest_route(const std::string& from, const std::string& to, std::ostream& out);

    bool is_valid_city(const std::string& name);

    // For test only   
    Route getCheapestRoute(const std::string& from, const std::string& to);

    friend void swap(RailSystem& first, RailSystem& second);

protected:
    std::map<std::string, std::list<Service*> > outgoing_services;
    std::map<std::string, City*> cities;

    void load_services(const std::string& filename);

    void reset();

    std::string recover_route(const std::string& city);

    std::pair<int, int> calc_route(const std::string& from, const std::string& to);
};

#endif
