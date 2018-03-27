#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>
#include "FileEncoder.h"
#include "TableEncoders/Huffman/HuffmanEncoder.h"
#include "TableEncoders/Fano/FanoEncoder.h"
#include "LZ77/LZ77Encoder.h"

long long encodeAndMeasureHuffman(const std::string& path, const std::string& encodedPath)
{
    HuffmanEncoder encoder;
    auto start = std::chrono::high_resolution_clock::now();
    encoder.encodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long decodeAndMeasureHuffman(const std::string& path, const std::string& encodedPath)
{
    HuffmanEncoder encoder;
    auto start = std::chrono::high_resolution_clock::now();
    encoder.decodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long encodeAndMeasureFano(const std::string& path, const std::string& encodedPath)
{
    FanoEncoder encoder;
    auto start = std::chrono::high_resolution_clock::now();
    encoder.encodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long decodeAndMeasureFano(const std::string& path, const std::string& encodedPath)
{
    FanoEncoder encoder;
    auto start = std::chrono::high_resolution_clock::now();
    encoder.decodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long encodeAndMeasureLZ775(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(4 * 1024, 5 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.encodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long decodeAndMeasureLZ775(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(4 * 1024, 5 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.decodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long encodeAndMeasureLZ7710(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(8 * 1024, 10 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.encodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long decodeAndMeasureLZ7710(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(8 * 1024, 10 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.decodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long encodeAndMeasureLZ7720(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(16 * 1024, 20 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.encodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

long long decodeAndMeasureLZ7720(const std::string& path, const std::string& encodedPath)
{
    LZ77Encoder encoder(16 * 1024, 20 * 1024);
    auto start = std::chrono::high_resolution_clock::now();
    encoder.decodeFile(path, encodedPath);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

double calculateCompression(const std::string& filePath, const std::string& encodedFilePath)
{
    std::ifstream file(filePath, std::ifstream::ate | std::ifstream::binary);
    std::ifstream encodedFile(filePath, std::ifstream::ate | std::ifstream::binary);
    double res = encodedFile.tellg() / (double)file.tellg();
    file.close();
    encodedFile.close();
    return res;
}

int main()
{
    const int n = 1;
    const std::string filesPath = "../../resources/files/";
    const std::string encodePath = "../../resources/encode/";
    const std::string decodePath = "../../resources/decode/";
    const std::string files[] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                                  "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
                                  "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36" };

    std::ofstream huffman("../../resources/HuffmanRes.csv");
    std::ofstream fano("../../resources/FanoRes.csv");
    std::ofstream lz775("../../resources/LZ775Res.csv");
    std::ofstream lz7710("../../resources/LZ7710Res.csv");
    std::ofstream lz7720("../../resources/LZ7720Res.csv");
    for(auto& file : files)
    {
        long long encodeTime = 0, decodeTime = 0;
        for(int k = 0; k < n; ++k) {
            encodeTime += encodeAndMeasureHuffman(filesPath + file, encodePath + file + ".huff");
            decodeTime += decodeAndMeasureHuffman(encodePath + file + ".huff", decodePath + file + ".unhuff");
        }
        huffman << file << "," << encodeTime / n << "," << decodeTime / n << ","
                << calculateCompression(filesPath + file, encodePath + file + ".huff") << std::endl;
        std::cout << file + ".huff" << std::endl;

        encodeTime = 0, decodeTime = 0;
        for(int k = 0; k < n; ++k) {
            encodeTime += encodeAndMeasureFano(filesPath + file, encodePath + file + ".fano");
            decodeTime += decodeAndMeasureFano(encodePath + file + ".fano", decodePath + file + ".unfano");
        }
        fano << file << "," << encodeTime / n << "," << decodeTime / n << ","
             << calculateCompression(filesPath + file, encodePath + file + ".fano") << std::endl;
        std::cout << file + ".fano" << std::endl;

        encodeTime = 0, decodeTime = 0;
        for(int k = 0; k < n; ++k) {
            encodeTime += encodeAndMeasureLZ775(filesPath + file, encodePath + file + ".lz775");
            decodeTime += decodeAndMeasureLZ775(encodePath + file + ".lz775", decodePath + file + ".unlz775");
        }
        lz775 << file << "," << encodeTime / n << "," << decodeTime / n << ","
              << calculateCompression(filesPath + file, encodePath + file + ".lz775") << std::endl;
        std::cout << file + ".lz775" << std::endl;

        encodeTime = 0, decodeTime = 0;
        for(int k = 0; k < n; ++k) {
            encodeTime += encodeAndMeasureLZ7710(filesPath + file, encodePath + file + ".lz7710");
            decodeTime += decodeAndMeasureLZ7710(encodePath + file + ".lz7710", decodePath + file + ".unlz7710");
        }
        lz7710 << file << "," << encodeTime / n << "," << decodeTime / n << ","
               << calculateCompression(filesPath + file, encodePath + file + ".lz7710") << std::endl;
        std::cout << file + ".lz7710" << std::endl;

        encodeTime = 0, decodeTime = 0;
        for(int k = 0; k < n; ++k) {
            encodeTime += encodeAndMeasureLZ7720(filesPath + file, encodePath + file + ".lz7720");
            decodeTime += decodeAndMeasureLZ7720(encodePath + file + ".lz7720", decodePath + file + ".unlz7720");
        }
        lz7720 << file << "," << encodeTime / n << "," << decodeTime / n << ","
               << calculateCompression(filesPath + file, encodePath + file + ".lz7720") << std::endl;
        std::cout << file + ".lz7720" << std::endl;
    }

    huffman.close();
    fano.close();
    lz775.close();
    lz7710.close();
    lz7720.close();
    return 0;
}