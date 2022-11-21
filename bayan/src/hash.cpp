/// @file
/// @brief Файл с реализацией алгоритмов хэш-функций

#include "hash.h"
#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>
#include <fstream>

void CrcHash::hash(FileMeta& file)
{
    std::vector<char> buf(FileMeta::bulkSize_, 0);

    std::ifstream f(file.path_.native(), std::ios::in | std::ios::binary);
    f.seekg(file.bulkHashes_.size() * FileMeta::bulkSize_);
    f.read(buf.data(), buf.size());

    boost::crc_32_type seed;
    seed.process_bytes(buf.data(), buf.size());

    file.bulkHashes_.push_back(seed.checksum());
}

void BoostHash::hash(FileMeta& file)
{
    std::vector<char> buf(FileMeta::bulkSize_, 0);

    std::ifstream f(file.path_.native(), std::ios::in | std::ios::binary);
    f.seekg(file.bulkHashes_.size() * FileMeta::bulkSize_);
    f.read(buf.data(), buf.size());

    std::size_t seed = 0;
    for (std::size_t i = 0; i < buf.size(); ++i)
    {
        boost::hash_combine(seed, buf[i]);
    }
    file.bulkHashes_.push_back(seed);
}
