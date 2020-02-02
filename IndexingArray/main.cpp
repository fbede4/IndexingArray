#include "IndexingArray.h"

int main()
{
	try {
		IndexingArray<int> inAr = { 3, 7, 10 };
		inAr.push_back(2);
		std::cout << "Actual array: " << std::endl;
		inAr.printSort(0);
		std::cout << "===============" << std::endl;
		inAr.addNewSort(std::less<int>{}, 1);
		inAr.push_back(1);
		inAr.addNewSort([](int a, int b) {return a > b; }, 2);
		std::cout << "Increasing sort (sort 1), THEN value '3' added: " << std::endl;
		inAr.printSort(1);
		std::cout << "===============" << std::endl;
		inAr.push_back(5);
		std::cout << "Decreasing sort (sort 2), THEN value '5' added: " << std::endl;
		inAr.printSort(2);
		std::cout << "===============" << std::endl;
		inAr.pop_back();
		std::cout << "pop_back, sort 2: " << std::endl;
		inAr.printSort(2);
		std::cout << "===============" << std::endl;
		inAr.setCurrentSortType(1);
		std::cout << "sortType = 1 (inc.) arr[1] = " << std::endl;
		std::cout << inAr[1] << std::endl;
		std::cout << "===============" << std::endl;
		inAr.deleteSort(1);
		std::cout << "deleteSort 1; arr[1] = " << std::endl;
		std::cout << inAr[1] << "  => current sort automatically set to 0" << std::endl;
		std::cout << "===============" << std::endl;

		// this would throw error
		/*std::cout << "set current sort 1;" << std::endl;
		inAr.setCurrentSortType(1);
		inAr.printSort(1);
		std::cout << "===============" << std::endl;*/
	}
	catch (std::exception & e) {
		std::cout << "Error ocured: " << e.what() << std::endl;
	}
	return 0;
}
