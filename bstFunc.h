//#pragma once
#include  <iostream>
#include <string>
#include <fstream>
using namespace std;

//-------------------struct BSTNode------------------------
//---------------------------------------------------------
template <typename T>
struct BSTNode
{
public:
	BSTNode<T>* rightPtr;

	BSTNode<T>* leftPtr;

	T data;
};

//------------------------class BST------------------------
//---------------------------------------------------------
template <typename T>
class BST
{
private:
	BSTNode<T>* root;//
public:

	//getters and foward declarations of templates

	BST();
	//~BST<T>();
	BSTNode<T>* getRoot();
	struct BSTNode<T>* insert(T data);
	struct BSTNode<T>* insertNode(BSTNode<T>* currentNode, BSTNode<T>* newNode);
	BSTNode<T>* find(T data);
	BSTNode<T>* recurFind(BSTNode<T>* current, T data);
	BSTNode<T>* recurDaddy(BSTNode<T>* current, T data);
	BSTNode<T>* findDaddy(T data);
	BSTNode<T>* findReplacement(BSTNode<T>* current);
	BSTNode<T>* findRightMost(BSTNode<T>* current);
	BSTNode<T>* findLeftMost(BSTNode<T>* current);
	BSTNode<T>* findReplacementsChild(BSTNode<T>* replace);
	void preDispInOrder();
	void displayInOrder(BSTNode<T>* currentNode);
	void removeWhen2Kids(BSTNode<T>* removeNode);
	void remove(T data);
	void empty();
	void emptyRecur(BSTNode<T>* current);
	bool elementExists(T data);
	int lengthRecur(BSTNode<T>* current, int count);
	int length();
	
};//class BST ends here

//---------------------BST Constructor---------------------
//---------------------------------------------------------
template <typename T>
BST<T>::BST()
{
	//BSTNode<T>* root = NULL;
}

//------------------------getRoot--------------------------
//---------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::getRoot()
{

	//BSTNode<T>* current = root;//gets the root

	return(root);
}

// -----------------------insert--------------------------------
//-------------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::insert(T data)
{

	//sets up all the variables to insert the new node

	BSTNode<T>* temp = NULL;

	temp = new BSTNode<T>;

	temp->data = data;

	temp->leftPtr = NULL;

	temp->rightPtr = NULL;

	this->root = insertNode(root, temp);

	return(this->root);

}//insert() ends here

// --------------------insertNode------------------------------
//-------------------------------------------------------------
template<typename T>
BSTNode<T>* BST<T>::insertNode(BSTNode<T>* currentNode, BSTNode<T>* newNode)
{
	//function recursively calls upon itself to insert a node into the BST

	if (currentNode == NULL)//runs if there is no other node inserted before hand
	{
		currentNode = newNode;//sets the root = current
	}
	else {
		if (newNode->data < currentNode->data)//if the element that wants to be inserted is less than the current node it will send it to the left side
		{
			currentNode->leftPtr = insertNode(currentNode->leftPtr, newNode);
		}
		else
		{
			if (newNode->data > currentNode->data)//if the element that wants to be inserted is greater than the current node it will send it to the right side
			{
				currentNode->rightPtr = insertNode(currentNode->rightPtr, newNode);
			}
		}
	}

	return(currentNode);

}//insertNode() ends here

// ------------------------find--------------------------------
//-------------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::find(T data)
{
	//Sets up the variables to use the recrFind function

	BSTNode<T>* current = root;
	BSTNode<T>* retVal = NULL;

	retVal = recurFind(current, data);

	return(retVal);
}

