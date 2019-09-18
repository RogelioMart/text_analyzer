# text_analyzer
Reads in a text document and checks the amount of words in the the document.

In order to use the program please place a .txt file in the same folder where the program
is, then boot up the txtProcessor program.

WARNING: Make sure your program has normal apostrophes in it because the program cannot tell
the difference between this ''' and this'’'.

Begin by typing in the name of the txt file without typing in the .txt file extension

It should take about a minute to read in a large book such as "War and Peace" 

Then you will be asked if
"Do you want to display all the words in the book along with their frequency? (Y/N): "

If you input y or Y it will output an alphabetical list of all the words in the book along
with a number that represents the amount of times that word apeared in the book.
If you inputted n or N no list will display and the program will continue on display the
rest of the information on the book

Afterwards the total amount of words and total amount of unique words will be displayed.
After this point the program will take some time to sort the value of the Binary Search
Tree by word frequency this takes about 3 minutes although running on PuTTY takes a few 
second so result may vary but go ahead and take a break while you wait for the list to sort
a and display the information.

After it is sorted you will be shown the top 5 most used words in the book and the top 5
least used words in the book.

You will also be shown a menu with these options.

Choose option:
1 - Find the Frequency of a word
2 - Output frequency analysis into a file.
0 - Exit from program

you can only exit the program by inputting '0'.

If you input '1' you will be asked to input a word. 
If the word exists in the book it will display the word along with its frequency.
If it doesn't exist it will tell you it doesn't exist.
After this you will be taken back to the main menu.

If you input '2' you will be  
You will be writing the book analysis into a file.
First you will be asked to give your file a name.
WARNING: if you write the name of another file that already exists in that folder you will
be overwriting the contents of that file.

next you will be shown the menu.

Do you want the file to be sorted alphabetically or by frequency
A: Sort Alphabetically
F: Sort By Frequency

If you input 'A' or 'a' a new file will be created in that same folder that has the book's
words and their frequencies sorted in alphabetical order.

If you input 'f' or 'F' a new file will be created in that same folder that has the book's
words and their frequencies sorted by their frequency.

After this you will be taken back to the main menu.
