#include <iomanip>		//Used for formatting output with setw()
#include "bstFunc.h"	//to be able to use the binary tree
#include "OVData.h"		//to use the wordNcount class and their overloads

struct queue//struct for the queue
{

	struct queue* next;

	string qWord;

};

//-------------------dispInOrder---------------------------
//---------------------------------------------------------
void dispInOrder(BSTNode <wordNcount>* current)
{
	if (current != NULL)
	{
		dispInOrder(current->leftPtr);
		cout << setw(20) << left << current->data.getWord() << setw(5) << right << current->data.getCount() << "\n";
		dispInOrder(current->rightPtr);
	}
}

//--------------------menu function------------------------
//---------------------------------------------------------
void menu()
{//menu begins here

	/*Displays options for the user*/

	cout << "\nChoose option:\n";
	cout << "1 - Find the Frequency of a word\n";
	cout << "2 - Output frequency analysis into a file.\n";
	cout << "0 - Exit from program\n";

}//menu ends here

//---------------------getSelect---------------------------
//---------------------------------------------------------
char getSelect()
{//getSelect begins here

	/*gets input from the user*/

	char input;

	cin >> input;

	cout << "\n";//used for formatting

	return(input);

}//getSelect ends here

//------------------enQ Function-------------------
//-------------------------------------------------
void enQ(struct queue* *rear, struct queue* *front, string word)
{
	
	//inserts words into the queue
	
	struct queue* temp = new queue;

	temp->qWord = word;
	temp->next = NULL;

	if (*front == NULL)//used to insert into the queue when there is nothing in the queue
	{
		(*front) = temp;
		(*rear) = temp;
	}
	else//inserts to the back of the line
	{
		(*rear)->next = temp;
		(*rear) = temp;
		(*rear)->qWord = word;
	}

}//enQ() ends here

//------------------dQ Function-------------------
//-------------------------------------------------
string dQ(struct queue* *front)
{
	//removes the first element of the queue

	string word = (*front)->qWord;

	*front = (*front)->next;

	return(word);
}

//--------------isEmpty Function-------------------
//-------------------------------------------------
int isEmpty(struct queue* front)
{
	//returns a 0 if the queue is empty, return a 1 if there is at least 1 element in the queue

	int retVal = 0;

	if (front != NULL)
	{
		retVal = 1;
	}

	return(retVal);
}

//-----------------discardSpecialChar----------------------
//---------------------------------------------------------
void discardSpecialChar(struct queue* *rear, struct queue* *front, string word)
{
	//this function gets rid of illegal character
	
	//local variables
	int endStr = 0;
	int beginStr = 0;
	int index = 0;
	int check = 0;

	//function code
	do
	{

		if (!(('a' <= word[index]) && (word[index] <= 'z')) && (word[index] != '\''))//looks for illegal characters
		{

			enQ(rear, front, word.substr(beginStr, endStr));//inserts the part of the string that does not have illegal characters into the queue

			endStr = 0;//sets end of the string that will be inserted into the queue to 0

			index = index + 1;//increments index

			while ((word[index] != '\0') && ((!(('a' <= word[index]) && (word[index] <= 'z'))) && (word[index] != '\'')))//looks for a legal character to start from
			{
				index = index + 1;
			}

			check = 1;

			beginStr = index;//sets the begining of the string that will be inserted to the queue later

		}
		else
		{
			index = index + 1;//updates index to access char
			endStr = endStr + 1;//updates the final index of the string that will be copied
			check = 0;
		}

	} while (word[index] != '\0');

	if (check == 0)//will run if there was no illegal char found in the string therefore also having no need to split it
	{	
		enQ(rear, front, word.substr(beginStr, endStr));
	}

}//discardSpecialChar() ends here

//--------------------convLower----------------------------
//---------------------------------------------------------
string convLower(string input)
{
	//local variables
	int j = 0;

	while (input[j] != '\0')//this loop checks that all words are upper case
	{

		if (('A' <= input[j]) && (input[j] <= 'Z'))//if a letter in the inputted string is uppercase it will be converted to lowercase
		{
			input[j] = input[j] + 32; //converts char to lower case
		}
		
		j = j + 1;//increments value of the variable that accesses the string
	}

	return(input);

}//convLower() ends here

