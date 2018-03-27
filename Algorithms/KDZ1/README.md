/* КДЗ по дисциплине Флгоритмы и структуры данных 2017-2018 уч. год
 *
 * Выполнил: Чуев Иван Сергеевич, группа БПИ163, 25.03.2018
 *
 * Среда разработки: CLion.
 *
 * Состав проекта:
 * src - папка с исходников
 *     LZ77 - папка с классом LZ77Encoder
 *         LZ77Encoder.h - класс LZ77Encoder
 *         LZ77Encoder.cpp
 *     TableEncoders - папка с классами кодировки с помощью таблицы
 *         Fano - папка с классом FanoEncoder
 *             FanoEncoder.h - класс FanoEncoder
 *             FanoEncoder.cpp
 *         Huffman - папка с классом HuffmanEncoder
 *             HuffmanEncoder.h - класс HuffmanEncoder
 *             HuffmanEncoder.cpp
 *         Helpers - папка вспомогательных методов для TableEncoder классов
 *         TableEncoder.h - абстрактный класс для TableEncoder-ов
 *         TableEncoder.cpp - вспомогательный файл для TableEncoder
 *     FileEncoder.h - абстрактный класс для всех кодировщиков
 *     timing.cpp - текст программы, подсчитывающей и записывающей среднее кодирование/декодирование
 *     entropy.cpp - текст программы, подсчитывающей энтропию
 *     nsimb.cpp - текст программы, подсчитывающий частоту встречаемых символов в файле
 * tests - папка тестов
 *     googletest - папка библиотеки google тестов
 *     resources - папка для тестов
 *     HuffmanTests.cpp - тесты для HuffmanEncoder
 *     FanoTests.cpp - тесты для FanoEncoder
 *     LZ77Tests.cpp - тесты для LZ77Encoder
 *
 * Сделано:
 *     Huffman
 *     Fano
 *     LZ77
 */