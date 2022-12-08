#include "csvreader.h"
#include <iostream>

std::vector<userData> CSVReader::get_samples(string file_name)
{
    std::vector<userData> samples;
    std::ifstream file(file_name);
    std::string line;
    while(file)
    {
        std::getline(file,line);
        std::vector<string> line_data = getNextLineAndSplitIntoTokens(line);
        if (line_data.size()!=INPUT_DATA_SIZE)
        {
            continue;
        }
        auto sample = vector_to_sample(line_data);
        samples.push_back(sample);
    }
    return samples;
}


bool CSVReader::get_sample(userData & sample, std::string line)
{
    std::vector<string> line_data = getNextLineAndSplitIntoTokens(line);
    if (line_data.size()!=INPUT_DATA_SIZE)
    {
        cout << line_data.size() << endl;
        return false;
    }
    sample = vector_to_sample(line_data);
    return true;
}


std::vector<std::string> CSVReader::getNextLineAndSplitIntoTokens(std::string & line)
{
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream,cell, ';'))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.emplace_back("");
    }
    return result;
}


userData CSVReader::vector_to_sample(std::vector<std::string> line_data)
{
    userData res;
    if (line_data.size() != INPUT_DATA_SIZE)
        return res;

    for (int i=0;i<6;i++)
    {
        double val = strtod(line_data[i].c_str(), nullptr);
        res(0,i) = val;
    }
    long stage = strtol(line_data[6].c_str(), nullptr, 0);
    long max_stages = strtol(line_data[7].c_str(), nullptr, 0);

    double stage_factor = 1.0;
    if ((stage == 1) || (stage != max_stages))
        stage_factor = 0.0;
    res(0,6) = stage_factor;

    return res;
}