//--------------------loadFile-----------------------------
//---------------------------------------------------------
BST<wordNcount>* loadFile(BST<wordNcount>* tree, int *totalWords)
{//loadFile begins here

	/*Function loads file into the binary search tree. */

	//local variables
	string fileName;//string for the file name

	string term;//string that is read in from file

	struct queue* front = NULL;//variable used for the front of the queue
	struct queue* rear = NULL;//variable used for the rear of the queue

	wordNcount word;//used to convert strings into the format of wordNcount

	int check;//used to check whether or not the user inputted a valid name to read the file

	//function code

	do
	{ 
		cout << "\nPlease input the name of the file you want to analyze (DO NOT input .txt at the end): ";

		cin >> fileName;

		fileName = fileName + ".txt";//concotanates the string so that it can be properly read by the ifstream

		ifstream myFile(fileName.c_str());

		if (myFile.is_open())//checks if the file exists
		{

			while (myFile >> term)//gets a string from the file and inputs it into the the variable
			{
				if ((!((term[0] >= 48) && (term[0] <= 57))) && (term[0] != '#'))//makes sure the string that was read in is not a digit
				{

					term = convLower(term);//converts all of the string's letters to lower case

					discardSpecialChar(&rear, &front, term);//gets rid of illegal character and inputs into the list

					do
					{
						term = dQ(&front);//gets the string from the queue

						if ((term[0] != '\0') && (!((term[0] >= 48) && (term[0] <= 57))))//makes sure the string is not null and not a number
						{

							word = term;//inputs the string into the class wordNcount format

							BSTNode<wordNcount>* found = tree->find(word);//looks for the string in the BST

							*totalWords = *totalWords + 1;//adds to the total number of words

							if (found == NULL)//if string is not originally in the BST then it will be inserted
							{
							tree->insert(word);
							}
							else//if string is found in the BST then only the count for that string is updated
							{
								found->data.count++;
							}
						}

					} while (isEmpty(front) != 0);//will continue getting strings from the queue until it is empty
					
				}// if statement for ((!((term[0] >= 48) && (term[0] <= 57))) && (term[0] != '#')) ends here

			}//while(myFile >> term) loop getting strings from file ends here

			myFile.close();
			check = 1;
		}
		else//runs if the user inputted a file name that doesn't exist
		{
			cout << "\nThe File was not found\n";
			cout << "Please input file name that does exist.\n\n";
			check = 0;
		}

	} while (check == 0);//runs until the user does inputs a file name that exists 

	return(tree);

}//loadFile ends here

//----------------------toArray----------------------------
//---------------------------------------------------------
void toArray(wordNcount* arr, int* i, BSTNode<wordNcount>* current)
{
	//This function puts all the nodes in the binary tree into an array
	
	//function code
	if (current != NULL)
	{
		toArray(arr, i, current->leftPtr);
		arr[*i] = current->data;//puts a value into the index for the array
		*i = *i + 1;//increments index in the array
		toArray(arr, i, current->rightPtr);
	}

}//toArray() ends here

//---------------------sortByFreq--------------------------
//---------------------------------------------------------
void sortByFreq(wordNcount* arr, int total)
{

	//sorts the nodes in the BST by their frequency

	/*
		war and peace to read in takes about 57.19 sec (57.63 sec )
			when dump is done take about 16.63 sec (16.64 sec)
			insertion sort takes about 2:41.82 (2:53.32)
		for a total 3:57.30 (4:07.74)
		BUT PuTTY seems to sort in a few seconds
	*/

	//local variables
	int i = 0; //used for the outer loop
	int j = 0; //used for the inner loop
	int index = 0; //used to access a certain index
	wordNcount min; //the minimum value
	wordNcount temp; //temporary variables used to switch around parts of the array

	//function code
	for (i = 0; i < total; i++)
	{
		min = arr[i];
		for (j = i + 1; j < total; j++)
		{
			if (arr[j].getCount() <= min.getCount())//compares the values in the nodes (specifically theri strings)
			{
				min = arr[j];
				index = j;
				temp = arr[i];//begins the switch around for sorting
				arr[i] = arr[index];
				arr[index] = temp;
			}
		}

	}

}//sortByFreq() ends here

