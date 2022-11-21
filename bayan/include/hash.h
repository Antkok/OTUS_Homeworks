#pragma once

/// @file
/// @brief Файл с объявлением алгоритмов хэш-функций

#include "filemeta.h"

/// @brief Интерфейс алгоритма хэш-функции
class Hash
{
public:
    /// @brief Рассчитать хэш на следующий блок файла
    /// @param file файл
    virtual void hash(FileMeta& file) = 0;
};

/// @brief Класс хэш-функции CRC
class CrcHash : public Hash
{
public:
    /// @brief Рассчитать хэш на следующий блок файла
    /// @param file файл
    void hash(FileMeta& file) override;
};

/// @brief Класс хэш-функции Boost
class BoostHash : public Hash
{
public:
    /// @brief Рассчитать хэш на следующий блок файла
    /// @param file файл
    void hash(FileMeta& file) override;
};
