#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include "selection_sort_template.h"

template<typename T, std::size_t N, typename Compare = std::less<>>
class Array
{
public:
    Array() : comp(Compare()), is_sorted(false) {}
    Array(Compare c) : comp(c), is_sorted(false) {}

    template<typename... Args>
    void emplace(std::size_t idx, Args&&... args)
    {
        data[idx] = T(std::forward<Args>(args)...);
        is_sorted = false;
    }

    void print()
    {
        if (!is_sorted)
        {
            selection_sort(data.begin(), data.end(), comp);
            is_sorted = true;
        }
        for (std::size_t i = 0; i < N; i++)
        {
            std::cout << data[i];
            if (i < N - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }

private:
    std::array<T, N> data;
    bool is_sorted;
    Compare comp;
};

#endif
