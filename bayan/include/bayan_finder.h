#pragma once

/// @file
/// @brief Файл с объявлением поисковика файлов-дубликатов

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include "filemeta.h"
#include "hash.h"

/// @brief Класс поисковика файлов-дубликатов
class BayanFinder
{
public:
    /// @brief Тип алгоритма хэширования
    enum class HashType
    {
        CRC,
        BOOST
    };

    /// @brief Класс параметров поиска файлов-дубликатов
    struct Options
    {
        /// @brief Установка типа хэш-функции
        /// @param hash строковое представление типа хэш-функции
        void setHash(const std::string& hash)
        {
            if (hash == "crc")
            {
                hash_ = HashType::CRC;
            }
            else if (hash == "boost")
            {
                hash_ = HashType::BOOST;
            }
            else
            {
                throw std::invalid_argument(hash);
            }
        }

        std::vector<std::string> targets_;
        std::vector<std::string> excludes_;
        std::vector<std::string> patterns_;
        std::size_t depth_ = 0;
        std::size_t minSize_ = 0;
        HashType hash_ = HashType::CRC;
    };

    /// @brief Конструктор
    /// @param options параметры поиска
    BayanFinder(const Options& options);

    /// @brief Получить параметры поиска
    /// @return параметры поиска
    Options options() const { return options_; }

    /// @brief Установить параметры поиска
    /// @return параметры поиска
    void setOptions(const Options& options);

    /// @brief Найти файлы-дубликаты
    /// @detail Возвращает первые найденные группы. Повторять вызов пока не вернется пустой набор.
    /// @return набор групп файлов-дубликатов
    std::vector<FileMetas> findBayans();

    /// @brief Сбросить состояние поисковика
    void reset() { files_.clear(); }

private:
    /// @brief Поиск файлов по параметрам
    /// @param targets список директорий для поиска
    /// @param excludes список директорий исключаемых из сканирования
    /// @param patterns маски имен файлов
    /// @param minSize минимальный размер файла
    /// @param depth глубина сканирования
    /// @return список файлов
    FileMetas scanDirs(const std::vector<std::string>& targets, const std::vector<std::string>& excludes,
            const std::vector<std::string>& patterns, std::size_t minSize, int depth) const;

    /// @brief Добавить файл, если его размер не меньше минимального
    /// @param file файл
    /// @param minSize минимальный размер
    /// @param files контейнер файлов
    void addBySize(fs::path file, std::size_t minSize, std::unordered_map<std::string, std::size_t>& files) const;

    /// @brief Получение набора файлов с одинаковым размером
    /// @detail После вызова из files исключается набор найденных файлов. Повторять вызов пока не вернется пустой набор.
    /// @param files список файлов
    /// @return набор файлов с одинаковым размером
    FileMetas getDuplSizeFiles(FileMetas& files) const;

    /// @brief Найти одинаковые файлы по содержимому
    /// @param files список файлов
    /// @return группы файлов с одинаковым содержимым
    std::vector<FileMetas> getDuplFileGroups(FileMetas& files) const;

    /// @brief Сравнение содержимого двух файлов
    /// @param file1 файл 1
    /// @param file2 файл 2
    /// @return true, если файлы одинаковые, иначе false
    bool compare(FileMeta& file1, FileMeta& file2) const;

    Options options_; ///< параметры поиска
    std::unique_ptr<Hash> hash_; ///< алгоритм хэширования
    FileMetas files_; ///< файлы
};
