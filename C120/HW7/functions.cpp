#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

void loadCorners(std::string filename, Corner imageCorners[MAX_CORNERS], unsigned int& numberOfCorners){
    ifstream inFS (filename);
    numberOfCorners = 0;
    if (!inFS.is_open()) throw runtime_error("Failed to open " + filename);
    unsigned int x_corner, y_corner;
    while (inFS >> x_corner >> y_corner){
        if (numberOfCorners >= MAX_CORNERS) throw runtime_error("Too many corners in " + filename);
        imageCorners[numberOfCorners++] = {x_corner, y_corner};
    }


}

double errorCalculation(Pixel image1[][MAX_HEIGHT], const unsigned int width1, const unsigned int height1,
                      Corner image1corner,
                      Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                      Corner image2corner){
        int errorSum = 0;

    for (int height_Adjust = -21/2; height_Adjust <= 21/2; ++height_Adjust){
        for (int width_Adjust = -21/2; width_Adjust <= 21/2; ++width_Adjust){ // Ideally goes through each pixel in image1 & 2 neighborhood
            
            // CornerLocation +- adjustment = neighborhood pixel  :  At w/h adjustment 0/0 we get corner center
            int image1Width = image1corner.x + width_Adjust; int image1Height = image1corner.y + height_Adjust;
            int image2Width = image2corner.x + width_Adjust; int image2Height = image2corner.y + height_Adjust;
            // Make sure no neighborhood pixel is outside bounds
          if (image1Width < 0 || (unsigned int) image1Width + 1 > width1
                    || image2Width < 0 || (unsigned int) image2Width + 1 > width2) {return INFINITY;}
            if (image1Height < 0 || (unsigned int) image1Height + 1 > height1
                    || image2Height < 0 || (unsigned int) image2Height + 1 > height2) {return INFINITY;}

            Pixel pixel1 = image1[image1Width][image1Height];
            Pixel pixel2 = image2[image2Width][image2Height];
            enum Color{RED, GREEN, BLUE};
            for (int color = RED; color <= BLUE; ++color){

                int p1Val, p2Val;
                switch (color){ // Depending on whether the loop is R, G, or B, p1 & 2 will be assigned the color value of R, G, or B
                case RED:
                    p1Val = pixel1.r; p2Val = pixel2.r;
                    break;
                case GREEN:
                    p1Val = pixel1.g; p2Val = pixel2.g; 
                    break;
                case BLUE:
                    p1Val = pixel1.b; p2Val = pixel2.b; 
                    break;
                }
                errorSum += abs(p1Val - p2Val);
            }
        }
    }
    
    return errorSum;
}

void matchCorners(CornerPair matchedPairs[MAX_CORNERS], unsigned int &matched_count,
                  Pixel image1[][MAX_HEIGHT], const unsigned int width1, const unsigned int height1,
                  Corner image1corners[], unsigned int image1CornerCount,
                  Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                  Corner image2corners[], unsigned int image2CornerCount){
    
    int pair_index = 0;
   
    Corner usedImageCorners[MAX_CORNERS];
    for (unsigned int corner1_index = 0; corner1_index < image1CornerCount; ++corner1_index){ 
        Corner image1corner = image1corners[corner1_index];
        double lowestErrorCalc = INFINITY;     
        for (unsigned int corner2_index = 0; corner2_index < image2CornerCount; ++corner2_index){ // for each unique (corner1, corner2) pairing
            bool skipCornerFlag = false;
            Corner image2corner = image2corners[corner2_index];
            for (int i = 0; i < pair_index; ++i){
                if (image2corner.x == usedImageCorners[i].x && image2corner.y == usedImageCorners[i].y) {
                    skipCornerFlag = true;
                    i = pair_index + 99;}
            }

            if (skipCornerFlag) {
                continue;
            }
            double error_calc = errorCalculation(image1, width1, height1, image1corner, image2, 
                                                        width2, height2, image2corner);
            // If error_calc wasn't possible, will skip all corner2Pairings and go to next image1 corner
            if (error_calc == INFINITY) {
                 continue;
                 }
            
            else if (error_calc < lowestErrorCalc){ // If new error calc lower than previously held lower calc
                usedImageCorners[pair_index] = image2corner;
                matchedPairs[pair_index] = {image1corner, image2corner, error_calc};
                lowestErrorCalc = error_calc;
                }
        }
        // By the time matchedPairs goes to next index, only the lowest corner1[i] corner2[j] pairing will be allowed
        
        if (lowestErrorCalc < INFINITY){
            pair_index++;
        }
        
    }
    matched_count = pair_index;
}

void mapCoordinates(const double H[3][3], unsigned int x, unsigned int y,
                    double& mapped_x, double& mapped_y){
    
    double x_prime = H[0][0]*x + H[0][1]*y + H[0][2];
    double y_prime = H[1][0]*x + H[1][1]*y + H[1][2];
    double z_prime = H[2][0]*x + H[2][1]*y + H[2][2];
    mapped_x = x_prime / z_prime;
    mapped_y = y_prime / z_prime;




}

void mergeImages( Pixel image1[][MAX_HEIGHT], unsigned int &width1, unsigned int &height1,
                  Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                  double H[3][3] ){
    for (unsigned int hei1 = 0; hei1 < MAX_HEIGHT; ++hei1){
        for (unsigned int wid1 = 0; wid1 < MAX_WIDTH; ++wid1){
            double xMapped; 
            double yMapped; 
            Pixel I1_pixel;
            Pixel I2_pixel;
            Pixel newPixel;
            bool p1_hasValue = false, p2_hasValue = false;

            mapCoordinates(H, wid1, hei1, xMapped, yMapped);
            if (xMapped <= width2 && yMapped <= height2
                    && xMapped > 0 && yMapped > 0){
                I2_pixel = bilinear_interpolation(image2, width2, height2, xMapped, yMapped);    
                p2_hasValue = true;        
            }
            if (wid1 < width1 && hei1 < height1){
                I1_pixel = image1[wid1][hei1];
                p1_hasValue = true;
            }
            
            if (p1_hasValue && p2_hasValue){
                newPixel.r = (I1_pixel.r + I2_pixel.r) / 2;
                newPixel.g = (I1_pixel.g + I2_pixel.g) / 2;
                newPixel.b = (I1_pixel.b + I2_pixel.b) / 2;
            }
            else if (!p1_hasValue && !p2_hasValue){
                newPixel = {0, 0, 0};
            }
            else{
                newPixel = (p1_hasValue && !p2_hasValue) ? I1_pixel : I2_pixel;
            }
            image1[wid1][hei1] = newPixel;

        }


    }
}