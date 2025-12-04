#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "list.h"
#include "functions.h"

const int TESTS_COUNT = 100;

class VectorMaker {
private:
	std::random_device seed;
	std::mt19937 rand_num = std::mt19937(seed());
public:
	std::vector<int> make_random(size_t size) {
		std::vector<int> res;
		res.reserve(size);
		for (size_t i = 0; i < size; i++)
			res.push_back(rand_num());
		return res;
	}

	std::vector<int> make_sorted(size_t size) {
		std::vector<int> res;
		res.reserve(size);
		for (size_t i = 0; i < size; i++) {
			res.push_back(i);
		}
		return res;
	}

	std::vector<int> make_reverse_sorted(size_t size) {
		std::vector<int> res;
		res.reserve(size);
		for (size_t i = 0; i < size; i++) {
			res.push_back(size - i);
		}
		return res;
	}
};

template <typename T>
LinkedList<T> vector_to_list(const std::vector<T>& vect) {
	LinkedList<T> list;

	for (const auto& elem : vect) {
		list.push_tail(elem);
	}

	return list;
}

void print_results(const std::vector<stats>& results) {
	double comprasion_count = 0;
	double copy_count = 0;

	for (const auto& el : results) {
		comprasion_count += el.comparison_count;
		copy_count += el.copy_count;
	}

	comprasion_count /= results.size();
	copy_count /= results.size();

	std::cout << "\tСравнения: " << comprasion_count << "\t";
	std::cout << "Копирования: " << copy_count << "\n";
}

void task_1(size_t size) {
	std::vector<stats> selection_results;
	std::vector<stats> shell_results;
	std::vector<stats> heap_results;

	VectorMaker maker;
	LinkedList<int> list;
	std::vector<int> temp;

	for (int i = 0; i < TESTS_COUNT; i++) {
		list = vector_to_list(maker.make_random(size));
		selection_results.push_back(selection_sort(list));

		temp = maker.make_random(size);
		shell_results.push_back(shell_sort(temp));

		temp = maker.make_random(size);
		heap_results.push_back(heap_sort(temp));
	}

	std::cout << "\tСортировака выбором: ";
	print_results(selection_results);
	std::cout << "\tСортировка Шелла: ";
	print_results(shell_results);
	std::cout << "\tПирамидальная сортировка: ";
	print_results(heap_results);
}

void task_2(size_t size) {
	VectorMaker maker;
	std::vector<int> temp;

	LinkedList<int> list = vector_to_list(maker.make_sorted(size));
	std::cout << "\tСортировака выбором: ";
	print_results({ selection_sort(list) });

	std::cout << "\tСортировка Шелла: ";
	temp = maker.make_sorted(size);
	print_results({ shell_sort(temp) });

	std::cout << "\tПирамидальная сортировка: ";
	temp = maker.make_sorted(size);
	print_results({ heap_sort(temp) });
}

void task_3(size_t size) {
	VectorMaker maker;
	std::vector<int> temp;

	LinkedList<int> list = vector_to_list(maker.make_reverse_sorted(size));
	std::cout << "\tСортировака выбором: ";
	print_results({ selection_sort(list) });

	std::cout << "\tСортировка Шелла: ";
	temp = maker.make_reverse_sorted(size);
	print_results({ shell_sort(temp) });

	std::cout << "\tПирамидальная сортировка: ";
	temp = maker.make_reverse_sorted(size);
	print_results({ heap_sort(temp) });
}

int main()
{
	std::setlocale(LC_ALL, "");

	std::vector<int> sizes{ 1000, 2000, 3000, 4000 };

	for (auto el : sizes) {
		std::cout << "Случайные числа(" << el << "):\n";;
		task_1(el);
		std::cout << "\nОтсортированный массив(" << el << "):\n";;
		task_2(el);
		std::cout << "\nОбратно отсортированный массив(" << el << "):\n";
		task_3(el);
		std::cout << "\n\n";
	}

	return 0;
}
