#pragma once

#include <string>

#include "user_data.h"


class DataPreProcessor
{
public:
    DataPreProcessor(std::string file_name):_file_name(file_name){};

    userData normalize_sample(userData sample);

    void calculate_normalization_values(const std::vector<userData> & in_data);

    void dump_normalization_values();

    void load_normalization_values();


    std::vector<userData> normalize_samples(const std::vector<userData> & in_data);
private:
    std::string _file_name;
    userData _min_sample;
    userData _max_sample;
    userData _interval;
};
