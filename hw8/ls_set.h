#ifndef LS_SET_H
#define LS_SET_H

#include <vector>
#include <algorithm>

template <typename T>
struct remove_pointers { using type = T; };

template <typename T>
struct remove_pointers<T*> { using type = typename remove_pointers<T>::type; };

template <typename T>
struct remove_pointers<T* const> { using type = typename remove_pointers<T>::type; };

template <typename T>
T& dereference(T& x) { return x; }

template <typename T>
auto& dereference(T* p) { return dereference(*p); }

template <typename T>
class ls_set {
    std::vector<T> data;
public:
    void insert(const T& val) {
        if (!find(val)) data.push_back(val);
    }
    void erase(const T& val) {
        data.erase(std::remove(data.begin(), data.end(), val), data.end());
    }
    bool find(const T& val) const {
        return std::find(data.begin(), data.end(), val) != data.end();
    }
    size_t size() const { return data.size(); }
};

template <typename T>
class ls_set<T*> {
    using base = typename remove_pointers<T*>::type;
    std::vector<base> data;
public:
    void insert(T* val) {
        base& deref = dereference(val);
        if (!find(deref)) data.push_back(deref);
    }
    void erase(const base& val) {
        data.erase(std::remove(data.begin(), data.end(), val), data.end());
    }
    bool find(const base& val) const {
        return std::find(data.begin(), data.end(), val) != data.end();
    }
    size_t size() const { return data.size(); }
};

#endif