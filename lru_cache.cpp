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
        auto find_result = key_val_map_.find(key);

        if(find_result != key_val_map_.end())
        {
            // find it, adjust element position in list
            for(auto it = key_list_.begin(); it != key_list_.end(); ++it)
            {
                if(*it == key)
                {
                    // change the key position to the end of list
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
        auto find_result = key_val_map_.find(key);

        // exist in map, update the value, change position
        if(find_result != key_val_map_.end())
        {
            find_result->second = value;  // update value

            for(auto it = key_list_.begin(); it != key_list_.end(); ++it)
            {
                if(*it == key)
                {
                    key_list_.erase(it);
                    key_list_.push_back(key);
                }
            }
        }
        else  // donot exist
        {
            // full
            if(key_val_map_.size() == capacity_)
            {
                // find oldest_key in map and erase
                int oldest_key = key_list_.front();
                auto find_result = key_val_map_.find(oldest_key);
                key_val_map_.erase(find_result);

                // erase the oldest ele in list
                key_list_.pop_front();
            }
            
            // insert ele to map and the end of list
            key_val_map_[key] = value;
            key_list_.push_back(key);
        }       
    }

private:
    int capacity_;
    std::list<int> key_list_;  // store the order, list: oldest(front) <------> newest(end)
    std::unordered_map<int, int> key_val_map_;  // store key and value
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