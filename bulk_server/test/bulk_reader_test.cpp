/// @file
/// @brief Файл с тестами класса читателя блока команд

#include <gtest/gtest.h>
#include <sstream>
#include "bulk.h"
#include "bulk_reader.h"

TEST(BulkReaderTest, Test1)
{
    std::stringstream is("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n");
    BulkReader reader(is, 3);

    Bulk bulk;
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 3);
    EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);

    bulk.clear();
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 2);
    EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);
}

TEST(BulkReaderTest, Test2)
{
    auto input = "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\ncmd6\ncmd7\n}\n";
    {
        std::stringstream is(input);
        BulkReader reader(is, 5);

        Bulk bulk;
        reader.read(bulk);
        EXPECT_EQ(bulk.size(), 3);
        EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);

        bulk.clear();
        reader.read(bulk);
        EXPECT_EQ(bulk.size(), 4);
        EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);
    }
    {
        std::stringstream is(input);
        BulkReader reader(is, 3);

        Bulk bulk;
        reader.read(bulk);
        EXPECT_EQ(bulk.size(), 3);
        EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);

        bulk.clear();
        reader.read(bulk);
        EXPECT_EQ(bulk.size(), 0);
        EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);

    }
}

TEST(BulkReaderTest, Test3)
{
    std::stringstream is("{\ncmd1\ncmd2\n{\ncmd3\ncmd4\n}\ncmd5\ncmd6\n}\n");
    BulkReader reader(is, 7);

    Bulk bulk;
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 0);
    EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);

    bulk.clear();
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 6);
    EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);
}

TEST(BulkReaderTest, Test4)
{
    std::stringstream is("cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\ncmd6\ncmd7\n");
    BulkReader reader(is, 5);

    Bulk bulk;
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 3);
    EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);

    bulk.clear();
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 4);
    EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);
}

TEST(BulkReaderTest, Test5)
{
    std::stringstream is("cmd1\n{\n}\ncmd2");
    BulkReader reader(is, 3);

    Bulk bulk;
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 1);
    EXPECT_EQ(reader.state(), BulkReader::OPENED_BULK);

    bulk.clear();
    reader.read(bulk);
    EXPECT_EQ(bulk.size(), 0);
    EXPECT_EQ(reader.state(), BulkReader::CLOSED_BULK);
}
