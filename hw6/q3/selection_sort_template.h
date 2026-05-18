#ifndef SELECTION_SORT_TEMPLATE_H
#define SELECTION_SORT_TEMPLATE_H

#include <functional>

template<typename Iterator, typename Compare = std::less<>>
void selection_sort(Iterator first, Iterator last, Compare comp = Compare())
{
    for (Iterator i = first; i != last; i++)
    {
        Iterator min_it = i;
        Iterator j = i;
        j++;
        for (; j != last; j++)
        {
            if (comp(*j, *min_it))
                min_it = j;
        }
        if (min_it != i)
        {
            auto tmp = *i;
            *i = *min_it;
            *min_it = tmp;
        }
    }
}

#endif
