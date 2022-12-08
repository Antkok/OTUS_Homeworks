#include <string>

#include <iostream>


#include "csvreader.h"
#include "classifier.h"
#include "datapreprocessor.h"

using namespace std;
using namespace dlib;




int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;

    int cluster_num = std::atoi(argv[1]);
    std::string file_name = argv[2];


    // read
    CSVReader reader;
    std::string samples_file_name = "dataset.csv";
    if (argc >= 4)
        samples_file_name = argv[3];
    auto samples = reader.get_samples(samples_file_name);


    Classifier cl(file_name);
    cl.create_clusters(samples, cluster_num);
    cout << "dump clusters: " << cl.dump_cluster() << endl;

    // classificate and dump clusters


}