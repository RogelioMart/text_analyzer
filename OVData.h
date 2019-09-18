#include  <iostream>
#include <string>
using namespace std;
//#pragma once
class wordNcount
{
public:
	wordNcount();//constructor
	~wordNcount();//destructor
	string word;
	int count;

	wordNcount& operator= (string); //declaration that overloads the = operator for the class wordNcount
	bool operator< (wordNcount word);//declaration that overloads the < operator for the class wordNcount
	bool operator> (wordNcount word);//declaration that overloads the > operator for the class wordNcount
	bool operator== (wordNcount word);//declaration that overloads the == operator for the class wordNcount
	bool operator!= (wordNcount word);//declaration that overloads the != operator for the class wordNcount
	friend std::ostream& operator<< (std::ostream &out, const wordNcount &word); //declaration that overloads cout for the class wordNcount
	friend std::istream& operator>> (std::istream &in, wordNcount &word);//declaration that overloads cin for the class wordNcount
	string getWord();//gets the word variable from the class wordNcount
	int getCount();//initilization of getCount


};

wordNcount::wordNcount()
{}

wordNcount::~wordNcount()
{}

wordNcount& wordNcount::operator= (string term)
{
	//overloads the = operator for the class wordNcount

	word = term;
	count = 1;

	return(*this);
}

bool wordNcount::operator< (wordNcount word)
{
	//overloads the < operator for the class wordNcount

	if (this->word < word.word)
	{
		return(true);
	}

	return(false);
}

bool wordNcount::operator> (wordNcount word)
{
	//overloads the > operator for the class wordNcount

	if (this->word > word.word)
	{
		return(true);
	}

	return(false);
}

bool wordNcount::operator== (wordNcount word)
{

	//overloads the == operator for the class wordNcount

	if (this->word == word.word)
	{
		return(true);
	}

	return(false);
}

bool wordNcount::operator!= (wordNcount word)
{

	//overloads the != operator for the class wordNcount

	if (this->word != word.word)
	{
		return(true);
	}

	return(false);
}

std::ostream& operator<< (std::ostream &out, const wordNcount &word)
{
	//overloads cout for the class wordNcount

	out << word.word;
	return(out);
}

std::istream& operator>> (std::istream &in, wordNcount &word)
{

	//overloads cin for the class wordNcount

	in >> word.word;
	word.count = 1;
	return(in);

}

string wordNcount::getWord()
{
	//gets the word variable from the class wordNcount

	return(word);
}

int wordNcount::getCount()
{
	//gets the count variable from the class wordNcount

	return(count);
}