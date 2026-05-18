#ifndef DO_FOR_EACH_TEMPLATE_H
#define DO_FOR_EACH_TEMPLATE_H

#include <iostream>

template<typename Functor>
void do_for_each(Functor f)
{
}

template<typename Functor, typename First, typename... Rest>
void do_for_each(Functor f, First& first, Rest&... rest)
{
    f(first);
    do_for_each(f, rest...);
}

void print()
{
    std::cout << std::endl;
}

template<typename First, typename... Rest>
void print(First first, Rest... rest)
{
    std::cout << first;
    if (sizeof...(rest) > 0)
        std::cout << " ";
    print(rest...);
}

#endif
