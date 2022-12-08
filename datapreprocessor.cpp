#include "datapreprocessor.h"

userData DataPreProcessor::normalize_sample(userData sample)
{
    userData normalized_sample;
    for (int i=0;i<DATA_DIM;i++)
    {
        normalized_sample(0,i)= (sample(0,i) - _min_sample(0, i));
        if (_interval(0,i) > 0)
            normalized_sample(0,i) = normalized_sample(0,i)/_interval(0,i);
        else
        {
            normalized_sample(0,i) = 0;
        }

    }
    return normalized_sample;
}

void DataPreProcessor::calculate_normalization_values(const std::vector<userData> & in_data)
{
    std::vector<userData> normalized_samples;
    normalized_samples.reserve(in_data.size());

    _max_sample = in_data[0];
    _min_sample = in_data[0];
    _interval = in_data[0];
    for (auto sample : in_data)
    {
        for (int i=0;i<DATA_DIM;i++)
        {
            if (_max_sample(0, i) < sample(0, i))
                _max_sample(0, i) = sample(0, i);

            if (_min_sample(0, i) > sample(0, i))
                _min_sample(0, i) = sample(0, i);
        }
    }
    for (int i=0;i<DATA_DIM;i++)
    {
        _interval(0,i) = _max_sample(0, i) - _min_sample(0, i);
    }
}

void DataPreProcessor::dump_normalization_values()
{
    string int_elem = _file_name + ".int";
    std::ofstream outInt(int_elem);
    if (outInt)
        serialize(_interval, outInt);
    outInt.close();

    string min_elem = _file_name + ".min";
    std::ofstream outMin(min_elem);
    if (outMin)
        serialize(_min_sample, outMin);
    outMin.close();
}

void DataPreProcessor::load_normalization_values()
{
    std::ifstream minIn;
    minIn.open(_file_name + ".min", std::ofstream::in);
    if (minIn)
        deserialize(_min_sample, minIn);
    minIn.close();

    std::ifstream intIn;
    intIn.open(_file_name + ".int", std::ofstream::in);
    if (intIn)
        deserialize(_interval, intIn);
    intIn.close();
}


std::vector<userData> DataPreProcessor::normalize_samples(const std::vector<userData> & in_data)
{
    std::vector<userData> normalized_samples;
    normalized_samples.reserve(in_data.size());

    for (auto & sample : in_data)
    {
        userData normalized_sample = normalize_sample(sample);
        normalized_samples.push_back(normalized_sample);
    }

    return normalized_samples;
}