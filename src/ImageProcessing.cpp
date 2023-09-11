#include <iostream>
#include <vector>
#include <fstream>
#include "Image.h"
#include "ImageProcessing.h"

using namespace std;
//ask about reinterpret_cast vs cout<< (int)someVariable
//found reinterpret cast method and do not know the benefits of drawbacks vs (type)

Image ImageProcessing::readImage(string fileName) {
    Image image;
    //is ios_base::binary necesary?

    ifstream file(fileName, ios_base::binary);
    file.read(&image.header.idLength, sizeof(image.header.idLength));
    file.read(&image.header.colorMapType, sizeof(image.header.colorMapType));
    file.read(&image.header.dataTypeCode, sizeof(image.header.dataTypeCode));
    //why does * have to be there ?
    file.read(((char*)&image.header.colorMapOrigin), sizeof(image.header.colorMapOrigin));
    file.read(((char*)&image.header.colorMapLength), sizeof(image.header.colorMapLength));
    file.read(&image.header.colorMapDepth, sizeof(image.header.colorMapDepth));
    file.read(((char*)&image.header.xOrigin), sizeof(image.header.xOrigin));
    file.read(((char*)&image.header.yOrigin), sizeof(image.header.yOrigin));
    file.read(((char*)&image.header.width), sizeof(image.header.width));
    file.read(((char*)&image.header.height), sizeof(image.header.height));
    file.read(&image.header.bitsPerPixel, sizeof(image.header.bitsPerPixel));
    file.read(&image.header.imageDescriptor, sizeof(image.header.imageDescriptor));

    //make vector of pixels
    for (unsigned int i = 0; i < (image.header.height * image.header.width); i++) {
        Image::Pixel pixel;
        file.read(((char*)&pixel.pixelB), sizeof(pixel.pixelB));
        file.read(((char*)&pixel.pixelG), sizeof(pixel.pixelG));
        file.read(((char*)&pixel.pixelR), sizeof(pixel.pixelR));
        image.pixelVector.push_back(pixel);
    }
    return image;
}
//same as read but instead using .write
void ImageProcessing::writeImage(string fileName, Image image) {
    ofstream file(fileName, ios_base::out | ios_base::binary);
    file.write(&image.header.idLength, sizeof(image.header.idLength));
    file.write(&image.header.colorMapType,  sizeof(image.header.colorMapType));
    file.write(&image.header.dataTypeCode,  sizeof(image.header.dataTypeCode));
    file.write(((char*)&image.header.colorMapOrigin),  sizeof(image.header.colorMapOrigin));
    file.write(((char*)&image.header.colorMapLength),  sizeof(image.header.colorMapLength));
    file.write(&image.header.colorMapDepth,  sizeof(image.header.colorMapDepth));
    file.write(((char*)&image.header.xOrigin),  sizeof(image.header.xOrigin));
    file.write(((char*)&image.header.yOrigin),  sizeof(image.header.yOrigin));
    file.write(((char*)&image.header.width),  sizeof(image.header.width));
    file.write(((char*)&image.header.height),  sizeof(image.header.height));
    file.write(&image.header.bitsPerPixel,  sizeof(image.header.bitsPerPixel));
    file.write(&image.header.imageDescriptor,  sizeof(image.header.imageDescriptor));

    //print from vector of pixels
    for (unsigned int i = 0; i < (image.header.height * image.header.width); i++) {
        Image::Pixel pixel = image.pixelVector[i];
        file.write(((char*)&pixel.pixelB), sizeof(pixel.pixelB));
        file.write(((char*)&pixel.pixelG), sizeof(pixel.pixelG));
        file.write(((char*)&pixel.pixelR), sizeof(pixel.pixelR));

    }
}
//compare
bool ImageProcessing::compare(Image image1, Image image2) {
    for (unsigned int i = 0; i < (image1.header.width * image1.header.height); i++) {
        if (!(image1.pixelVector[i] == image2.pixelVector[i])) {
            return false;
        }
    }
    return true;
}
//multiply
Image ImageProcessing::multiply(Image image1, Image image2 ) {
    Image result;
    result.header = image1.header;
    for(unsigned int i = 0; i <(image1.header.height * image1.header.width); i++ ){
        result.pixelVector.push_back(image1.pixelVector[i] * image2.pixelVector[i]);
    }
    return result;
}

//subtract
Image ImageProcessing::subtract(Image image1, Image image2) {
    Image result;
    result.header = image1.header;
    for(unsigned int i = 0; i <(image1.header.height * image1.header.width); i++ ){
        result.pixelVector.push_back(image1.pixelVector[i] - image2.pixelVector[i]);
    }
    return result;
}
//screen
Image ImageProcessing::screen(Image image1, Image image2) {
    Image result;
    result.header = image1.header;
    Image::Pixel temp1;
    Image::Pixel temp2;
    Image::Pixel temp3;

    for(unsigned int i = 0; i <(image1.header.height * image1.header.width); i++ ){
        temp1.pixelR = temp2.pixelR = temp3.pixelR = 255;
        temp1.pixelG = temp2.pixelG = temp3.pixelG = 255;
        temp1.pixelB = temp2.pixelB = temp3.pixelB = 255;
//help from OH, understanding screen function
        Image::Pixel finalA = temp2 - image1.pixelVector[i];
        Image::Pixel finalB = temp3 - image2.pixelVector[i];
        Image::Pixel finalC = finalA * finalB;
        Image::Pixel final = temp1 - finalC;

        result.pixelVector.push_back(final);
    }
    return result;
}
//careful of rounding, use 255.0f
Image ImageProcessing::overlay(Image image1, Image image2) {
    Image result;
    result.header = image1.header;

    for(unsigned int i = 0; i <(image1.header.height * image1.header.width); i++ ){
        float red = 0;
        float overlayRed = image1.pixelVector[i].pixelR / 255.0f;
        float overlayRed2 = image2.pixelVector[i].pixelR / 255.0f;
//(each is the same foor every color)
        if(overlayRed2 <= 0.5){
            red = 2.0f * overlayRed * overlayRed2;
        }
        else {
            red = 1.0f - 2.0f * (1.0f - overlayRed) * (1.0f - overlayRed2);
        }
        red = red * 255.0f + 0.5f;

        float green = 0;
        float overlayGreen = image1.pixelVector[i].pixelG / 255.0f;
        float overlayGreen2 = image2.pixelVector[i].pixelG / 255.0f;

        if(overlayGreen2 <= 0.5) {
            green = 2.0f * overlayGreen * overlayGreen2;
        }
        else {
            green = 1.0f - 2.0f*(1.0f - overlayGreen)*(1.0f - overlayGreen2);
        }
        green = green * 255.0f + 0.5f;

        float blue = 0;
        float overlayBlue = image1.pixelVector[i].pixelB / 255.0f;
        float overlayBlue2 = image2.pixelVector[i].pixelB / 255.0f;

        if(overlayBlue2 <= 0.5) {
            blue = 2.0f * overlayBlue * overlayBlue2;
        }
        else {
            blue = 1.0f - 2.0f * (1.0f - overlayBlue) * (1.0f - overlayBlue2);
        }
        blue = blue * 255.0f + 0.5f;

        Image::Pixel tempP;
        tempP.pixelR = red;
        tempP.pixelG = green;
        tempP.pixelB = blue;
        result.pixelVector.push_back(tempP);
    }
    return result;
}
