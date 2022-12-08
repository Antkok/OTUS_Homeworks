#pragma once

#include "user_data.h"
#include "datapreprocessor.h"

typedef radial_basis_kernel<userData> kernelType;


class Classifier{
public:
    Classifier(std::string file_name): _file_name(file_name), dpp(file_name){pKmean_cluster = nullptr;};

    void create_clusters(std::vector<userData> & samples, int cnum);
    bool dump_cluster();
    bool load_cluster();
    int classify(userData & sample);
    void print_close_samples(int cluster, userData sample);
private:
    std::string _file_name;
    std::shared_ptr<kkmeans<kernelType> > pKmean_cluster;
    DataPreProcessor dpp;
    std::vector<userData> _samples;

    double sample_distance(userData sample1, userData sample2);
};

