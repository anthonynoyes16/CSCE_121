#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int energy(const Pixel *const *image, int col, int row, int width, int height)
{
  Pixel x1, x2, y1, y2;
  bool left = false;   // x = 0
  bool right = false;  // x = width - 1
  bool top = false;    // y = 0
  bool bottom = false; // y = height - 1
  bool x_lock = false;
  bool y_lock = false;
  int gradient_x = 0;
  int gradient_y = 0;

  // check for width or height edges
  if (width <= 2)
  {
    gradient_x = 0;
    x_lock = true;
  }
  if (height <= 2)
  {
    gradient_y = 0;
    y_lock = true;
  }

  // check if on edges or corners
  if (!x_lock)
  {
    if (col == 0)
    {
      left = true;
      x1 = image[width-1][row];
      x2 = image[1][row];
    }
    if (col == width - 1)
    {
      right = true;
      x1 = image[width-2][row];
      x2 = image[0][row];
    }
    if (!left && !right) 
    {
      x1 = image[col-1][row];
      x2 = image[col+1][row];
    }
    gradient_x = pow(abs(x1.r - x2.r), 2) + pow(abs(x1.g - x2.g), 2) + pow(abs(x1.b - x2.b), 2);
  }
  if (!y_lock)
  {
    if (row == 0)
    {
      top = true;
      y1 = image[col][height-1];
      y2 = image[col][1];
    }
    if (row == height - 1)
    {
      bottom = true;
      y1 = image[col][height-2];
      y2 = image[col][0];
    }
    if (!bottom && !top)
    {
      y1 = image[col][row-1];
      y2 = image[col][row+1];
    }
    gradient_y = pow(abs(y1.r - y2.r), 2) + pow(abs(y1.g - y2.g), 2) + pow(abs(y1.b - y2.b), 2);
  }  
  return gradient_x + gradient_y;
}

int getVerticalSeam(const Pixel *const *image, int start_col, int width, int height, int *seam)
{
  seam[0] = start_col;
  int i = 0;
  i = start_col;
  int e_left = 0;
  int e_mid = 0;
  int e_right = 0;
  int e_curr = 0;
  int sum_energy = 0;
  sum_energy += energy(image, start_col, 0, width, height);

  if (width == 1) {
    for (int k = 1; k < height; k++) {
      seam[k] = 0;
      sum_energy += energy(image, 0, k, width, height);
    }
    return sum_energy;
  }
  for (int j = 1; j < height; j++) {
    sum_energy += e_curr;
    bool left_wall = false;
    bool right_wall = false;

    if (i == 0) {
      right_wall = true;
    }
    else if (i == width - 1) {
      left_wall = true;
    }

    if (left_wall) {
      e_mid = energy(image, i, j, width, height);
      e_right = energy(image, i - 1, j, width, height);
      if (e_right < e_mid) {
        e_curr = e_right;
        i -= 1;
      }
      else {
        e_curr = e_mid;
      }
    }

    else if (right_wall) {
      e_mid = energy(image, i, j, width, height);
      e_left = energy(image, i + 1, j, width, height);
      if (e_left < e_mid) {
        e_curr = e_left;
        i += 1;
      }
      else {
        e_curr = e_mid;
      }
    }
    
    else {
      e_left = energy(image, i + 1, j, width, height);
      e_mid = energy(image, i, j, width, height);
      e_right = energy(image, i - 1, j, width, height);
    
      if (e_mid < e_right && e_mid < e_left) {
        e_curr = e_mid;
      }
      else if (e_left < e_mid && e_left < e_right) {
        e_curr = e_left;
        i += 1;
      }
      else if (e_right < e_mid && e_right < e_left) {
        e_curr = e_right;
        i -= 1;
      }
      else if (e_mid == e_left || e_mid == e_right) {
        e_curr = e_mid;
      }
      else if (e_left == e_right) {
        e_curr = e_left;
        i += 1;
      }
    }
    seam[j] = i;
    if (j == height - 1) {
      sum_energy += e_curr;
    }
  }
  return sum_energy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int &width, int height, int *verticalSeam)
{
  Pixel x_new;
  for (int j = 0; j < height; j++) {
    for (int k = verticalSeam[j]; k < width-1; k++) {
        x_new = image[k+1][j];
        image[k][j] = x_new;
      }
  }
  width -= 1;
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const *image, int start_row, int width, int height, int *seam)
{
  if (image == nullptr) { ; }
  if (start_row == 0) { ; }
  if (width == 0) { ; }
  if (height == 0) { ; }
  if (seam == nullptr) { ; }
  return 0;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int &height, int *horizontalSeam)
{
if (image == nullptr) { ; }
if (width == 0) { ; }
if (height == 0) { ; }
if (horizontalSeam == nullptr) { ; }
}

int *findMinVerticalSeam(const Pixel *const *image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int *temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up
  delete[] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const *image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int *temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up
  delete[] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel **loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}