// ----------------------recurFind-----------------------------
//-------------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::recurFind(BSTNode<T>* current, T data)
{
	//recursively calls on itself to find the element the user specified
	//returns NULL it is not found

	//local variables
	BSTNode<T>* found;
	
	//function code
	if (current == NULL)//if node is not found or tree is empty
	{
		found = NULL;
	}
	else
	{
		if (current->data == data)
		{
			found = current;
		}
		else
		{
			if (current->data > data)//goes to the left node if the current's data is greater than the the inputted data
			{
				found = recurFind(current->leftPtr, data);
			}
			else//goes to the right node if the current's data is less than the the inputted data
			{
				found = recurFind(current->rightPtr, data);
			}

		}//ends else statement for current->data == data)

	}//ends else statement for (current == NULL)

	return(found);

}//recurFind() ends here

// ---------------------findDaddy------------------------------
//-------------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::findDaddy(T data)
{
	//Sets up all variables to call the function that will find the parent node

	BSTNode<T>* current = root;
	BSTNode<T>* retVal = NULL;

	retVal = recurDaddy(current, data);//function that finds the parent node

	return(retVal);

}//findDaddy() ends here

// ---------------------recurDaddy-----------------------------
//-------------------------------------------------------------
template <typename T>
BSTNode<T>* BST<T>::recurDaddy(BSTNode<T>* current, T data)
{
	//recursively calls itself to look for the nodes parent

	//local variables
	BSTNode<T>* found;//The variable that is returned

	//function code
	if (current == NULL)//if node is not found or tree is empty
	{
		found = NULL;
	}
	else
	{

		if ((current->rightPtr != NULL) && (current->rightPtr->data == data))//if the currents node's rightPtr is not NULL and has the inputted data then current is the parent
		{
			found = current;
		}
		else
		{
			if ((current->leftPtr != NULL) && (current->leftPtr->data == data))//if the currents node's leftPtr is not NULL and has the inputted data then current is the parent
			{
				found = current;
			}
			else
			{
				if (current->data > data)//goes to the left node if the current's data is greater than the the inputted data
				{
					found = recurDaddy(current->leftPtr, data);
				}
				else////goes to the right node if the current's data is less than the the inputted data
				{
					found = recurDaddy(current->rightPtr, data);
				}

			}//else statement for ((current->leftPtr != NULL) && (current->leftPtr->data == data)) ends here

		}//else statement for ((current->rightPtr != NULL) && (current->rightPtr->data == data)) ends here

	}//else statement for (current == NULL) ends here

	return(found);

}//recurDaddy() ends here

// ---------------------findReplacement------------------------
//-------------------------------------------------------------
template<typename T>
BSTNode<T>* BST<T>::findReplacement(BSTNode<T>* current)
{

	//finds a replacement for a node that is being removed & has atleast 1 child

	if (current->leftPtr != NULL)
	{
		current = findRightMost(current->leftPtr);
	}
	else
	{
		current = findLeftMost(current->rightPtr);
	}

	return(current);

}//findReplacement() ends here

// ---------------------findRightMost--------------------------
//-------------------------------------------------------------
template<typename T>
BSTNode<T>* BST<T>::findRightMost(BSTNode<T>* current)
{

	/*finds the right most child of the element current
	when used input the child of the node you're trying to delete
	used in removal function*/

	if (current->rightPtr != NULL)
	{
		current = findRightMost(current->rightPtr);
	}

	return(current);

}//findRightMost() ends here

// ---------------------findLeftMost---------------------------
//-------------------------------------------------------------
template<typename T>
BSTNode<T>* BST<T>::findLeftMost(BSTNode<T>* current)
{

	/*finds the left most child of the element current
	when used input the child of the node you're trying to delete
	used in removal function*/

	if (current->leftPtr != NULL)
	{
		current = findLeftMost(current->leftPtr);
	}

	return(current);

}//findLeftMost() end here

// -----------------findReplacementsChild----------------------
//-------------------------------------------------------------
template<typename T>
BSTNode<T>* BST<T>::findReplacementsChild(BSTNode<T>* replace)
{

	//finds the child node of the node that will replace the node that is being removed

	BSTNode<T>* retVal;

	if (replace->rightPtr == NULL)
	{
		retVal = replace->leftPtr;//gets the left child
	}
	else
	{
		retVal = replace->rightPtr;//gets the right child
	}

	return(retVal);

}//findReplacementsChild() ends here

