#pragma once

/// @file
/// @brief Файл с объявлением мета-структуры файла

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

/// @brief Класс мета-структуры файла
struct FileMeta
{
    /// @brief Конструктор
    /// @param filePath путь к файлу
    FileMeta(const fs::path& filePath) : path_(filePath) { }

    FileMeta(const fs::path& filePath, std::size_t size) : path_(filePath), size_(size) { }

    fs::path path_;
    std::size_t size_;
    std::vector<std::size_t> bulkHashes_;

    static std::size_t bulkSize_;
};

using FileMetas = std::vector<FileMeta>;
