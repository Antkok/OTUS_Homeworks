/// @file
/// @brief Файл с реализацией основного потока приложения

#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include "bayan_finder.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "this help")
            ("target", po::value<std::vector<std::string>>(), "target dir")
            ("exclude", po::value<std::vector<std::string>>(), "exclude dir")
            ("name", po::value<std::vector<std::string>>(), "file name pattern")
            ("depth,d", po::value<std::size_t>()->default_value(0), "scan depth: 0 - only target dir")
            ("min-size", po::value<std::size_t>()->default_value(1), "minimal file size for scan in bytes")
            ("bulk-size", po::value<std::size_t>()->default_value(16), "compare bulk size in bytes")
            ("hash", po::value<std::string>()->default_value("crc"), "hash algorithm: crc, boost");

        po::positional_options_description pos;
        pos.add("target", -1);

        po::parsed_options parsed = po::command_line_parser(argc, argv). options(desc).positional(pos).run();

        po::variables_map vm;
        po::store(parsed, vm);

        if (!vm.count("target") || vm.count("help"))
        {
            std::cout << "Usage: " << argv[0] << " target dir..." << '\n' << desc << '\n';
            return 0;
        }

        auto getValue = [&vm](const char* name, auto& value){
                if (vm.count(name))
                {
                    value = vm[name].as<std::remove_reference_t<decltype(value)>>();
                }
            };

        BayanFinder::Options options;
        getValue("target", options.targets_);
        getValue("exclude", options.excludes_);
        getValue("name", options.patterns_);

        getValue("depth", options.depth_);
        getValue("min-size", options.minSize_);
        getValue("bulk-size", FileMeta::bulkSize_);

        std::string hash;
        getValue("hash", hash);
        try
        {
            options.setHash(hash);
        }
        catch (const std::invalid_argument& e)
        {
            std::string hash = e.what();
            auto msg = "the argument ('" + hash + "') for option '--hash' is invalid";
            throw std::invalid_argument(std::move(msg));
        }

        BayanFinder finder(options);
        std::vector<FileMetas> bayans;
        while (!(bayans = finder.findBayans()).empty())
        {
            for (auto& group : bayans)
            {
                for (auto& f : group)
                {
                    std::cout << fs::canonical(f.path_) << '\n';
                }
                std::cout << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
