#include "xipoint.h"

#include <algorithm>        // min

namespace xi {
    Point::Point(int x, int y)
    {
        _x = x;
        _y = y;
    }

    void Point::shift(int shf)
    {
        _x += shf;
        _y += shf;
    }

    void Point::shift(int xSh, int ySh)
    {
        _x += xSh;
        _y += ySh;
    }

    void Point::shift(const Point &pt)
    {
        _x += pt.getX();
        _y += pt.getY();
    }

    int Point::getX() const { return _x; }

    int Point::getY() const { return _y; }

    void Point::setX(int x) { _x = x; }

    void Point::setY(int y) { _y = y; }


    PointArray::PointArray()
    {
        _arr = nullptr;
        _size = 0;
    }

    PointArray::PointArray(const Point points[], Uint n)
    {
        _size = n;
        _arr = new Point[n];
        for(Uint i = 0; i < n; i++)
            _arr[i] = Point(points[i].getX(), points[i].getY());
    }

    PointArray::PointArray(const PointArray &pv)
    {
        _size = pv.getSize();
        _arr = new Point[_size];
        for(Uint i = 0; i < _size; i++)
            _arr[i] = Point(pv.get(i)->getX(), pv.get(i)->getY());
    }

    PointArray::~PointArray()
    {
        delete[] _arr;
    }

    void PointArray::append(const Point &pt)
    {
        resize(_size + 1);
        _arr[_size - 1] = Point(pt.getX(), pt.getY());
    }

    void PointArray::insert(const Point &pt, Uint pos)
    {
        if(pos >= _size) {
            append(pt);
            return;
        }
        if(pos < 0)
            return;

        resize(_size + 1);
        for(Uint i = _size - 1; i > pos; i--)
            _arr[i] = _arr[i - 1];
        _arr[pos] = Point(pt.getX(), pt.getY());
    }

    void PointArray::remove(Uint pos)
    {
        if(pos >= _size || pos < 0)
            return;
        if(_size == 1 && pos == 0)
            clear();

        for(Uint i = pos; i < _size - 1; i++)
            _arr[i] = _arr[i + 1];
        resize(_size - 1);
    }

    void PointArray::resize(Uint n)
    {
        if(_size == 0 && n > 0) {
            _arr = new Point[n];
            _size = n;
            return;
        }

        Point *arrCopy = _arr;
        _arr = new Point[n];
        for(Uint i = 0; i < std::min(n, _size); i++)
            _arr[i] = arrCopy[i];
        _size = n;
        delete[] arrCopy;
    }

    void PointArray::clear()
    {
        if(_arr != nullptr) {
            delete[] _arr;
            _arr = nullptr;
        }
        _size = 0;
    }

    const PointArray::Uint PointArray::getSize() const
    {
        return _size;
    }

    Point *PointArray::get(Uint pos)
    {
        if(_size == 0 || pos < 0 || pos >= _size)
            return nullptr;
        return &_arr[pos];
    }

    const Point *PointArray::get(Uint pos) const
    {
        if(_size == 0 || pos < 0 || pos >= _size)
            return nullptr;
        return &_arr[pos];
    }


} // namespace xi {