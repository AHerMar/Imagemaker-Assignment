#include "ImageMaker.h"
#include <iostream>
#include <string>
#include <fstream>


// Your code goes here...
ImageMaker::ImageMaker() {
    width = 0;
    height = 0;
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
    //Sets the image to white
    for(int x = 0; x < MAX_WIDTH ; x++) {
        for(int y = 0; y < MAX_HEIGHT; y++) {
            image[x][y][0]= 255;
            image[x][y][1]= 255;
            image[x][y][2]= 255;
        }
    }
}

ImageMaker::ImageMaker(string filename) {
    width = MAX_WIDTH;
    height = MAX_HEIGHT;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            image[x][y][RED] = 255;
            image[x][y][GREEN] = 255;
            image[x][y][BLUE] = 255;
        }
    }
    LoadImage(filename);
    pen_red = 0;
    pen_green = 0;
    pen_blue = 0;
}

void ImageMaker::LoadImage(string filename) {
    int maxColorValue;
    int redValue;
    int greenValue;
    int blueValue;

    //Replacing pen_red to redValue, pen_green to greenValue, and pen_blue to blueValue
    ifstream infile;
    infile.open(filename);
    if(!infile.is_open()) {
        throw  "File failed to open";
    }

    //read magic number

    infile >> magic;
    if(magic != "P3") {
        throw "Bad magic number";
    }
    infile.ignore();
    //Gets the width, height, and color value from the file and stores them as a string.
    string sWidth, sHeight, smaxColorValue;
    infile >> sWidth >> sHeight >> smaxColorValue;
    //converts the numeric string into a integer value
    width = stoi(sWidth);
    height = stoi(sHeight);
    maxColorValue = stoi(smaxColorValue);


    if(width > MAX_WIDTH || width < 0 || height < 0 || height > MAX_HEIGHT) {
        throw "Bad image size";
    }
    if(maxColorValue != 255) {
        throw "Max color range not 255";
    }
    //Updated: swapping width and height to read image row by row
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            infile >> redValue;
            infile >> greenValue;
            infile >> blueValue;
            image[x][y][RED] = redValue;
            image[x][y][GREEN] = greenValue;
            image[x][y][BLUE] = blueValue;

            if(redValue > 255 || redValue < 0 || greenValue > 255 || greenValue < 0 ||
                blueValue > 255 || blueValue < 0) {
                throw "Color value invalid";
            }
        }
    }




}

void ImageMaker::SaveImage(string filename) {
    ofstream outfile;
    outfile.open(filename);
    //Writes header values
    outfile << "P3" << "\n";
    outfile << width << " " << height << "\n";
    outfile << "255" << "\n";
    //Updated: swapping width and height
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            outfile << image[x][y][RED] << " ";
            outfile << image[x][y][GREEN] << " ";
            outfile << image[x][y][BLUE] << "\n";
        }
    }
    if(width == 0 && height == 0) {
        throw "Image must have non-zero dimensions";
    }
}

int ImageMaker::GetWidth() {
    return width;
}

int ImageMaker::GetHeight() {
    return height;
}

void ImageMaker::SetWidth(int width) {
    if (width < 0 || width > MAX_WIDTH) {
        throw "Width out of bounds";
    }

    this->width = width;
}

void ImageMaker::SetHeight(int height) {
    if (height < 0 || height > MAX_HEIGHT) {
        throw "Height out of bounds";
    }

    this->height = height;
}

int ImageMaker::GetPenRed() {
    return pen_red;
}

int ImageMaker::GetPenGreen() {
    return pen_green;
}

int ImageMaker::GetPenBlue() {
    return pen_blue;
}

void ImageMaker::SetPenRed(int newR) {
    if(newR < 0 || newR > 255) {
        throw "Color value invalid";
    }
    pen_red = newR;
}

void ImageMaker::SetPenGreen(int newG) {
    if(newG < 0 || newG > 255) {
        throw "Color value invalid";
    }
    pen_green = newG;
}

void ImageMaker::SetPenBlue(int newB) {
    if (newB < 0 || newB > 255) {
        throw "Color value invalid";
    }
    pen_blue = newB;
}

void ImageMaker::DrawPixel(int x, int y) {
    image[x][y][RED] = pen_red;
    image[x][y][GREEN] = pen_green;
    image[x][y][BLUE] = pen_blue;
    if( x < 0 || x > width || y < 0 || y > height) {
        throw "Point out of bounds";
    }

    if(width == 0 && x == 0) {
        throw "Point out of bounds";
    }
    if(height == 0 && y == 0) {
        throw "Point out of bounds";
    }
 }

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {
    if(!PointInBounds(x1, y1)) {
        throw "Point out of bounds";
    }
    if(!PointInBounds(x2, y2)) {
        throw "Point out of bounds";
    }
    //Draws 4 lines to construct a rectangle
    DrawLine(x1, y1, x2,y1);
    DrawLine(x2,y1, x2,y2);
    DrawLine(x2,y2,x1,y2);
    DrawLine(x1,y2,x1,y1);

}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    //throw out of bounds
    //if coordinates are greater than image width or height
    if(x1 > width || x2 > width || y1 > height || y2 > height) {
        throw "Point out of bounds";
    }
    //negative x or y coordinates
    if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        throw "Point out of bounds";
    }

    //Handles the case of both points having the same coordinates
    if(x1 == x2 && y1 == y2) {
        DrawPixel(x1, y1);
        return;
    }

    //Handles the case of vertical lines but only works if y1 < y2(ie y1 = 2 to y2 =4)
    if(x1 == x2 && y1 < y2) {
        for(int y = y1; y <= y2; y++) {
            DrawPixel(x1, y);
        }
        return;
    }
    //Handles vertical lines when the y1 is bigger (ie y1 = 4 to y2 =2)
    if(x1 == x2 && y2 < y1) {
        for(int y = y2; y <= y1; y++) {
            DrawPixel(x1, y);
        }
        return;
    }

    double const slope = (static_cast<double>(y2) - static_cast<double>(y1)) /
        (static_cast<double>(x2) - static_cast<double>(x1));

    double const b = static_cast<double>(y1) - slope * static_cast<double>(x1);

    //Calculate y values for all x values
    //The for loop doesn't work if you are going from x = 6 to x = 2 vs x = 2 to x =6 so
    //the value of x1 has to be smaller one of the two. In the case that it isn't
    //swap x2 to be the initial x value
    if(x1 > x2) {
        for(int x = x2; x <= x1; x++) {
            double y = slope*x + b;
            round(y);
            int yvalue = static_cast<int>(y < 0 ? y- 0.5 : y + 0.5);
            DrawPixel(x,abs(yvalue));
        }
    } else{
        for(int x = x1; x <= x2; x++) {
            double y = slope*x + b;
            round(y);
            int yvalue = static_cast<int>(y < 0 ? y - 0.5 : y + 0.5);
            DrawPixel(x,abs(yvalue));
            //DrawPixel(x,abs(static_cast<int>(y))) doesn't work on the last test
            //because of truncation. To prevent this, add/subtract 0.5 to the
            //y before casting to int to prevent rounding errors
        }
    }
}

bool ImageMaker::PointInBounds(int x, int y) {
    //checks if x and y coordinates are valid
    if(x < 0 || x > MAX_WIDTH || y < 0 || y > MAX_HEIGHT) {
        return false;
    }
    return true;
}
