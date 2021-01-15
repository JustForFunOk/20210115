#include <iostream>

class LRUCache {
public:
    static const int NOT_FOUND = -1;
    
    /*
    * @param capacity: An integer
    */
    LRUCache(int capacity){
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
    }
};

int main() {
    LRUCache lru_cache1(1);
    lru_cache1.set(2, 1);
    std::cout << lru_cache1.get(2) << std::endl;
    lru_cache1.set(3, 2);
    std::cout << lru_cache1.get(2) << std::endl;
    std::cout << lru_cache1.get(3) << std::endl;
    std::cout << std::endl;

    LRUCache lru_cache2(2);
    lru_cache2.set(2, 1);
    lru_cache2.set(1, 1);
    std::cout << lru_cache2.get(2) << std::endl;
    lru_cache2.set(4, 1);
    std::cout << lru_cache2.get(1) << std::endl;
    std::cout << lru_cache2.get(2) << std::endl;

    std::cout << "Hello, LRU Cache!" << std::endl;
    return EXIT_SUCCESS;
}