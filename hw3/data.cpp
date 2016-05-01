#include "data.h"

Data::Data() {
}

Data::~Data() {  
}

void Data::parse(char *filePath) {
  ifstream fin(filePath);

  string line;
  getline(fin, line);
  strip(line);
  trim(line);
  mSplineType = line;

  getline(fin, line);
  strip(line);
  trim(line);
  mNumberOfCrossSections = atoi(line.c_str());

  getline(fin, line);
  strip(line);
  trim(line);
  mNumberOfControlPoints = atoi(line.c_str());

  for (int i = 0; i < mNumberOfCrossSections; i++)
    mCrossSections.push_back(CrossSection());

  int i = 0, j = 0;
  while (!fin.eof()) {
    getline(fin, line);
    strip(line);
    trim(line);
    if (line.length() == 0) continue;
    
    stringstream stream(line);
    vector<string> tokens;
    string token;
    while (stream >> token) tokens.push_back(token);

    if (tokens.size() == 1)
      mCrossSections.at(i).setScalingFactor(atof(tokens.at(0).c_str()));
    else if (tokens.size() == 4) {
      vector<float> rotationFactor;
      rotationFactor.push_back(atof(tokens.at(0).c_str()));
      rotationFactor.push_back(atof(tokens.at(1).c_str()));
      rotationFactor.push_back(atof(tokens.at(2).c_str()));
      rotationFactor.push_back(atof(tokens.at(3).c_str()));
      mCrossSections.at(i).setRotationFactor(rotationFactor);
    }
    else if (tokens.size() == 3) {
      vector<float> translationFactor;
      translationFactor.push_back(atof(tokens.at(0).c_str()));
      translationFactor.push_back(atof(tokens.at(1).c_str()));
      translationFactor.push_back(atof(tokens.at(2).c_str()));
      mCrossSections.at(i++).setTranslationFactor(translationFactor);
    }
    else {
      ControlPoint controlPoint(atof(tokens.at(0).c_str()), atof(tokens.at(1).c_str()));
      mCrossSections.at(i).addControlPoint(controlPoint);
      if (++j == mNumberOfControlPoints) j = 0;
    }
  }
}

string Data::getSplineType() {
  return mSplineType;
}

int Data::getNumberOfCrossSections() {
  return mNumberOfCrossSections;
}

int Data::getNumberOfControlPoints() {
  return mNumberOfControlPoints;
}

vector<CrossSection> Data::getCrossSections() {
  return mCrossSections;
}
