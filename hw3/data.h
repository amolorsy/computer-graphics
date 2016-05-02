#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "cross_section.h"

using namespace std;

static inline void ltrim(string &str) {
  str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
}

static inline void rtrim(string &str) {
  str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
}

static inline void trim(string &str) {
  ltrim(str);
  rtrim(str);
}

static inline void strip(string &str) {
  int found = str.find('#');
  if (found != string::npos) str.erase(found, str.length() - 1);
}

class Data {
  private:
    string mSplineType;
    int mNumberOfCrossSections; // The number of cross sections.
    int mNumberOfControlPoints; // The number of control points per cross section.

    vector<CrossSection> mCrossSections;

  public:
    Data();
    ~Data();

    void parse(char *filePath);

    string getSplineType();
    int getNumberOfCrossSections();
    int getNumberOfControlPoints();
    vector<CrossSection> getCrossSections();

    void modifyNumberOfCrossSections(int numberOfCrossSections);
};
