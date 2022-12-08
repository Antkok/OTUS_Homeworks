#include "classifier.h"

void Classifier::create_clusters(std::vector<userData> & samples, int cnum)
{
    dpp.calculate_normalization_values(samples);
    auto normalized_samples = dpp.normalize_samples(samples);

    std::vector<userData> initial_centers;
//    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8)
    kcentroid<kernelType> kc(kernelType(0.1),0.01, 8);
    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.

    pKmean_cluster = std::make_shared<kkmeans<kernelType>>(kc);
    pKmean_cluster->set_number_of_centers(cnum);
    pick_initial_centers(cnum, initial_centers, normalized_samples, pKmean_cluster->get_kernel());
    pKmean_cluster->train(normalized_samples, initial_centers);

    _samples = samples;

}


bool Classifier::dump_cluster()
{
    dpp.dump_normalization_values();

    kcentroid<kernelType> kc(kernelType(0.1),0.01, 8);
    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.

    auto newCluster = std::make_shared<kkmeans<kernelType>>(kc);
    if (pKmean_cluster != nullptr)
    {
        string classificator_file = _file_name + ".cls";
        std::ofstream outClass(classificator_file, ofstream::out);
        if (outClass)
            serialize(*pKmean_cluster, outClass);
        outClass.close();
        return true;
    }

    std::map<int, Samples> clusters;
    for (auto sample : _samples)
    {
        auto result_class = classify(sample);
        clusters[result_class].push_back(sample);
    }
    std::cout << "Cluster size: " << clusters.size() << std::endl;
    for (auto pair : clusters)
    {
        std::string result_file = _file_name + "." + to_string(pair.first);
        serialize(result_file) << pair.second;
    }

    return false;
}


bool Classifier::load_cluster() {
    dpp.load_normalization_values();

    kcentroid<kernelType> kc(kernelType(0.1), 0.01, 8);
    pKmean_cluster = std::make_shared<kkmeans<kernelType>>(kc);

    try {
        string classificator_file = _file_name + ".cls";
        std::ifstream outClass(classificator_file, ifstream::in);
        if (outClass)
            deserialize(*pKmean_cluster, outClass);
        outClass.close();
        return true;
    }
    catch (exception &e) {
        cout << "Error during load " << e.what() << endl;
        return false;
    }


}


int Classifier::classify(userData & sample)
{
    auto normalized_sample = dpp.normalize_sample(sample);
    int result_class = -1;
    if (pKmean_cluster != nullptr)
    {
        result_class = (*pKmean_cluster)(normalized_sample);
    }
    else
    {
        std::cout << "not loaded" << endl;
    }
    return result_class;
}

void Classifier::print_close_samples(int cluster, userData sample)
{
    Samples cluster_samples;
    std::string result_file = _file_name + "." + to_string(cluster);
    Samples cur_cluster;
    deserialize(result_file) >> cur_cluster;
    std::map<double, userData> sample_dist_map;
    for (auto cluster_sample : cur_cluster)
    {
        sample_dist_map[sample_distance(cluster_sample, sample)] = cluster_sample;
    }

    for (auto pair : sample_dist_map)
    {
        cout << pair.second << endl;
    }
}



double Classifier::sample_distance(userData sample1, userData sample2)
{
    double dim1_dist = (sample1(0)-sample2(0))*(sample1(0)-sample2(0));
    double dim2_dist = (sample1(1)-sample2(1))*(sample1(1)-sample2(1));
    return sqrt(dim1_dist+dim2_dist);
}