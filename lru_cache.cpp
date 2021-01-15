#include <iostream>
#include <list>
#include <unordered_map>

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
        auto find_result = key_list_iterator_map_.find(key);

        if(find_result != key_list_iterator_map_.end())
        {
            // find it, adjust element position in list
            key_value_list_.push_back(std::make_pair(key, find_result->second->second));
            key_value_list_.erase(find_result->second);
            auto last_ele_iterator = key_value_list_.end();
            find_result->second = --last_ele_iterator; // update the iterator in the map
            
            return find_result->second->second;
        }

        return NOT_FOUND;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        auto find_result = key_list_iterator_map_.find(key);

        // exist in map, update the value, change position
        if(find_result != key_list_iterator_map_.end())
        {
            // update value
            find_result->second->second = value;  

            // change position to the end of list
            key_value_list_.push_back(std::make_pair(key, value));
            key_value_list_.erase(find_result->second);

            // update the iterator in the map
            auto last_ele_iterator = key_value_list_.end();
            find_result->second = --last_ele_iterator; 
        }
        else  // not exist
        {
            // full, erase the oldest element
            if(key_value_list_.size() == capacity_)
            {
                // get the key of oldest value
                int oldest_key = key_value_list_.front().first;

                // erase the oldest ele in map
                auto find_result = key_list_iterator_map_.find(oldest_key);
                key_list_iterator_map_.erase(find_result);

                // erase the oldest ele in list
                key_value_list_.pop_front();
            }
            
            // insert key-value pair to the end of list
            key_value_list_.push_back(std::make_pair(key, value));
            
            // insert key and iterator to the map
            auto last_ele_iterator = key_value_list_.end();
            key_list_iterator_map_[key] = --last_ele_iterator; // update the iterator to the end of list
        }       
    }

private:
    int capacity_;
    std::list<std::pair<int, int>> key_value_list_;  // store the key-value pair, list order: oldest(front) <------> newest(end)
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> key_list_iterator_map_;  // store key and the position of value in list 
};

int main() {
    LRUCache lru_cache1(1);
    lru_cache1.set(2, 1);
    std::cout << lru_cache1.get(2) << std::endl;  // 1
    lru_cache1.set(3, 2);
    std::cout << lru_cache1.get(2) << std::endl;  // -1 not exist
    std::cout << lru_cache1.get(3) << std::endl;  // 2
    std::cout << std::endl;

    LRUCache lru_cache2(2);
    lru_cache2.set(2, 1);
    lru_cache2.set(1, 1);
    std::cout << lru_cache2.get(2) << std::endl;  // 1
    lru_cache2.set(4, 1);
    std::cout << lru_cache2.get(1) << std::endl;  // -1 not exist
    std::cout << lru_cache2.get(2) << std::endl;  // 1

    std::cout << "Hello, LRU Cache!" << std::endl;
    return EXIT_SUCCESS;
}