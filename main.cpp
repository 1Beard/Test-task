#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

//The test task result should be located at any convenient Git repository

//Create a class "yourTestClass", which is inherited from interface class "testBase" presented below.
//Implement functions described in the interface class.


class testBase
{
public:
	//Function must revert the sequence of words. ("word1 word2 word3" becomes "word3 word2 word1")
	virtual void revertWords(char* arr) = 0;

	//Function must revert words using revertWords method and return the longest word.
	virtual std::string processWords(std::string& input) = 0;

	//Function must generate random length(up to 20) array of random signed integer numbers.
	//Function must print the generated sequence in console.
	virtual void signedIntGenerator(signed int* arr) = 0;

	//Function must use signedIntGenerator() and return minimum value.
	virtual signed int signedMin(signed int* arr) = 0;

	virtual ~testBase() = 0;

};
testBase::~testBase(){}

class yourTestClass: public testBase
{
    int mSize = 7;

    static inline bool space(char c)
    {
        return isspace(c);
    }

    static inline bool notspace(char c)
    {
        return !isspace(c);
    }

    vector<string> SplitWords(string input)
    {
        vector<string> splitWords;
        string::iterator i = input.begin();
        string::iterator j = input.begin();
        while(i!=input.end())
        {
            i = find_if(i, input.end(), notspace);
            j= find_if(i, input.end(), space);
            if(i!=input.end())
            {
                splitWords.push_back(string(i, j));
                i = j;
            }
        }
        return splitWords;
    }

public:

    ~yourTestClass(){}

    void signedIntGenerator(signed int *arr)
    {
        srand(time(0));
        for(int i = 0; i < mSize; i++)
        {
            arr[i] = rand()%200;
            cout << arr[i] << endl;
        }
    }

    signed int signedMin(signed int* arr)
    {
        arr = new int[mSize];
        signedIntGenerator(arr);
        int minInt = arr[0];
        for(int i = 0; i < mSize; i++)
        {
            if(arr[i] < minInt) minInt = arr[i];
        }
        return minInt;
    }

    void revertWords(char* arr)
    {
        vector<string> spWords;
        spWords = SplitWords(string(arr));
        string temp = "";
        for(int i = spWords.size()-1; i >=0; i--)
        {
            temp.append(spWords[i]);
            if (i != 0)temp.append(" ");
        }
        strcpy(arr,temp.c_str());
    }

    std::string processWords(std::string& input)
    {
        char* sWords = nullptr;
        sWords = const_cast<char*>(input.c_str());
        revertWords(sWords);
        input = string(sWords);
        vector<string> spWords;
        spWords = SplitWords(input);
        unsigned int num = 0, maxSize = 0;
        for (unsigned int v = 0;  v < spWords.size(); v++)
        {
            if(spWords[v].size() > maxSize)
            {
                maxSize = spWords[v].size();
                num = v;
            }
        }
        return spWords[num];
    }
};


int main() //DO NOT MODIFY THIS BLOCK
{
	yourTestClass myTest;
	signed int* arr = nullptr;

	std::cout << "Test started" << std::endl;
	std::cout << "Please input a text with several words" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << "Input text: " << input << std::endl;
	std::cout << "Longest word: " << myTest.processWords(input) << std::endl;
	std::cout << "Reverted text: " << input << std::endl;
	std::cout << "Minimal is : " << myTest.signedMin(arr) << std::endl;
	std::cout << std::endl << "Test ended";
	return 0;
}
