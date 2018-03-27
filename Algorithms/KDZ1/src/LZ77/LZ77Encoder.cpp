//
// Created by Ivan on 3/23/2018.
//

#include "LZ77Encoder.h"

struct Buffer
{
    Buffer(unsigned short int size)
    {
        this->size = size;
        this->pos = size - 1;
        this->buffer = new char[size];
    }

    char& get(unsigned short int p)
    {
        if(p > size || p < 0)
            throw std::invalid_argument((int)p + " ");
        return buffer[(pos - p + size) % size];
    }

    void put(char c)
    {
        pos = (unsigned short int)(pos + 1) % size;
        buffer[pos] = c;
    }

    ~Buffer()
    {
        delete[] buffer;
    }

    unsigned short int pos;
    unsigned short int size;
    char* buffer;
};

void LZ77Encoder::encode(std::istream& encoded, std::ostream& decoded)
{
    Buffer buffer(historyBufferSize + previewBufferSize);
    unsigned short int pbs = 0, hbs = 0;
    char c;
    for(; pbs < previewBufferSize && encoded.get(c); ++pbs)
        buffer.put(c);

    while(pbs > 0)
    {
        unsigned short int len = 0, pos = 0;
        for(unsigned short int p = 0; p < hbs; ++p)
        {
            unsigned short int k = 0;
            for(;  k < pbs - 1 && buffer.get(hbs + pbs - p - k - 1) == buffer.get(pbs - k - 1); ++k);
            if(k > len)
            {
                len = k;
                pos = p;
            }
        }

        decoded << static_cast<char>((unsigned char)(pos / 256))
                << static_cast<char>((unsigned char)(pos % 256))
                << static_cast<char>((unsigned char)(len / 256))
                << static_cast<char>((unsigned char)(len % 256))
                << (char)buffer.get(pbs - len - 1);

        int i = -1;
        for(; i < len; ++i) {
            if(!encoded.get(c))
                break;
            buffer.put(c);
        }

        pbs += i - len;
        if(hbs < historyBufferSize)
            hbs = hbs + len + 1 > historyBufferSize ? historyBufferSize : hbs + len + 1;
    }
}

void LZ77Encoder::decode(std::istream& decoded, std::ostream& encoded)
{
    Buffer buffer(historyBufferSize);
    char latter;
    unsigned short int pos, len, hbs = 0;
    while(true)
    {
        if(!decoded.get(latter))
            break;
        pos = static_cast<unsigned char>(latter) * 256;
        if(!decoded.get(latter))
            break;
        pos += static_cast<unsigned char>(latter);

        if(!decoded.get(latter))
            break;
        len = static_cast<unsigned char>(latter) * 256;
        if(!decoded.get(latter))
            break;
        len += static_cast<unsigned char>(latter);

        if(!decoded.get(latter))
            break;

        char c;
        for(unsigned short int p = 0; p < len; ++p) {
            c = buffer.get(hbs - pos - 1);
            buffer.put(c);
            encoded << c;
        }
        buffer.put(latter);
        encoded << latter;

        if(hbs < historyBufferSize)
            hbs = hbs + len + 1 > historyBufferSize ? historyBufferSize : hbs + len + 1;
    }
}

unsigned short int LZ77Encoder::getHistoryBufferSize() const
{
    return historyBufferSize;
}

unsigned short int LZ77Encoder::getPreviewBufferSize() const
{
    return previewBufferSize;
}