#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
using namespace std;

Image::Image() {
    header = Header();
}

Image::Header::Header() {
    height = 0;
    width = 0;
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 0;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    bitsPerPixel = 0;
    imageDescriptor = 0;
}

//ACCOUNTING FOR COLOR VALUES
Image::Pixel &Image::Pixel::operator+(Image::Pixel pixel) {
    int tempInt = pixelR;
    tempInt -= pixel.pixelR;
    //if greater than 255, se to 0
    if(tempInt >255)
        this->pixelR = 0;
    else
        this->pixelR = tempInt;
    tempInt -= pixel.pixelG;

    if(tempInt >255)
        this->pixelG = 0;
    else
        this->pixelG = tempInt;
    tempInt -= pixel.pixelB;

    if(tempInt >255)
        this->pixelB = 0;
    else
        this->pixelB = tempInt;
    return *this;
}

Image::Pixel &Image::Pixel::operator-(Image::Pixel pixel) {
    int tempInt = pixelR;
    tempInt -= pixel.pixelR;

    if (tempInt < 0)
        this->pixelR = 0;
    else
        this->pixelR = tempInt;
    tempInt = pixelG;
    tempInt -= pixel.pixelG;

    if (tempInt < 0)
        this->pixelG = 0;
    else
        this->pixelG = tempInt;
    tempInt = pixelB;
    tempInt -= pixel.pixelB;

    if (tempInt < 0)
        this->pixelB = 0;
    else
        this->pixelB = tempInt;

    return *this;
}
Image::Pixel &Image::Pixel::operator*(Image::Pixel pixel) {
    float tempFloat;
    tempFloat = (((this->pixelR / 255.0f) * (pixel.pixelR / 255.0f)) * 255.0f) + 0.5f;
    this->pixelR = (unsigned char) tempFloat;

    tempFloat = (((this->pixelG / 255.0f) * (pixel.pixelG / 255.0f)) * 255.0f) + 0.5f;
    this->pixelG = (unsigned char) tempFloat;

    tempFloat = (((this->pixelB / 255.0f) * (pixel.pixelB / 255.0f)) * 255.0f) + 0.5f;
    this->pixelB = (unsigned char) tempFloat;

    return *this;
}

bool Image::Pixel::operator==(Image::Pixel pixel) {
    return (pixel.pixelR == this->pixelR) && (pixel.pixelB == this->pixelB) && (pixel.pixelG == this->pixelG);
}

Image::Pixel &Image::Pixel::operator=(Image::Pixel pixel) {
    this->pixelR = pixel.pixelR;
    this->pixelG = pixel.pixelG;
    this->pixelB = pixel.pixelB;
    return *this;
}