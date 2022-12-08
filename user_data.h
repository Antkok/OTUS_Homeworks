#pragma once

#include <dlib/svm_threaded.h>

using namespace std;
using namespace dlib;
const int DATA_DIM = 7;

typedef matrix<double,DATA_DIM,1> userData;
typedef std::vector<userData> Samples;