#include <gtest/gtest.h>
#include <list>
#include <string>
#include <iostream>
#include "matrix.h"

TEST(GOOGLE_TEST1, test1)
{
    matrix<int, 5, 1> m;
    m[3] = 4;
    const int& a(m[7]);
    std::cout << a << " " << m[3] << " " << m[0] << std::endl;
    ASSERT_TRUE(m[3] == 4);
    ASSERT_TRUE(m[111] == 5);
    ASSERT_TRUE(m.size() == 1);
}

TEST(GOOGLE_TEST2, test2)
{
    matrix<int, 6, 2> m;
    m[1][2] = 11;
    m[1][3] = 12;
    m[2][2] = 13;
    ASSERT_TRUE(m.size() == 3);
    ASSERT_TRUE(m[1][2] == 11);
    ASSERT_TRUE(m[1][3] == 12);
    ASSERT_TRUE(m[2][2] == 13);
    ASSERT_TRUE(m[777][6] == 6);
    for (const auto i : m) {
        ASSERT_TRUE(std::get<0>(i) == 1 || std::get<0>(i) == 2);
        ASSERT_TRUE(std::get<1>(i) == 2 || std::get<1>(i) == 3);
    }
}

TEST(GOOGLE_TEST3, test3)
{
    matrix<int, -1> m; // бесконечная матрица int заполнена значениями -1
    ASSERT_TRUE(m.size() == 0); // все ячейки свободны
    auto a = m[0][0];
    ASSERT_TRUE(a == -1);
    ASSERT_TRUE(m.size() == 0);
    m[100][100] = 314;
    ASSERT_TRUE(m[100][100] == 314);
    ASSERT_TRUE(m.size() == 1);
    // выведется одна строка
    // 100100314
    std::stringstream ss;
    int i = 0;
    for(auto c : m) {
        i++;
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        ss << x << y << v << std::endl;
    }
    ASSERT_TRUE(i == 1);
    std::string res;
    ss >> res;
    ASSERT_TRUE(res == "100100314");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}