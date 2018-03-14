#ifndef SAFEARRAY_SAFEARRAY_H_
#define SAFEARRAY_SAFEARRAY_H_

#include <stdexcept>
#include <iostream>

namespace xi {

    template<typename T>
    class SafeArray;

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const SafeArray<T>& subj);

    template<typename T>
    void swap(SafeArray<T>& first, SafeArray<T>& second);

/** \brief Класс "защищенный массив"
 *
 *  Определяет класс-массив с доступом к элементам с контролем по индексу.
 */
    template<typename T>
    class SafeArray {

    public:

        /** \brief Конструктор по умолчанию.
         *
         *  Не распределяет память, использует nullptr в качестве адреса массива.
         */
        SafeArray() : _storage(nullptr), _capacity(0)
        {
        }


        /** \brief Конструктор инициализации размером (число объектов) массива.
         *
         *  Распределяет память соответствующего размера, устанавливает значение емкости массива.
         * \param[in] cap Размер (емкость) массива.
         */
        SafeArray(size_t cap);


        /** \brief Конструктор копирования массива.
        *
        *  Создает объект SafeArray, копируя данные из объекта objectToCopy
        * \param[in] objectToCopy копируемый массив.
        */
        SafeArray(const SafeArray<T>& objectToCopy);


        /** \brief Метод копирования массива.
        *
        *  Копирует данные из объекта objectToCopy в наш массив
        * \param[in] objectToCopy копируемый массив.
        */
        SafeArray<T>& operator=(const SafeArray<T>& objectToCopy);

        /** \brief Деструктор.
         *
         *  Освобождает занимаемую массивом память.
         */
        ~SafeArray(); // destructor

        /** \brief Оператор индексирования.
         *
         *  Выполняет «защищенное» обращение к индивидуальным элементам массива.
         * Элемент возвращается по ссылке, и, таким образом, может находиться как в позиции \a rhv, так и в
         * позиции \a lhv.
         * \param[in] k — индекс элемента. Если указанный индекс находится вне диапазона распределенной памяти,
         * генерируется исключительная ситуация \c std::out_of_range.
         * \return Возвращает ссылку на \a k -тый элемент массива.
         */
        T& operator[](size_t k);


        /** \brief Константная перегруженная версия метода Safearray::operator[].
         *
         *  Возвращает константную ссылку на элемент, которая может находиться только в позиции \a rhv.
         */
        const T& operator[](size_t k) const;


        /// Возвращает "сырой" константный указатель на массив. Используется только для специальных целей
        /// в позиции \a rhv.
        const T* getRawPtr() const { return _storage; }

        /// Возвращает актуальный размер массива.
        size_t getCapacity() const;


        /** \brief Дружественная оператор-функция вывода объекта в поток вывода.
        *
        *  Конструкция расширяет семантику объекта типа SafeArray, позволяя его использовать
        *  в потоковых операциях, например со стандартным потоком вывода: \verbatim
        SafeArray array...
        cout << array;   \endverbatim
        *  \param[in,out] str Поток вывода.
        *  \param[in] subj Константный объект-предмет, для вывода его текстового представления.
        *  \return Функция возвращает тот же поток \c str, чтобы ее можно было использовать ...
        */
        friend std::ostream& operator<<<T>(std::ostream& out, const SafeArray<T>& subj);


        /** \brief Дружественная функция обмена данными между объектами SafeArray.
        *
        *   Записывает все данные из второго объекта в первый, из первого во второй
        *  \param[in] first Первый объект.
        *  \param[in] second Второй объект.
        */
        friend void swap<T>(SafeArray<T>& first, SafeArray<T>& second);


    protected:
        /// Вспомогательный метод, проверяющий, что заданный индекс \a index не выходит за границу
        /// распределенной под массив памяти. Если индекс вне диапазона, генерирует
        /// исключительную ситуацию \c std::out_of_range.
        void checkBounds(size_t index) const;


    private:
        /// Массив, представленный указателем на параметрический тип.
        T* _storage;

        /// Реальная память, распределенная под массив (в количестве элементов размера sizeof(T)).
        size_t _capacity;


    }; // class SafeArray<T>



} // namespace xi






// Here we simply add definitions from a file safearray.hpp. It's the same as we 
// simply put those defitions as a as a continuation of this very file.
// Not, that neither safearray.h nor safearray.hpp are compiled on their own.
#include "safearray.hpp"


#endif // SAFEARRAY_SAFEARRAY_H_