//-------------------dispBookInfo--------------------------
//---------------------------------------------------------
void dispBookInfo(BST<wordNcount>* tree, int totalWords, int totalUniqueWords, wordNcount* arr)
{
	//display an analysis on the book such as most used and least used words

	int i = 0;// used to iterate through the array

	cout << "\nTotal Words: "<< totalWords<< "\n";
	cout << "Total Unique Words: " << totalUniqueWords << "\n\n";

	toArray(arr, &i, tree->getRoot());//puts the BST into an array

	sortByFreq(arr, totalUniqueWords);//sorts the elements in the array by their frequency values
	
	totalUniqueWords = totalUniqueWords - 1;//value is modified to use in the array without going over the range of the array

	cout << "\nTop 5 Most Frequently Used Words\n";

	for (i = 0; i < 5; i++)//outputs the top 5 most used words
	{
		cout << setw(20) << left << arr[totalUniqueWords].getWord() << setw(5) << right << arr[totalUniqueWords].getCount() << "\n";
		totalUniqueWords = totalUniqueWords - 1;
	}

	cout << "\nTop 5 Least Frequently Used Words\n";

	for (i = 0; i < 5; i++) //outputes the top 5 least frequently used words
	{
		cout <<setw(20) << left << arr[i].getWord() << setw(5) << right << arr[i].getCount() << "\n";
	}

}//dispBookInfo() ends here

//---------------------wordFreq----------------------------
//---------------------------------------------------------
void wordFreq(BST<wordNcount>* tree )
{//wordFreq begins here
	
	//asks the user for a word to look for and if found displays it along with its frequency

	//local variables
	string input; //gets the user's input
	wordNcount find;//since the BST has nodes of type wordNcount the func will only take an input of type wordNcount
	BSTNode<wordNcount>* found;//used to stor the value in found since it returns a pointer to its node

	//function code
	cout<< "\nInput a word and if it exists in the readings its frequency will be displayed: ";
	cin >> input;
	cout << "\n\n";//used for space
	
	find = input;//converts input to wordNcount class

	found = tree->find(find);//looks for the desired node

	if (found != NULL)//if the return is not null it then the word the user was looking for was found and the program displays it
	{
		cout <<found->data.getWord() << "\t" << found->data.getCount() << "\n\n";
	}
	else//find returned a NULL that means the word the user was looking for does not exist in the BST
	{
		cout << "\n"<< input <<" does not exist in the tree\n";
	}

}//wordFreq ends here

//---------------------toFileAlpha-------------------------
//---------------------------------------------------------
void toFileAplha(BST<wordNcount>* tree, string newFileName)
{//toFileAlpha begins here

	//puts the nodes from the BST into a file sorted alphabetically

	//local variables
	int size = tree->length();//sized is used to know how many iterations must be done
	int i = 0;//used to traverse the loop and array

	//function code
	newFileName = newFileName + ".txt";

	wordNcount* arrAlphabet = new wordNcount[size];
	
	toArray(arrAlphabet, &i, tree->getRoot());//puts the elements of the BST into an array

	ofstream analysisFile(newFileName.c_str());//creates file

	i = 0;

	if (analysisFile.is_open())//if it opens it it will write in the analysis onto the file
	{
		do 
		{
			
			analysisFile<< setw(20) << left << arrAlphabet[i].getWord() << setw(5) << right << arrAlphabet[i].getCount() << "\n";

			i = i + 1;

		} while (i < size);
		analysisFile.close();
	}
	else
	{
		cout << "\nThere was some error and we became unable to create the file\n";
	}

}//toFileAlpha ends here

//---------------------toFileFreq--------------------------
//---------------------------------------------------------
void toFileFreq(BST<wordNcount>* tree, string newFileName, wordNcount* arrFrequency)
{//toFileFreq begins here

	//puts the values of the BST node into a file sorted by frequency

	//local variables
	int size = tree->length(); //sized is used to know how many iterations must be done
	int i = 0;//to help navigate in the loop

	//function code
	newFileName = newFileName + ".txt";
	
	ofstream analysisFile(newFileName.c_str());//creates file
	
	i = 0;

	if (analysisFile.is_open())//if it opens it it will write in the analysis onto the file
	{
		do
		{

			analysisFile << setw(20) << left << arrFrequency[i].getWord() << setw(5) << right << arrFrequency[i].getCount() << "\n";

			i = i + 1;

		} while (i < size);
		analysisFile.close();
	}
	else
	{
		cout << "\nThere was some error and we became unable to create the file\n";
	}

}//toFileFreq ends here

