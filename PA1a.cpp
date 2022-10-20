//Diana Salinas
//Programming Assignment 1
//  to run program, just use:
//  g++ -o PA1a PA1a.cpp
//  and then:
//  ./PA1a
#include <iostream>
using namespace std;
#define SIZE 30 // 

// Function to convert the string to lowercase since I was having trouble when 
// they were all captilized, having lowercased made it so I could for sure get 
// the needed representation of the letter
void toLowerCase(char messageRep[], int position)
{
	for (int i = 0; i < position; i++) {
		if (messageRep[i] > 64 && messageRep[i] < 91)
			messageRep[i] += 32;
	}
}

// Function to remove all the spaces in a string 
//(would affect the Mississippi quesiton)
int removeSpaces(char* messageRep, int position)
{
    int i, count = 0;
	for (i = 0; i < position; i++)
		if (messageRep[i] != ' ')
			messageRep[count++] = messageRep[i];
	messageRep[count] = '\0';
	return count;
}

// constructing the Playfair Matrix
void matrixCons(char keyword[], int keyword1, char keywordE[5][5])
{
	int i, j, k = 0;
	// a hashmap for the alphabet (26 letters = 26 characters) 
	int letters[26] = { 0 };
	for (i = 0; i < keyword1; i++) {
        //since I and J are counted to be in the same blokc
		if (keyword[i] != 'j')
			letters[keyword[i] - 97] = 2;
	}

	letters['j' - 97] = 1;
    //we are referencing these varibales outside of the function 
    //since the count gets restarted
	i = 0;
	j = 0;

	for (k = 0; k < keyword1; k++) {
		if (letters[keyword[k] - 97] == 2) {
			letters[keyword[k] - 97] -= 1;
			keywordE[i][j] = keyword[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	for (k = 0; k < 26; k++) {
		if (letters[k] == 0) {
			keywordE[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}

// Function to search for the characters of a digraph
// in the keyword square and return their position
void search(char keywordE[5][5], char a, char b, int arr[])
{
    //we are referencing these varibales outside of the function 
    //since it will be used in other functions and not just the insdie loops
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';
	for (i = 0; i < 5; i++) 
    {
		for (j = 0; j < 5; j++) 
        {
			if (keywordE[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keywordE[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

// Function to find the modulus with 5
int mod5(int a) { return (a % 5); }

// Function to make the messageRep text length to be even
int prepare(char message[], int ptrs)
{
	if (ptrs % 2 != 0) 
    {
		message[ptrs++] = 'x';
		message[ptrs] = '\0';
	}
	return ptrs;
}

// Function for performing the encryption
void encrypt(char message[], char keywordE[5][5], int position)
{
	int i, a[4];

	for (i = 0; i < position; i += 2) 
    {
		search(keywordE, message[i], message[i + 1], a);

		if (a[0] == a[2]) 
        {
			message[i] = keywordE[a[0]][mod5(a[1] + 1)];
			message[i + 1] = keywordE[a[0]][mod5(a[3] + 1)];
		}
		else if (a[1] == a[3]) 
        {
			message[i] = keywordE[mod5(a[0] + 1)][a[1]];
			message[i + 1] = keywordE[mod5(a[2] + 1)][a[1]];
		}
		else 
        {
			message[i] = keywordE[a[0]][a[3]];
			message[i + 1] = keywordE[a[2]][a[1]];
		}
	}
}

// Function to encrypt using Playfair Cipher
void encryption(char message[], char keyword[])
{
    //matrix encryption starts
	char position, keyword1, keywordE[5][5];

	// the keyword gets pulled, should go first since 
    //its the first thing we need to put on the matrix
    //plus would be best since its the way which it talks about on the 
    //PA assignment
	keyword1 = strlen(keyword);
	keyword1 = removeSpaces(keyword, keyword1);
	toLowerCase(keyword, keyword1);

	// the message will be next since that is next to be able to encrypt
	position = strlen(message);
	toLowerCase(message, position);
	position = removeSpaces(message, position);

	position = prepare(message, position);  //placing
	matrixCons(keyword, keyword1, keywordE);   //matrix 
	encrypt(message, keywordE, position); //encryption yada yada yada
}

// and fianlly... the driver code 
int main()
{
    cout << endl;
    cout << "Diana Salinas -- Programming Assignment 1\n";
    cout << endl;
    cout << "Part 1 of Encryption\n";
    cout << endl;
    //////part 1 of encryption

    //setting arrays for message and keyword
	char message[SIZE];
    char keyword[SIZE];
    char message1[SIZE]; 

    // the message that will be encrypted
	strcpy(message, "OLEMISS");
    strncpy(message1, message, 30);

	// Keyword that will encrypted
	strcpy(keyword, "OXFORD");
    
    // encrypting using the Playfair Cipher
	encryption(message, keyword);

    //captilize the message 
    for (int i = 0; i < 30; i++)
        message1[i] = toupper(message1[i]);

    //captilize the keyword
    for (int i = 0; i < 30; i++)
        keyword[i] = toupper(keyword[i]);

    cout << "The message is: " << message1 << "\n";
	cout << "The keyword is: " << keyword << "\n";

     //captilize the transformed message
    for (int i = 0; i < 30; i++)
        message[i] = toupper(message[i]);

	cout << "The transformed message is: " << message << "\n";
    cout << endl;
    
    /////part 2 of encryption
     cout << "Part 2 of Encryption\n";
     cout << endl;

    //setting arrays for message and keyword

    // the message that will be encrypted
	strcpy(message, "Mississippi is a state");
    strncpy(message1, message, 30);

	// Keyword that will encrypted
	strcpy(keyword, "OLEMISS");
    
    // encrypting using the Playfair Cipher
	encryption(message, keyword);

    //captilize the message 
    for (int i = 0; i < 30; i++)
        message1[i] = toupper(message1[i]);

    //captilize the keyword
    for (int i = 0; i < 30; i++)
        keyword[i] = toupper(keyword[i]);

    cout << "The message is: " << message1 << "\n";
	cout << "The keyword is: " << keyword << "\n";

     //captilize the transformed message
    for (int i = 0; i < 30; i++)
        message[i] = toupper(message[i]);

	cout << "The transformed message is: " << message << "\n";

	return 0;
}