// --------------------preDispInOrder--------------------------
//-------------------------------------------------------------
template <typename T>
void BST<T>::preDispInOrder()
{
	//sets up variables to display elements of the BST in order

	BSTNode<T>* current = root;

	displayInOrder(current);

}//preDispInOrder() ends here

// ------------------displayInOrder----------------------------
//-------------------------------------------------------------
template <typename T>
void BST<T>::displayInOrder(BSTNode<T>* currentNode)
{
	//displays the elements of the BST in order

	if (currentNode != NULL)
	{
		displayInOrder(currentNode->leftPtr);
		cout << currentNode->data << "\n";
		displayInOrder(currentNode->rightPtr);
	}

}//displayInOrder() ends here

// ------------------removeWhen2Kids---------------------------
//-------------------------------------------------------------
template <typename T>
void BST<T>::removeWhen2Kids(BSTNode<T>* removeNode)
{

	//adjusts the binary tree when the node that the user wants to remove has 2 children

	if (removeNode != NULL)
	{

		BSTNode<T>* sub = findReplacement(removeNode);//sub: stands for substitute

		BSTNode<T>* removesDad = findDaddy(removeNode->data);//finds the parent of the node what the user wants to remove

		BSTNode<T>* subsChild = findReplacementsChild(sub);//gets the replacement's child

		BSTNode<T>* subsDad = findDaddy(sub->data); //find's the substitute's parent

		if (removesDad == NULL)//if the user wants to remove the root node
		{

			if (subsDad->data < sub->data)//if the replacement node (sub) is greater than its parent
			{
				subsDad->rightPtr = subsChild;
			}
			else//if the replacement node (sub) is less than its parent
			{
				subsDad->leftPtr = subsChild;
			}

			//take's over root's pointers
			sub->rightPtr = removeNode->rightPtr;
			sub->leftPtr = removeNode->leftPtr;

		}
		else//removes non-root node with 2 children
		{

			if (subsDad->data < sub->data)//if the replacement node (sub) is greater than its parent
			{
				subsDad->rightPtr = subsChild;
			}
			else//if the replacement node (sub) is less than its parent
			{
				subsDad->leftPtr = subsChild;
			}

			//take's over root's pointers
			sub->rightPtr = removeNode->rightPtr;
			sub->leftPtr = removeNode->leftPtr;

			if (removesDad->data < removeNode->data)//if the remove's node is greater than its parent
			{
				removesDad->rightPtr = sub;
			}
			else//if the remove's node is less than its parent
			{
				removesDad->leftPtr = sub;
			}

		}//removes non-root node with 2 children ends here

		free(removeNode);

	}// if(removeNode != NULL) ends here

}//removeWhen2Kids ends here

