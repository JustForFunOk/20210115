// 现有两个 producer线程 A和 B负责生产数据
//（A线程生产的数据是结构体 A_struct，A_struct.a是随机产生的 1 到 100间的一个整数,
// B线程生产的数据是结构体 B_struct，B_struct.data是随机产生的 0 到 1之间 的 5个小数（精确到小数点后 2位））。
// 一个 consumer线程 C负责计算最新收取的 B_struct.data中数据的加和 sum_b，
// sum_b满足当最新收取的 A_struct.a数据为奇数时,sum_b取正，当最新收取的 A_struct.a数据为偶数时，sum_b取负。
// 如果连续来的数据都为 B_struct时，sum_b的正负由最近一次收取到的 A_struct.a的奇偶决定。
// 线程 C会实时维护一个累计 sum_b的加和 sum_b_all。
// 最后线程 D每隔 1秒钟打印一次当前 sum_b_all的值。
// 请设计程序，使得线程间通讯的延迟最小。
// A_struct和 B_struct定义如下：
// structA_struct{
//     int a;
// }
// structB_struct{
//     double data[5];
// }
// c++ 14

// g++ multi_thread.cpp -o multi_thread -std=c++14 -pthread
#include <queue>
#include <thread>
#include <random>
#include <chrono>
#include <iostream>
#include <mutex>
#include <condition_variable>

struct A_struct{
    int a;
} product_A;

struct B_struct{
    double data[5];
};
std::queue< B_struct > product_B_queue;

double sum_b_all = 0;

// mutex lock
std::mutex product_B_queue_mtx;
std::mutex mtx;

// condition_variable
std::condition_variable queue_has_product;

// generate ramdom number
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<int> distr_duration(100, 1000); // duration range: 100-1000 ms
std::uniform_int_distribution<int> distr_A(1, 100); // range: 1-100
std::uniform_int_distribution<int> distr_B(0, 100); // range: 0-100

/*
 * produce a random number(1-100) in random duration(1-100ms)
 */
void producer_A()
{
    while(1)
    {   
        // sleep for random milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(distr_duration(gen)));  

        // update random number
        product_A.a = distr_A(gen);
        // std::cout << product_A.a << std::endl;
    }
}

/*
 * produce 5 random numbers(0-1) in random duration(100-1000ms)
 */
void producer_B()
{
    while(1)
    {   
        // sleep for random milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(distr_duration(gen)));  
        
        // produce 5 random number
        B_struct product_B;
        for(int i = 0; i < 5; ++i)
        {
            product_B.data[i] = distr_B(gen) / 100.0; // range: 0-1, precision 0.01
        }

        // push random number to queue
        std::unique_lock<std::mutex> queue_lock(product_B_queue_mtx);
        product_B_queue.push(product_B);
        queue_lock.unlock();

        queue_has_product.notify_all();  // notify consumer
    }
}

void consumer_C()
{
    while(1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        queue_has_product.wait(lock);  // wait for new product
      
        std::unique_lock<std::mutex> queue_lock(product_B_queue_mtx);
        // get product_B
        auto product_B = product_B_queue.front();
        // pop product_B 
        product_B_queue.pop();
        queue_lock.unlock();
        
        // calculate sum_b
        double sumb = 0;
        for(int i = 0; i < 5; ++i)
        {
            sumb += product_B.data[i];  // cal sum
        }
        
        if(!(product_A.a % 2))
        {
            sumb *= -1;  // even
        }
        sum_b_all += sumb;       
    }
}

void consumer_D()
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // sleep for 1 second

        std::cout << sum_b_all << std::endl;
    }
}

int main()
{
    // spawn thread
    std::thread thread_A(producer_A);
    std::thread thread_B(producer_B);
    std::thread thread_C(consumer_C);
    std::thread thread_D(consumer_D);

    // wait for thread finish
    thread_A.join();
    thread_B.join();
    thread_C.join();
    thread_D.join();

    return 0;
}