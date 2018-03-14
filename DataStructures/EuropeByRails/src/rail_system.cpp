/*
 * \file
 * \brief реализация методов класса RailSystem
 * \author Чуев Иван БПИ163
 * \date 05.11.2017
 *       Представляет собой реализацию методов класса системы маршрутов.
 *       Добавлена реализация 'большой тройки'
 *       Также добавлен метод swap. Для более простой реализации оператора =
 */


//#pragma warning (disable:4786)
//#pragma warning (disable:4503)

#include "rail_system.h"
#include "priority_queue.h"
#include <algorithm>    //swap


// Здесь объявляем псевдоним для специфицированной собственной реализации очереди с приоритетами,
// шаблон которой объявлен в файле "priority_queue.h"
typedef PriorityQueue<City*, Cheapest> CitiesPriorityQueue;

//Итератор по городам
typedef std::map<std::string, City*>::const_iterator city_it;

//Итератор по дорогам из городов
typedef std::map<std::string, std::list<Service*>>::const_iterator services_it;

//Итератор по дорогам из города
typedef std::list<Service*>::const_iterator service_it;



// в cpp так можно
//using namespace std;

RailSystem::RailSystem(const std::string& filename)
{
    //Считываем данные из файла
    load_services(filename);
}

RailSystem::~RailSystem(void)
{
    //Проходим по коллекции City и удаляем элементы
    for(city_it it = cities.begin(); it != cities.end(); it++)
        delete it->second;

    //Проходим по коллекции и удаляем элементы Service
    for(services_it ser_it = outgoing_services.begin(); ser_it != outgoing_services.end(); ser_it++)
        for(service_it ser = ser_it->second.begin(); ser != ser_it->second.end(); ser++)
            delete *ser;
}

RailSystem::RailSystem(const RailSystem& obj)
{
    //Копируем коллекцию городов
    for(city_it it = obj.cities.begin(); it != obj.cities.end(); it++) {
        City* objCity = it->second;
        City* city = new City(it->second->name);

        city->from_city = objCity->from_city;
        city->total_distance = objCity->total_distance;
        city->total_fee = objCity->total_fee;
        city->visited = objCity->visited;

        cities[city->name] = city;
    }

    //Копируем коллекцию дорог из городов
    for(services_it ser_it = obj.outgoing_services.begin(); ser_it != obj.outgoing_services.end(); ser_it++) {
        for(service_it ser = ser_it->second.begin(); ser != ser_it->second.end(); ser++) {
            Service* s = *ser;
            outgoing_services[ser_it->first].push_back(new Service(s->destination, s->fee, s->distance));
        }
    }
}

RailSystem& RailSystem::operator=(const RailSystem& obj)
{
    RailSystem copy = RailSystem(obj);
    swap(copy, *this);                         //Меняем местами obj и this

    return *this;                              //Удаляется объект copy и возвращается ссылка на текущий объект
}

void swap(RailSystem& first, RailSystem& second)
{
    std::swap(first.cities, second.cities);
    std::swap(first.outgoing_services, second.outgoing_services);
}


void RailSystem::reset(void)
{
    //Проходимся по коллекции City и задаем ее элементам значения по умолчанию
    for(city_it it = cities.begin(); it != cities.end(); it++) {
        it->second->visited = false;
        it->second->total_fee = 0;
        it->second->total_distance = 0;
        it->second->from_city = "";
    }
}

void RailSystem::load_services(const std::string& filename)
{
    std::ifstream inf(filename.c_str());
    std::string from, to;
    int fee, distance;

    //Считываем данные из файла
    while(inf.good()) {
        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if(inf.good()) {
            //Добавляем город from в список городов
            if(cities.find(from) == cities.end())           // Защита от утечки памяти
                cities[from] = new City(from);

            //Добавляем город to в список городов
            if(cities.find(to) == cities.end())           // Защита от утечки памяти
                cities[to] = new City(to);

            //Добавляем путь из from  до to
            outgoing_services[from].push_back(new Service(to, fee, distance));
        }
    }

    //Закрываем файл
    inf.close();
}


void RailSystem::output_cheapest_route(const std::string& from, const std::string& to, std::ostream& out)
{
    reset();
    std::pair<int, int> totals = calc_route(from, to);

    if(totals.first == INT_MAX) {
        out << "There is no route from " << from << " to " << to << "\n";
        return;
    }

    out << "The cheapest route from " << from << " to " << to << "\n";
    out << "costs " << totals.first << " euros and spans " << totals.second << " kilometers\n";
    out << recover_route(to) << "\n\n";
}

bool RailSystem::is_valid_city(const std::string& name)
{
    return cities.count(name) == 1;
}

std::pair<int, int> RailSystem::calc_route(const std::string& from, const std::string& to)
{
    //Очередь элементов, являющихся кандитатами на построение маршрута
    CitiesPriorityQueue candidates;

    //Кладем нычальный элемент в очередь
    candidates.push(cities[from]);

    //Пока список всх кандидатов на построение маршрута не пуст, пересчитываем маршруты до городов
    while(!candidates.isEmpty()) {
        //Достаем город с наибольшим приоритетом
        City* cityFrom = candidates.pop();
        cityFrom->visited = true;           //Помечаем посещенным, так как, построенная дорога до этого города, уже минимальна
        if(cityFrom->name ==
           to)            //Заканчиваем цикл обноаления длин, если данный город является точкой назначения
            break;

        //проходимся по всем дорогам из города
        std::list<Service*> edges = outgoing_services[cityFrom->name];
        for(std::list<Service*>::iterator edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
            Service* edge = *edges_it;
            City* cityTo = cities[edge->destination];

            //Если найден лучший маршрут до этого города или маршрута еще нет, то маршрут обновляется
            if(!cityTo->visited && (cityTo->total_fee == 0 || cityTo->total_fee > cityFrom->total_fee + edge->fee)) {
                if(!cityTo->total_fee == 0)     //Если маршрут лежит в очереди предпологаемых городов,
                    candidates.remove(cityTo);  //то город удаляется из списка, так как маршрут до него будет обновлен

                cityTo->total_fee = cityFrom->total_fee + edge->fee;
                cityTo->total_distance = cityFrom->total_distance + edge->distance;
                cityTo->from_city = cityFrom->name;

                candidates.push(cityTo);        //Город добавляется в очередь предпологаемых маршрутов
            }
        }
    }

    //Если удалось построить маршрут до города to, то возвращается информация о маршруте
    if(cities[to]->visited)
        return std::pair<int, int>(cities[to]->total_fee, cities[to]->total_distance);

    //Если не удалось построить маршрут до города to, то "пустой" маршрут
    return std::pair<int, int>(INT_MAX, INT_MAX);
}

std::string RailSystem::recover_route(const std::string& city)
{
    std::string r_route = city, currentCity = cities[city]->from_city;

    //Проходим по маршруту в обратном направлении, и добавляем города в r_route
    while(currentCity != "") {
        r_route = currentCity + " to " + r_route;
        currentCity = cities[currentCity]->from_city;
    }

    return r_route;
}


Route RailSystem::getCheapestRoute(const std::string& from, const std::string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    std::pair<int, int> p = calc_route(from, to);

    return Route(from, to, p.first, p.second);
}
