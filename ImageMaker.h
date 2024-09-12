//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    ImageMaker();
    //Precondition: none
    //Post-condition: The default constructor initializes the image to be white. The
    //dimensions (width and height) are set to 0 and the default pen color is set as black.

    ImageMaker(string filename);
    //Precondition: The constructor requires a ppm image filename as a string input.
    //Post-condition: The function sets the image dimensions to the max width and height
    //of 800 pixels and the default pen color to black. It initializes the image to white
    //and then loads the ppm image file.


    // Opens image with filename and stores information into
    void LoadImage(string filename);
    //Precondition: It requires a ppm image filename to be set as a string input. The
    //width and height, RGB values, and max color value within the filename must be valid values.
    //The image file must have P3 set as the magic number and be able to open.

    //Post-condition: The ppm image is opened and the image is then loaded into the
    //image matrix.

    void SaveImage(string filename);
    //Precondition: It requires a ppm image filename to be set as a string input. The
    //image must have non-zero dimensions.
    //Post-condition: The image is saved to the provided filename.

    // Size functions
    int GetWidth();
    //Precondition: None
    //Post-condition: The function returns the value of width.
    int GetHeight();
    //Precondition: None
    //Post-condition: The function returns the value of height.
    void SetWidth(int width);
    //Precondition: The width is set to a valid an integer value between 0 and
    //800.
    //Post-condition: The function sets the width of the image.
    void SetHeight(int height);
    //Precondition: The height is set to a valid integer value between 0 and
    //800.
    //Post-condition: The function sets the height of the image.

    // Color functions
    int GetPenRed();
    //Precondition: None
    //Post-condition: The function returns the current red pen color value.
    int GetPenGreen();
    //Precondition: None
    //Post-condition: The function returns the current green pen color value.
    int GetPenBlue();
    //Precondition: None
    //Post-condition: The function returns the current blue pen color value.
    void SetPenRed(int newR);
    //Precondition: The input (new red pen color value) must be an integer value and
    //cannot be negative nor exceed the max color value of 255.
    //Post-condition: The function sets the new red pen color value.
    void SetPenGreen(int newG);
    //Precondition: The input (new green pen color value) must be an integer value and
    //cannot be negative nor exceed the max color value of 255.
    //Post-condition: The function sets the new green pen color value.
    void SetPenBlue(int newB);
    //Precondition: The input (new blue pen color value) must be an integer value and
    //cannot be negative nor exceed the max color value of 255.
    //Post-condition: The function sets the new blue pen color value.

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen
    void DrawPixel(int x, int y);
    //Precondition: The inputs x and y must be an integer value and
    //must not be negative nor exceed the image width and height values.
    //Post-condition: The function colors the coordinate at (x,y) using the current
    //RGB pen values.
    void DrawRectangle(int x1, int y1, int x2, int y2);
    //Precondition: The inputs of the coordinate x and y values must be
    //integer values and must not be negative nor exceed the image width and height values.
    //Post-condition: The function draws a rectangle from the respective coordinates
    //using the current RGB pen values.
    void DrawLine(int x1, int y1, int x2, int y2);
    //Precondition: The inputs of the coordinate x and y values must be an
    //integer value and must not be negative nor exceed the image width and height
    //values.
    //Post-condition: The function draws a line from the first coordinate to the second
    //coordinate with the current RGB pen values.

private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions
    bool PointInBounds(int x, int y);  // Not a bad idea to implement
    //Precondition: The inputs x and y must be an integer.
    //Post-condition: Returns false if the coordinates are out of bounds.
    //Otherwise, it returns true.

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif //IMAGEMAKER_H
