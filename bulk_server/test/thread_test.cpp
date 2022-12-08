/// @file
/// @brief Файл с тестами класса потока исполнения

#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include "cp_queue.h"
#include "thread.h"

TEST(ThreadTest, Test1)
{
    Thread t("Test1", std::function<void()>());
    t.waitStop();
    EXPECT_THROW(t.start(), std::bad_function_call);
}

TEST(ThreadTest, Test2)
{
    std::atomic_bool stop{false};
    auto f = [&stop]()
        {
            while (!stop.load())
            {
                std::this_thread::sleep_for(10ms);
            }
        };
    Thread t("Test2");
    t.start(f);
    std::this_thread::sleep_for(5ms);

    t.stop([&stop]{ stop.store(true); });
    t.start();
}

TEST(ThreadTest, Test3)
{
    ConsumerProducerQueue<int> q;
    int j = 0;

    auto f = [&q, &j]()
    {
        int i = 0;
        while (q.waitPop(i))
        {
            EXPECT_EQ(i, j);
            j++;
        }
    };

    Thread t("Test3", f);
    t.start();

    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(10ms);
        q.waitPush(i);
    }

    t.stop([&q]{ q.disable(); }, true);
    ASSERT_EQ(j, 10);
}
