#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  int* A = new int[length] ();
  return A;
}

void deleteSeam(int* seam) {
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  // declare/define and open input file stream
  ifstream ifs (filename);
  
  // check if input stream opened successfully
  if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }
  
  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }
  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w >> h;
  if (!ifs) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (w != width) { // check that width matches what was passed into the function
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h != height) { // check that height matches what was passed into the function
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }

  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (colorMax != 255) {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  }
  /*
  int totalpixels = width * height * 3;
  int numberCount = 0;
  while (!ifs.eof()) {
    int tempval;
    ifs >> tempval;
    if (!ifs && totalpixels < numberCount && tempval != ' ') {
      cout << tempval << endl;
      cout << "Error: too many color values" << endl;
      return false;
    } else if(!ifs) {
      cout << "Error: read non-integer value" << endl;
      return false;
    }
    numberCount++;
  }
  
  if (totalpixels > numberCount) {
    cout << "Error: not enough color values" << endl;
    return false;
  } else if (totalpixels < numberCount) {
    cout << "Error: too many color values" << endl;
    return false;
  }
  ifs.close();
  int tempval1, tempval2, tempval3;
  ifstream ifs1 (filename);
  ifs1 >> tempval1 >>tempval2 >> tempval3;
  */
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Pixel object;
      ifs >> object.r; // red input
      if (object.r > 255 || object.r < 0) {
        cout << "Error: invalid color value " << object.r << endl;
        return false;
      }
      ifs >> object.g; // green input
      if (object.g > 255 || object.g < 0) {
        cout << "Error: invalid color value " << object.g << endl;
        return false;
      }
      
      ifs >> object.b; // blue input
      if (object.b > 255 || object.b < 0) {
        cout << "Error: invalid color value " << object.b << endl;
        return false;
      }
      if(ifs.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      
      
      image[j][i] = object;
    }
  }
  ifs.close();
  return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  cout << "Outputting image..." << endl;
  // TODO(student): declare/define and open output file stream
  ofstream ofs (filename);
  // TODO(student): check if output stream opened successfully
  if (!ofs.is_open()) {
    cout << "Error: failed to open output file " << filename << endl;
    return false;
  }
  // TODO(student): output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  // TODO(student): output pixels
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      ofs << image[j][i].r << endl;
      ofs << image[j][i].g << endl;
      ofs << image[j][i].b << endl;
    }
  }
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
  int xpositionPos = x + 1;
  int xpositionNeg = x - 1;
  int ypositionPos = y + 1;
  int ypositionNeg = y - 1;
  // test for edges cases
  
  if (ypositionPos > height - 1) {
    ypositionPos = 0;
  }
  if (ypositionNeg < 0) {
    ypositionNeg = height - 1;
  }
  if (xpositionPos > width - 1 ) {
    xpositionPos = 0;
  }
  if (xpositionNeg < 0) {
    
    xpositionNeg = width - 1;
  }
  
  // find x measurements
  int xr, xg, xb;
  xr = image[xpositionPos][y].r - image[xpositionNeg][y].r;
  xg = image[xpositionPos][y].g - image[xpositionNeg][y].g;
  xb = image[xpositionPos][y].b - image[xpositionNeg][y].b;
  // compute change in x
  int xChange = (xr * xr) + (xg * xg) + (xb * xb);
  // find y measurements
  int yr, yg, yb;
  yr = image[x][ypositionPos].r - image[x][ypositionNeg].r;
  yg = image[x][ypositionPos].g - image[x][ypositionNeg].g;
  yb = image[x][ypositionPos].b - image[x][ypositionNeg].b;
  // compute change in y
  int yChange = (yr * yr) + (yg * yg) + (yb * yb);
  // compute final energy level
  int totalEnergy = xChange + yChange;
  return totalEnergy;
}


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  int col = start_col;
  int totalEnergy = energy(image, col, 0, width, height);
  seam[0] = col;
  for (int row = 1; row < height; row++){
    
    int midEnergy = energy(image, col, row, width, height);
    int leftEnergy = midEnergy;
    int rightEnergy = midEnergy;
    if (col < width - 1) {
      rightEnergy = energy(image, col + 1, row, width, height);
    }
    if (col > 0) {
      leftEnergy = energy(image, col - 1, row, width, height);
    }
    if (rightEnergy <= leftEnergy && rightEnergy < midEnergy) {  // my right looking at the picture
      col += 1;
      totalEnergy += rightEnergy;
    } else if (leftEnergy < rightEnergy && leftEnergy < midEnergy) {
      col -= 1;
      totalEnergy += leftEnergy;
    } else { // col stays the same
      totalEnergy += midEnergy;
    }
    seam[row] = col; // row is just an index variable here
  }
  return totalEnergy;
}




int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* minimalSeam = new int[height];
  int minimalEnergy = loadVerticalSeam(image, 0, width, height, minimalSeam);
  for (int col = 1; col < width; col++) {
    int* tempSeam = new int[height];
    int tempEnergy = loadVerticalSeam(image, col, width, height, tempSeam);
    if (tempEnergy < minimalEnergy) {
      delete[] minimalSeam;
      minimalSeam = tempSeam;
      minimalEnergy = tempEnergy;
    } else {
      delete[] tempSeam;
    }
  }
  return minimalSeam;
}



void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int row = 0; row < height; row++) {
    int col = verticalSeam[row];
    for (int index = col; index < width - 1; index++) {
      image[index][row] = image[index+1][row];
    }
  }
}




int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  int row = start_row;
  int totalEnergy = energy(image, 0, row, width, height);
  seam[0] = row;
  for (int col = 1; col < width; col++){
    
    int midEnergy = energy(image, col, row, width, height);
    int leftEnergy = midEnergy;
    int rightEnergy = midEnergy;
    if (row < height - 1) {
      rightEnergy = energy(image, col, row + 1, width, height);
    }
    if (row > 0) {
      leftEnergy = energy(image, col, row - 1, width, height);
    }
    if (rightEnergy <= leftEnergy && rightEnergy < midEnergy) {  // my right looking at the picture
      row += 1;
      totalEnergy += rightEnergy;
    } else if (leftEnergy < rightEnergy && leftEnergy < midEnergy) {
      row -= 1;
      totalEnergy += leftEnergy;
    } else { // col stays the same
      totalEnergy += midEnergy;
    }
    seam[row] = row; // row is just an index variable here
  }
  return totalEnergy;
}


int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  int* minimalSeam = new int[width];
  int minimalEnergy = loadHorizontalSeam(image, 0, width, height, minimalSeam);
  for (int row = 1; row < height; row++) {
    int* tempSeam = new int[width];
    int tempEnergy = loadHorizontalSeam(image, row, width, height, tempSeam);
    if (tempEnergy < minimalEnergy) {
      delete[] minimalSeam;
      minimalSeam = tempSeam;
      minimalEnergy = tempEnergy;
    } else {
      delete[] tempSeam;
    }
  }
  return minimalSeam;
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
  for (int col = 0; col < width; col++) {
    int row = horizontalSeam[col];
    for (int index = row; index < height - 1; index++) {
      image[col][index] = image[col][index+1];
    }
  }
}



