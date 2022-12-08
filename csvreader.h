#pragma once

#include <string>
#include <dlib/svm_threaded.h>

#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using namespace dlib;

#include "user_data.h"


class CSVReader
{
public:
    std::vector<userData> get_samples(string file_name);
    std::vector<userData> get_sample(string line);
    bool get_sample(userData & sample, string line);
private:
    static const int INPUT_DATA_SIZE = 8;
    std::vector<std::string> getNextLineAndSplitIntoTokens(std::string & line);
    userData vector_to_sample(std::vector<std::string> line_data);
};