// -------------------------remove-----------------------------
//-------------------------------------------------------------
template <typename T>
void BST<T>::remove(T data)
{

	//This function will search for the element the user wants to remove and if found will remove it

	//function code
	BSTNode<T>* removeThis = find(data);//if the element exists it will return a pointer to that element

	if (removeThis != NULL)//the value that the user wants to remove was found and will be removed
	{
		BSTNode<T>* daddy = findDaddy(removeThis->data);//looks for removeThis's parent

		if ((removeThis->leftPtr == NULL) && (removeThis->rightPtr == NULL))//deletes a leaf node
		{

			if (daddy->data < removeThis->data)//sets its parent's right pointer to NULL
			{
				daddy->rightPtr = NULL;
			}
			else//sets its parent's left pointer to NULL
			{
				daddy->leftPtr = NULL;
			}

			free(removeThis);//Free's up removeThis

		}
		else
		{
			if ((removeThis->leftPtr != NULL) && (removeThis->rightPtr != NULL))//deletes when node has 2 children
			{

				removeWhen2Kids(removeThis);//calls function that removes an element with 2 childen

			}
			else
			{

				if ((removeThis->leftPtr != NULL) || (removeThis->rightPtr != NULL))//deletes when node has 1 child
				{

					if ((removeThis->leftPtr != NULL) && (removeThis->rightPtr == NULL))//if only the left child exists
					{

						if (removeThis->data > daddy->data)//if the element being removed has a larger value than its parent
						{
							daddy->rightPtr = removeThis->leftPtr;//sets the parent's right pointer to the removed element's left child
						}
						else//if the element being removed has a smaller value than its parent
						{
							daddy->leftPtr = removeThis->leftPtr;//sets the parent's left pointer to the removed element's left child
						}

						free(removeThis);//free's the removed element

					}
					else
					{
						if ((removeThis->leftPtr == NULL) && (removeThis->rightPtr != NULL))//if only the right child exists
						{

							if (removeThis->data > daddy->data)//if the element being removed has a larger value than its parent
							{

								daddy->rightPtr = removeThis->rightPtr;//sets the parent's right pointer to the removed element's right child

							}
							else//if the element being removed has a smaller value than its parent
							{
								daddy->leftPtr = removeThis->rightPtr;//sets the parent's left pointer to the removed element's right child

							}

							free(removeThis);//free's the removed element

						}//ends ((removeThis->leftPtr == NULL) && (removeThis->rightPtr != NULL))
					}

				}

			}//else from ((removeThis->leftPtr != NULL) && (removeThis->rightPtr != NULL)) ends here

		}//the else for ((removeThis->leftPtr == NULL) && (removeThis->rightPtr == NULL)) ends here

	}//if (removeThis != NULL) statement ends here

}//remove function ends here

// --------------------elementExists---------------------------
//-------------------------------------------------------------
template <typename T>
void BST<T>::empty()
{//empty() begins here

	//This function will call a recursive function to delete the binary tree

	BSTNode<T>* current = root;//gets the root

	emptyRecur(current);

}//empty() ends here

// ----------------------emptyRecur----------------------------
//-------------------------------------------------------------
template<typename T>
void BST<T>::emptyRecur(BSTNode<T>* current)
{//begins emptyRecur()

	//This function will recursively traverse the list in post order to delete the 
	//binary tree

	//function code
	if (current != NULL)
	{
		emptyRecur(current->leftPtr);
		emptyRecur(current->rightPtr);
		current->leftPtr = NULL;
		current->rightPtr = NULL;
		current = NULL;
		free(current);
	}

}//ends empty

// --------------------elementExists---------------------------
//-------------------------------------------------------------
template<typename T>
bool BST<T>::elementExists(T data)
{//begins elementExists

	/*checks if an element exists in the binary tree. If the element exists function
	will return true*/

	//local variables
	bool retVal = false; //the return value
	BSTNode<T>* found = find(data);//looks for the element in the list

	//function code
	if (found != NULL)//will execute command if it returns a non-NULL value
	{
		retVal = true;
	}

	return(retVal);

}//ends elementExists

// ---------------------lengthRecur----------------------------
//-------------------------------------------------------------
template <typename T>
int BST<T>::lengthRecur(BSTNode<T>* current, int count)
{//length() begins here

	//Recursively traverses the binary tree and count the number of elements present

	//function code
	if (current != NULL)
	{
		count = lengthRecur(current->leftPtr, count);
		count = count + 1;
		count = lengthRecur(current->rightPtr, count);
	}

	return(count);
}//lengthRecur() ends here
 
// -----------------------length-------------------------------
//-------------------------------------------------------------
template <typename T>
int BST<T>::length()
{//length() begins here

	//This function will call a recursive function to count the elements in a binary tree

	BSTNode<T>* current = root;//gets the root

	int count = 0;

	count = lengthRecur(current, count);//calls the function that counts the elements in the list

	return(count);

}//length() ends here
