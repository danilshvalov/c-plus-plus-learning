#ifndef __THREADSAFE_LOOKUP_TABLE_H__
#define __THREADSAFE_LOOKUP_TABLE_H__

#include <future>
#include <mutex>
#include <list>
#include <shared_mutex>
#include <vector>
#include <memory>
#include <map>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class threadsafe_lookup_table {
private:
  using bucket_value = std::pair<Key, Value>;
  using bucket_data = std::list<bucket_value>;
  using bucket_iterator = typename bucket_data::iterator;
  struct bucket_type {
    bucket_data data;
    mutable std::shared_mutex mutex;

    bucket_iterator find_entry_for(const Key& key) const {
      return std::find_if(begin(data), end(data), [&](const bucket_value& item) {return item.first == key;});
    }
    Value value_for(const Key& key, const Value& default_value) const {
      std::shared_lock<std::shared_mutex> lock(mutex);
      const bucket_iterator found_entry = find_entry_for(key);
      return (found_entry == end(data)) ? default_value : found_entry->second;
    }
    void add_or_update_mapping(const Key& key, const Value& value) {
      std::unique_lock<std::shared_mutex> lock(mutex);
      bucket_iterator found_entry = find_entry_for(key);
      if (found_entry == end(data)) {
        data.push_back(bucket_value(key, value));
      } else {
        found_entry->second = value;
      }
    }
    void remove_mapping(const Key& key) {
      std::unique_lock<std::mutex> lock(mutex);
      bucket_iterator found_entry = find_entry_for(key);
      if (found_entry != end(data)) {
        data.erase(found_entry);
      }
    }
  };
  std::vector<std::unique_ptr<bucket_type>> buckets;
  Hash hasher;
  bucket_type& get_bucket(const Key& key) {
    const std::size_t bucket_index = hasher(key) % buckets.size();
    return *buckets[bucket_index];
  }
public:
  using key_type = Key;
  using mapped_type = Value;
  using hash_type = Hash;
  threadsafe_lookup_table(unsigned num_buckets = 19, const Hash& hasher_ = Hash())
    : buckets(num_buckets), hasher(hasher_) {
    for (unsigned i = 0; i < num_buckets; ++i) {
      buckets[i].reset(new bucket_type);
    }
  }
  threadsafe_lookup_table(const threadsafe_lookup_table& other) = delete;
  threadsafe_lookup_table& operator=(const threadsafe_lookup_table& other) = delete;

  Value value_for(const Key& key, const Value& default_value = Value()) const {
    return get_bucket(key).value_for(key, default_value);
  }
  void add_or_update_mapping(const Key& key, const Value& value) {
    get_bucket(key).add_or_update_mapping(key, value);
  }
  void remove_mapping(const Key& key) {
    get_bucket(key).remove_mapping(key);
  }
  std::map<Key, Value> get_map() const {
    std::vector<std::unique_lock<std::shared_mutex>> locks;
    for (unsigned i = 0; i < buckets.size(); ++i) {
      locks.push_back(
        std::unique_lock<std::shared_mutex>(buckets[i]->mutex));
    }
    std::map<Key, Value> res;
    for (unsigned i = 0;i < buckets.size();++i) {
      for (bucket_iterator it = buckets[i]->data.begin(); it != buckets[i]->data.end(); ++it) {
        res.insert(*it);
      }
    }
    return res;
  }
};

#endif // __THREADSAFE_LOOKUP_TABLE_H__