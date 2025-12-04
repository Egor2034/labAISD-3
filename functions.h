#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <vector>
#include "list.h"

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

template <typename T>
void swap(T& val1, T& val2) {
    T temp = val1;
    val1 = val2;
    val2 = temp;
}

template <typename T>
stats selection_sort(LinkedList<T>& list) {
    if (list.count() <= 1) { return { 0,0 }; }

    stats stat = { 0, 0 };
    size_t count = list.count();

    auto* current = list.head_;

    for (size_t i = 0; i < count - 1; i++) {
        auto* min_node = current;
        auto* new_current = current->next;

        for (size_t j = i + 1; j < count; j++) {
            stat.comparison_count++;
            if (new_current->data < min_node->data) {
                min_node = new_current;
            }
            new_current = new_current->next;
        }

        if (min_node != current) {
            swap(min_node->data, current->data);
            stat.copy_count += 3;
        }

        current = current->next;
    }

    return stat;
}

stats shell_sort(std::vector<int>& vect) {
    if (vect.size() <= 1) { return { 0, 0 }; }

    stats stat = { 0, 0 };

    // 6 5 1 7
    for (int step = vect.size() / 2; step > 0; step /= 2) {
        for (int i = step; i < vect.size(); i++) {
            int temp = vect[i];
            stat.copy_count++;
            int j = i;

            while (j >= step) {
                stat.comparison_count++;
                if (vect[j - step] > temp) {
                    vect[j] = vect[j - step];
                    stat.copy_count++;
                    j -= step;
                }
                else {
                    break;
                }
            }

            vect[j] = temp;
            stat.copy_count++;
        }
    }
    return stat;
}

void heapify(std::vector<int>& vect, size_t n, size_t i, stats& stat) {
    size_t largest = i;
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;

    if (l < n) {
        stat.comparison_count++;
        if (vect[l] > vect[largest]) {
            largest = l;
        }
    }

    if (r < n) {
        stat.comparison_count++;
        if (vect[r] > vect[largest]) {
            largest = r;
        }
    }

    if (largest != i) {
        swap(vect[i], vect[largest]);
        stat.copy_count += 3;
        heapify(vect, n, largest, stat);
    }
}

stats heap_sort(std::vector<int>& vect) {
    if (vect.size() <= 1) { return { 0, 0 }; }

    stats stat = { 0,0 };

    for (int i = vect.size() / 2 - 1; i >= 0; i--) {
        heapify(vect, vect.size(), i, stat);
    }

    for (int i = vect.size() - 1; i > 0; i--)
    {
        swap(vect[0], vect[i]);
        stat.copy_count += 3;
        heapify(vect, i, 0, stat);
    }

    return stat;
}

#endif