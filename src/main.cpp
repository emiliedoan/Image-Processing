#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
#include "ImageProcessing.h"

using namespace std;
int main() {
    ImageProcessing process;
    unsigned int testGrade = 0;

    //task 1 MULTIPLY LAYER1 PATTERN1
    Image layer1 = process.readImage("input/layer1.tga");
    Image pattern1 = process.readImage("input/pattern1.tga");
    Image example = process.readImage("examples/EXAMPLE_part1.tga");

    Image result = process.multiply(layer1,pattern1);

    process.writeImage("output/part1.tga",result);

    if(process.compare(example, result)){
        cout<<"Task #1...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #1...... Failed!" << endl;


//task 2 SUBTRACT CAR LAYER2
    Image car = process.readImage("input/car.tga");
    Image layer2 = process.readImage("input/layer2.tga");
    example = process.readImage("examples/EXAMPLE_part2.tga");

    result = process.subtract(car,layer2);

    process.writeImage("output/part2.tga",result);

    if(process.compare(example, result)){
        cout<<"Task #2...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #2...... Failed!" << endl;


    //task 3 MULTIPLY LAYER1 PATTERN2 SCREEN TEXT RESULT
     layer1 = process.readImage("input/layer1.tga");
    Image pattern2 = process.readImage("input/pattern2.tga");
    Image text = process.readImage("input/text.tga");
    example = process.readImage("examples/EXAMPLE_part3.tga");
    result = process.multiply(layer1,pattern2);
    Image result2 = process.screen(text, result);
    process.writeImage("output/part3.tga",result2);
    if(process.compare(example, result2)){
        cout<<"Task #3...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #3...... Failed!" << endl;


//task 4 MULTIPLY LAYER2 CIRCLES SUBTRACT RESULT PATTERN2
     layer2 = process.readImage("input/layer2.tga");
    Image circles = process.readImage("input/circles.tga");
    example = process.readImage("examples/EXAMPLE_part4.tga");

    result = process.multiply(layer2,circles);

    pattern2 = process.readImage("input/pattern2.tga");
    result2 = process.subtract(result, pattern2);
    process.writeImage("output/part4.tga",result2);

    if(process.compare(example, result2)){
        cout<<"Task #4...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #4...... Failed!" << endl;


    //task 5 OVERLAY LAYER1 PATTERN1
     layer1 = process.readImage("input/layer1.tga");
     pattern1 = process.readImage("input/pattern1.tga");
    example = process.readImage("examples/EXAMPLE_part5.tga");

    result = process.overlay(layer1,pattern1);

    process.writeImage("output/part5.tga",result);
    if(process.compare(example, result)){
        cout<<"Task #5...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #5...... Failed!" << endl;

    //task 6 ADD 200 GREEN TO CAR
     car = process.readImage("input/car.tga");
    example = process.readImage("examples/EXAMPLE_part6.tga");
    for(unsigned int i = 0; i <(car.header.height * car.header.width);i++){
        int green = car.pixelVector[i].pixelG;
        green += 200;
        if(green > 255)
            car.pixelVector[i].pixelG = 255;
        else
            car.pixelVector[i].pixelG = green;
    }
    process.writeImage("output/part6.tga",car);
    if(process.compare(example, car)){
        cout<<"Task #6...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #6...... Failed!" << endl;

    //task 7
     car = process.readImage("input/car.tga");
    example = process.readImage("examples/EXAMPLE_part7.tga");
    for(unsigned int i = 0; i <(car.header.height * car.header.width);i++){
        int red = car.pixelVector[i].pixelR;
        red *= 4;
        if(red > 255)
            car.pixelVector[i].pixelR = 255;
        else
            car.pixelVector[i].pixelR = red;

        car.pixelVector[i].pixelB *=0;
    }
    process.writeImage("output/part7.tga",car);

    if(process.compare(example, car)){
        cout<<"Task #7...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #7...... Failed!" << endl;


    //task 8
    car = process.readImage("input/car.tga");
    example = process.readImage("examples/EXAMPLE_part8_r.tga");
    Image example2 = process.readImage("examples/EXAMPLE_part8_g.tga");
    Image example3 = process.readImage("examples/EXAMPLE_part8_b.tga");
//make red
    for(unsigned int i = 0; i <(car.header.height * car.header.width);i++){
        car.pixelVector[i].pixelB = car.pixelVector[i].pixelR;
        car.pixelVector[i].pixelG = car.pixelVector[i].pixelR;
    }
    process.writeImage("output/part8_r.tga",car);
    Image Part8_r = process.readImage("output/part8_r.tga");

    //make green
     car = process.readImage("input/car.tga");
    for(unsigned int i = 0; i <(car.header.height * car.header.width);i++){
        car.pixelVector[i].pixelR = car.pixelVector[i].pixelG;
        car.pixelVector[i].pixelB = car.pixelVector[i].pixelG;
    }
    process.writeImage("output/part8_g.tga",car);
    Image Part8_g = process.readImage("output/part8_g.tga");

    //make blue
     car = process.readImage("input/car.tga");
    for(unsigned int i = 0; i <(car.header.height * car.header.width);i++){
        car.pixelVector[i].pixelR = car.pixelVector[i].pixelB;
        car.pixelVector[i].pixelG = car.pixelVector[i].pixelB;
    }
    process.writeImage("output/part8_b.tga",car);
    Image Part8_b = process.readImage("output/part8_b.tga");
    //compare all 3 files with their examples
    if((process.compare(example, Part8_r))&&(process.compare(example2,Part8_g))&&(process.compare(example3,Part8_b))){
        cout<<"Task #8...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #8...... Failed!" << endl;


//task 9
    Image layerRed = process.readImage("input/layer_red.tga");
    Image layerGreen = process.readImage("input/layer_green.tga");
    Image layerBlue = process.readImage("input/layer_blue.tga");
    example = process.readImage("examples/EXAMPLE_part9.tga");

    for(unsigned int i = 0; i <(layerRed.header.height * layerRed.header.width);i++){
        layerRed.pixelVector[i].pixelB = 0;
        layerRed.pixelVector[i].pixelG = 0;
        layerGreen.pixelVector[i].pixelR = 0;
        layerGreen.pixelVector[i].pixelB = 0;
        layerBlue.pixelVector[i].pixelR = 0;
        layerBlue.pixelVector[i].pixelG = 0;
    }
    result = process.screen(layerRed, layerGreen);
    result = process.screen(result, layerBlue);

    process.writeImage("output/part9.tga",result);
    //comapre
    if(process.compare(example, result)){
        cout<<"Task #9...... Passed!" << endl;
        testGrade++;
    }else
        cout<<"Task #9...... Failed!" << endl;


    //task 10 FLIP IMAGE
    Image text2 = process.readImage("input/text2.tga");
    example = process.readImage("examples/EXAMPLE_part10.tga");
    for(unsigned int i = 0; i < (text2.header.width); i++){
        unsigned int j = i;
        //why do i have to put -i-1
        unsigned int k = (text2.header.width * text2.header.height ) - i -1;
       // while(i<k){
         //swap(text2.pixelVector[i],text2.pixelVector[k]);
        // i+=text2.header.width;
        // k-=text2.header.width;
       // }
       //swap pixels
        while(j < k){
            swap(text2.pixelVector[j],text2.pixelVector[k]);
            j += text2.header.width;
            k -= text2.header.width;
        }
    }
    process.writeImage("output/part10.tga",text2);

    if(process.compare(example, text2)){
        cout<<"Task #10...... Passed!" << endl;
        testGrade++;
    }
    else
        cout<<"Task #10...... Failed!" << endl;


cout<<"Test results: " << testGrade << "/10"<<endl;
    return 0;

}