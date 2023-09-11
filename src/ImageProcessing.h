#include <iostream>
#include "Image.h"
#include <fstream>
#include "vector"
using namespace std;

class ImageProcessing {
public:
    //read and write
    Image readImage(string fileName);
    void writeImage(string fileName, Image image);
    //processing
    bool compare(Image image1, Image image2);
    Image multiply(Image image1, Image image2);
    Image subtract(Image image1, Image image2);
    Image screen (Image image1, Image image2);
    Image overlay(Image image1, Image image2);

};