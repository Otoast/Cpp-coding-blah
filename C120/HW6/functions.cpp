#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  ofstream outFS (filename);
  if (!outFS.is_open()) throw runtime_error("Failed to open <filename>");
  outFS << "P3\n" << width << " " << height << "\n255" << endl;
  for (unsigned int hei = 0; hei < height; ++hei){
    for (unsigned int wid = 0; wid < width; ++wid){
        outFS << image[wid][hei].r << " " << image[wid][hei].g << " " << image[wid][hei].b << " ";
        }
    outFS << "\n";
  }
  outFS.flush();
  outFS.close();

}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  // TODO: implement image loading
  ifstream inFS(filename);
  if (!inFS.is_open()) throw runtime_error("Failed to open <filename>");
  string inData = ""; inFS >> inData;
  if (!(inData == "p3" ||inData == "P3")) throw runtime_error("invalid type <type>");
  string w, h;
  inFS >> w >> h >> inData;
  int w_asInt, h_asInt;
  if (!isdigit(*w.c_str()) || !isdigit(*h.c_str())) throw runtime_error("Invalid dimensions");
  w_asInt = stoi(w), h_asInt = stoi(h);  
  if((w_asInt != stod(w)) || (h_asInt != stod(h))) throw runtime_error("Invalid dimensions");
  if ((w_asInt < 0 || h_asInt < 0) || (w_asInt > static_cast<int>(MAX_WIDTH) || h_asInt > static_cast<int>(MAX_HEIGHT)))
    { throw runtime_error("Invalid dimensions"); }
  
  width = w_asInt; height = h_asInt;

  
  
  short red, green, blue;
  for (unsigned int hei = 0; hei < height; ++hei){
    for(unsigned int wid = 0; wid < width; ++wid){
      red = -256, blue = -256, green = -256;
      inFS >> red >> green >> blue;
      if (red >= 256 || green >= 256 || blue >= 256 || red < 0 || blue < 0 || green < 0){
        throw  runtime_error("Invalid color value");
      }
      image[wid][hei] = {red, green, blue};
      
    }
  }
  if (inFS >> red) throw runtime_error("Too many values");
  inFS.close();

  
}


double map_coordinates(unsigned int source_dimension, unsigned int target_dimension, unsigned int pixel_coordinate){
  return (static_cast<double>(source_dimension - 1) / (target_dimension - 1)) * pixel_coordinate;
  
}

Pixel bilinear_interpolation(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, double x, double y) {
  (void)height; (void)width;
  int x_floor = floor(x), x_ceil = ceil(x);
  int y_floor = floor(y), y_ceil = ceil(y);
  Pixel pixel1 = image[x_floor][y_floor]; Pixel pixel2 = image[x_ceil][y_floor];
  Pixel pixel3 = image[x_floor][y_ceil]; Pixel pixel4 = image[x_ceil][y_ceil];
  Pixel newPixel;
 
  //cout << "SOURCE PIXEL APPROX is (" << x << ", " << y << "). ROUNDED IS: |" << x_floor << " " << x_ceil << "|" << y_floor << " " << y_ceil << "|----" << endl;
  for (int rgb_colorValue = 0; rgb_colorValue < 3; ++rgb_colorValue){ //Iterates through red, green, blue
    int p1Val, p2Val, p3Val, p4Val; // Holds p1-4 color values
    short* newPixelColorValue = nullptr; // Will hold the memory address for newPixel R G or B
    double interpolateValue1, interpolateValue2, mappedColorValue;
    switch (rgb_colorValue){ // Depending on whether the loop is R, G, or B, p1-4 will be assigned the color value of R, G, or B
      // Memory address newPixelColorValue will get assigned memory address of newPixel R G or B
      case 0:
        p1Val = pixel1.r; p2Val = pixel2.r; 
        p3Val = pixel3.r; p4Val = pixel4.r;
        newPixelColorValue = &newPixel.r;
        break;
      case 1:
        p1Val = pixel1.g; p2Val = pixel2.g; 
        p3Val = pixel3.g; p4Val = pixel4.g;
        newPixelColorValue = &newPixel.g;
        break;
      case 2:
        p1Val = pixel1.b; p2Val = pixel2.b; 
        p3Val = pixel3.b; p4Val = pixel4.b;
        newPixelColorValue = &newPixel.b;
        break;
    }
    mappedColorValue = p1Val; // In case conditions listed under are not met

    if (x_ceil != x_floor && y_ceil != y_floor){ // x and y are decimals so floor and ceil return diff values
      // cout << "different rgb " << rgb_colorValue <<" is: " << mappedColorValue << endl;
      interpolateValue1 = (x - x_floor) * p2Val + (x_ceil - x) * p1Val;
      interpolateValue2 = (x - x_floor) * p4Val + (x_ceil - x) * p3Val;
      mappedColorValue = (y_ceil - y) * interpolateValue1 + (y - y_floor) * interpolateValue2;
    }
    else if (x_ceil == x_floor && y_ceil != y_floor){ // x is an integer, y is a decimal (xceil and floor the same y, is not)
      mappedColorValue = (y_ceil - y) * p1Val + (y - y_floor) * p3Val;
      // cout <<"xEQUAL rgb " << rgb_colorValue <<" is: " << mappedColorValue << endl;
    }
    else if (x_ceil != x_floor && y_ceil == y_floor){ // y is an integer, x is a decimal
      // cout << "yEQUALrgb " << rgb_colorValue <<" is: " << mappedColorValue << endl;
      mappedColorValue = (x_ceil - x) * p1Val + (x - x_floor) * p2Val;
    }
    *newPixelColorValue = static_cast<short>(round(mappedColorValue));  // newPixel will be updated to hold new calculated R G B
  }
  return newPixel;
}

void scale_image(Pixel sourceImage[][MAX_HEIGHT], unsigned int sourceWidth, unsigned int sourceHeight,
                   Pixel targetImage[][MAX_HEIGHT], unsigned int targetWidth, unsigned int targetHeight){
  // Iterates through every pixel in the new image size

  for (unsigned int hei = 0; hei < targetHeight; ++hei){
    for(unsigned int wid = 0; wid < targetWidth; ++wid){
      // Approximated x & y coordinates on where the target pixel would be at source
      double yMapped = map_coordinates(sourceHeight, targetHeight, hei); 
      double xMapped = map_coordinates(sourceWidth, targetWidth, wid);
      // Specific pixel color will be calculated and put into the new image
      targetImage[wid][hei] = bilinear_interpolation(sourceImage, sourceWidth, sourceHeight, xMapped, yMapped);
        }

  }

}