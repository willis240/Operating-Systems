//memory_misses.cpp
//William Fisher
//Operating Systems
//Feb. 29, 2020

#include<iostream>
using std::cout;
using std::endl;
#include<vector>
using std::vector;
#include<chrono>

int main()
{
	vector<int> vec(100);

	auto start = std::chrono::high_resolution_clock::now();
	int num = 0;
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

	for (int i = 0; i < vec.size(); ++i)
	{
		start = std::chrono::high_resolution_clock::now();
		num = vec[i];
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		cout << "num: " << num << "          time to access: " << duration.count() << " nanoseconds" << endl;
	}
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	//int average = (duration.count() / vec.size());
	
}