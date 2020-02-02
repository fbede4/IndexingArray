#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <initializer_list>

template<typename T>
class IndexingArray {
public:
	IndexingArray();
	IndexingArray(std::initializer_list<T> list);
	void push_back(const T& data);
	void pop_back();
	size_t size() noexcept;
	void addNewSort(std::function<bool(T, T)> func, size_t index);
	void sort(std::function<bool(T, T)> func);
	void deleteSort(size_t index);
	void setCurrentSortType(size_t index);
	void printSort(size_t index);
	T& operator[](size_t index);
private:
	std::vector<T> dataArray;
	std::map<size_t, std::vector<size_t>> indexArrays;
	std::map<size_t, std::function<bool(T, T)>> sortingFunctions;
	size_t currentSortType = 0;
};

template<typename T>
IndexingArray<T>::IndexingArray() {
	indexArrays[0] = std::vector<size_t>();
}

template <typename T>
IndexingArray<T>::IndexingArray(std::initializer_list<T> list) {
	dataArray = std::vector<T>(list.begin(), list.end());
	indexArrays[0] = std::vector<size_t>(dataArray.size());
	std::iota(indexArrays[0].begin(), indexArrays[0].end(), 0);
}

template<typename T>
void IndexingArray<T>::deleteSort(size_t index) {
	if (index == 0) {
		throw std::out_of_range("Physical sequence can not be deleted!");
	}
	auto iter = indexArrays.find(index);
	if (iter == indexArrays.end()) {
		throw std::out_of_range("a sort with given index does not exist!");
	}
	// if current is deleted set to physical sequence
	if (index == currentSortType) {
		currentSortType = 0;
	}
	indexArrays.erase(iter);
}

template<typename T>
void IndexingArray<T>::addNewSort(std::function<bool(T, T)> func, size_t index) {
	if (index == 0) {
		throw std::out_of_range("Physical sequence can not be overwritten!");
	}
	// creating new, not overwriting
	if (indexArrays.find(index) == indexArrays.end()) {
		indexArrays[index] = std::vector<size_t>(dataArray.size());
		std::iota(indexArrays[index].begin(), indexArrays[index].end(), 0);
	}
	sortingFunctions[index] = func;
	std::sort(indexArrays[index].begin(), indexArrays[index].end(),
		[&](size_t i1, size_t i2) {return func(dataArray[i1], dataArray[i2]); });
}

template<typename T>
void IndexingArray<T>::push_back(const T& data) {
	dataArray.push_back(data);
	for (auto &i : indexArrays) {
		i.second.push_back(dataArray.size() - 1);
		if (i.first != 0) {
			// insertion sort
			int j = dataArray.size() - 2;
			while (j >= 0 && sortingFunctions[i.first](dataArray[dataArray.size() - 1], dataArray[i.second[j]]))
			{
				i.second[j + 1] = i.second[j];
				--j;
			}
			i.second[j + 1] = dataArray.size() - 1;
		}
	}
}

template<typename T>
void IndexingArray<T>::pop_back() {
	if (dataArray.size() < 1) {
		throw std::out_of_range("empty data array!");
	}
	dataArray.pop_back();
	indexArrays[0].pop_back();
	for (auto &i : indexArrays) {
		if (i.first != 0) {
			i.second.erase(std::remove(i.second.begin(), i.second.end(), dataArray.size()), i.second.end());
		}
	}
}

template<typename T>
void IndexingArray<T>::printSort(size_t index) {
	if (indexArrays.find(index) == indexArrays.end()) {
		throw std::out_of_range("a sort with given index does not exist!");
	}
	for (auto i : indexArrays[index]) {
		std::cout << dataArray[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void IndexingArray<T>::setCurrentSortType(size_t index) {
	if (indexArrays.find(index) == indexArrays.end()) {
		throw std::out_of_range("a sort with given index does not exist!");
	}
	currentSortType = index;
}

template<typename T>
void IndexingArray<T>::sort(std::function<bool(T, T)> func) {
	sortingFunctions[currentSortType] = func;
	std::sort(indexArrays[currentSortType].begin(), indexArrays[currentSortType].end(),
		[&](size_t i1, size_t i2) {return func(dataArray[i1], dataArray[i2]); });
}

template<typename T>
T& IndexingArray<T>::operator[](size_t index) {
	if (index > dataArray.size() - 1) {
		throw std::out_of_range("index out of range!");
	}
	return dataArray[indexArrays[currentSortType][index]];
}

template<typename T>
size_t IndexingArray<T>::size() noexcept {
	return dataArray.size();
}