//--------------------toFileProcess------------------------
//---------------------------------------------------------
void toFileProcess(BST<wordNcount>* tree, wordNcount* arrFrequency)
{//toFileProcess begins here
	
	//lets the user name the book analysis file and lets the user choose whether or not it should be sorted alphabetically or by frequency
	
	//local variables
	string newFileName;
	char option;

	//function code
	cout << "\nWhat name do you want to give your file \n(do not include the .txt and careful to name it with the same name as another file because it will overwrite it.): ";
	cin >> newFileName;

	do {

		cout << "\n\nDo you want the file to be sorted alphabetically or by frequency\nA: Sort Alphabetically\nF: Sort By Frequency\n";
		cin >> option;

		if ((option == 'a') || (option == 'A'))
		{
			toFileAplha(tree, newFileName);//aphabetically writes the values of the BST into a txt file
			option = '\0';//sets condition to exit the loop
			cout << "\nA file has been created in the same folder where this program is running.\n\n";
		}
		else
		{
			if ((option == 'f') || (option == 'F'))
			{
				toFileFreq(tree, newFileName, arrFrequency);//writes the values of the BST into a txt file but sorted by frequency
				option = '\0';//sets condition to exit the loop
				cout << "\nA file has been created in the same folder where this program is running.\n\n";
			}
			else
			{
				cout << "\nYour input is not an appropriate input, please try again";
			}
		}

	} while (option != '\0');

}//toFileProcess ends here

//----------------------process----------------------------
//---------------------------------------------------------
void process(char select, BST<wordNcount>* tree, wordNcount* arrFrequency)
{
	/*gets input from the user and decides what to do it*/

	switch (select)
	{
		case '1': wordFreq(tree);//looks for a word in the binary tree
			break;
		case '2': toFileProcess(tree, arrFrequency);//outputs the file analysis into a file
			break;
		case '0': cout << "\n\nExiting Program\n";
			break;
		default: cout << "\n\nIncorrect Input Please input another function\n\n";
	}

}//ends process

//----------------------wordDump---------------------------
//---------------------------------------------------------
void wordDump(BST<wordNcount>* tree)
{
	//gives the user the option to display all the individual words in the book or not

	//local variables
	char select;

	//function code
	do
	{

		cout << "Do you want to display all the words in the book along with their frequency? (Y/N): ";
		cin >> select;

		if ((select == 'Y') || (select == 'y'))
		{
			dispInOrder(tree->getRoot());
			select = '\0';// sets the character to exit the loop
		}
		else
		{

			if ((select == 'N') || (select == 'n'))
			{
				select = '\0';// sets the character to exit the loop
			}

		}

	} while(select != '\0');

}//wordDump() ends here

/////////////////////////////////////////////////////
/////////////////////Main Function///////////////////
/////////////////////////////////////////////////////
int main()
{
	//variables
	BST<wordNcount>* tree = new BST<wordNcount>;//usd to access the methods of the templated BST

	int totalWords = 0;//used to count the total number of words

	char select;//used to get the input from the user

	int totalUniqueWords = 0;//used to count all the words in the book

	//main code

	loadFile(tree, &totalWords);//loads in the file into the BST

	totalUniqueWords = tree->length();//gets the total number of unique words in the BST

	wordNcount* arrFreq = new wordNcount[totalUniqueWords];//creates an array to keep the nodes of the BST but sorted by their frequency

	wordDump(tree);//if the user wants to it displays all value of the book alphabetical order this will be used

	dispBookInfo(tree, totalWords, totalUniqueWords, arrFreq);//displays information on the book

	do
	{
		menu();//displays the menu for options

		select = getSelect();//gets input from the user

		process(select, tree, arrFreq);//gets an input from the user and decides what to 

	} while (select != '0');//exits the program if the user inputs '0'

	return(0);//ends program
}