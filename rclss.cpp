#include <string>

#include "csvreader.h"
#include "classifier.h"
#include "datapreprocessor.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;

    std::string file_name = argv[1];

    // read
    CSVReader reader;

    Classifier cl(file_name);
    cout << "load cluster" << endl;
    cl.load_cluster();
    cout << "loaded cluster" << endl;

    std::string line;
    userData sample;
    while(cin)
    {
        std::getline(cin,line);

        if (!reader.get_sample(sample, line))
        {
            cout << "Wrong input data" << endl;
            continue;
        }

        int sample_class = cl.classify(sample);
        cl.print_close_samples(sample_class, sample);
    }

}