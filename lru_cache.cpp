#include <iostream>
#include <list>

class LRUCache {
public:
    static const int NOT_FOUND = -1;
    
    /*
    * @param capacity: An integer
    */
    LRUCache(int capacity){
        capacity_ = capacity;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        // find element in map
        auto find_result = key_val_map_.find(key);

        if(find_result != key_val_map_.end())
        {
            // find it, adjust element position in list
            // old element in the front, new element in the end
            for(auto it = key_list_.begin(); it != key_list_.end(); ++it)
            {
                if(*it == key)
                {
                    key_list_.erase(it);
                    key_list_.push_back(key);
                }
            }

            return find_result->second;
        }

        return NOT_FOUND;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
    }

private:
    int capacity_;
    list<int> key_list_;
    unordered_map<int, int> key_val_map_;
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