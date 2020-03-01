//wordcount.cpp
//William Fisher
//Operating Systems
//Feb. 29, 2020

#include<iostream>
using std::cout;
using std::endl;
#include<vector>
using std::vector;
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include<chrono>
#include<future>
#include<algorithm>
using std::sort;
using std::lower_bound;
#include<map>
using std::map;
#include<iomanip>
#include<iterator>
using std::advance;
#include<thread>
using std::thread;

vector<string> intoVector(string fileName)
{
	string input;
	vector<string> words;

	ifstream file(fileName);
	if (!file)
	{
		cout << "Error" << endl;
		return words;
	}

	while (true)
	{
		file >> input;
		if (!file)
		{
			if (file.eof())
				break;
			else
				cout << "Unkown error" << endl;
		}
		else
		{
			words.push_back(input);
		}
	}

	return words;
}

void countOccurrences(vector<string>& allWords, vector<string>& searchWords, map<string, int>& wordCount, int numThreads,
						int begin, int end)
{
	for (int i = begin; i < end; ++i)
	{
		for (int ii = 0; ii < searchWords.size(); ++ii)
		{
			if (allWords[i] == searchWords[ii])
			{
				wordCount[allWords[i]]++;
			}
		}
	}
}
//TODO: IMPLEMENT THE CLOCK PROPERLY SO THAT WE CAN GRAPH THE DATA AND GET OTHER FILE TO COUNT NUMBER OF WORDS
int main()
{
	vector<string> allWords = intoVector("sampleFICT.txt");
	
	vector<string> searchWords = { "applesauce", "happy", "and", "the", "truth", "help", "drugs", "computer", "end", "life",
									"death", "good", "bad", "ugly", "cash", "bagel", "crab", "math", "caramel", "chocolate",
									"peanut", "butter", "tree", "house", "expedition", "katana", "job", "apocalypse", "vacuum", "joker",
									"manticore", "salutations", "tape", "resident", "evil", "fire", "emblem", "Jack", "garbage", "military",
									"economy", "metal", "do", "not", "claw", "couch", "thesis", "paper", "ore", "oar" };

	//initialize the map
	map<string, int> wordCount;
	for (auto word : searchWords)
	{
		wordCount[word] = 0;
	}

	int numThreads = 8;
	vector<thread> threads;
	int begin = 0;
	int end = (allWords.size() / numThreads);

	//auto beginClock = std::chrono::steady_clock::now(); //start the timer
	for (int i = 0; i < numThreads; ++i)
	{
		thread t(countOccurrences, std::ref(allWords), std::ref(searchWords), std::ref(wordCount), numThreads, begin, end);
		threads.push_back(std::move(t));
		begin = end;
		end += (allWords.size() / numThreads);
	}
	//auto endClock = std::chrono::steady_clock::now(); //end the timer
	//auto elapsedTime = endClock - beginClock;

	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	for (auto word : searchWords)
	{
		cout << word << " : " << wordCount[word] << " times" << endl;
	}

	cout << "This program was run using " << numThreads << " threads." << endl;
	//cout << "It took " << std::chrono::duration<double>(elapsedTime).count() << " for the threads to do their thing." << endl;
}

