#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Image {
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
        Header();
    };
    struct Pixel {
        unsigned char pixelR, pixelG, pixelB;
        //operators
        Pixel &operator * (Pixel pixel);
        Pixel &operator + (Pixel pixel);
        Pixel &operator - (Pixel pixel);
        bool operator == (Pixel pixel);
        Pixel &operator = (Pixel pixel);
    };
    vector<Pixel> pixelVector;
    Header header;
    Image();

};
