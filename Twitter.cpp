// Program to implement a very simplified list of tweets
// from a single simulated Twitter account
// Tweets can be added, deleted, and liked
// Luis Sanjuan-Cruz, Jared Harrell, Holden Davis, Jerod Cohen, Anika Koob, Altana Narmaeva

#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

const int MSGSIZE = 100;	// Maximum size for a tweet message
const int CAPACITY = 10;	// Maximum number of tweets

// Structure used to define a tweet entry
struct Tweet
{
	int id;
	char msg[MSGSIZE];
	int likes;
};


/*
* Prints out an entire timeline to the screen
* timeline = timeline of tweets to be printed
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
*/
void displayTimeline(const Tweet timeline[], int usedSize, int selected);


/*
* Edits currently selected tweet
* with a new message entered by the user.
* timeline = timeline in which the tweet is to be edited
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
* If 'selected' represents a valid array position, the
* selected tweet will be updated.
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doEditTweet(Tweet timeline[], int usedSize, int selected);


/*
* Adds a like to the currently selected tweet.
* timeline = timeline in which the tweet is to be edited
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
* If 'selected' represents a valid array position, the
* selected tweet's likes will be updated.
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doLikeTweet(Tweet timeline[], int usedSize, int selected);


/*
* Deletes currently selected tweet.
* timeline = timeline in from which the entry is to be deleted
* usedSize = number of tweets in the timeline
* selected = position number of currently selected tweet
* If 'selected' represents a valid array position:
* the selected tweet will be deleted
* usedSize will be updated to reflect the updated number of tweets in the timeline
* selected will be updated to -1
* If 'selected' is not valid a 'no tweet is selected message' will be
* displayed and no changes will be made.
*/
void doDeleteTweet(Tweet timeline[], int& usedSize, int& selected);


/*
* If there is room in the timeline for new tweets, then this gets
* a new tweet from the user and adds it to the timeline.
* timeline = timeline in which the tweet is to be added
* usedSize = number of tweets in the timeline
* If tweet was able to be added, returns the position number in the
* timeline of where the item was added, and usedSize will be
* updated to reflect the number of tweets now in the timeline.
* If tweet was not able to be added, returns -1, and usedSize
* remains unchanged.
*/
int doAddTweet(Tweet timeline[], int& usedSize);


/*
* Adds a new tweet to the list
* timeline = timeline in which the entry is to be added
* usedSize = number of tweets in the timeline
* message = tweet message to be added
* If tweet was able to be added, returns the position number in the
* timeline of where the item was added, and usedSize will be
* updated to reflect the number of tweets now in the timeline.
* If tweet was not able to be added, returns -1, and usedSize
* remains unchanged.
*/
int addTweet(Tweet timeline[], int& usedSize, const char message[]);


/*
* Returns the next available ID number
* timeline = timeline in which to find the highest ID
* usedSize = number of tweets in the timeline
* If timeline is empty, returns 100;
* otherwise, returns 1 + highest ID number in the timeline
*/
int getNextId(Tweet timeline[], int usedSize);


/*
* Gets a tweet id from the user. Searches a timeline to try
* to find the specified tweet by its id.
* timeline = timeline to be searched
* usedSize = number of tweets in the timeline
* If the tweet is found, the position number of where the tweet
* is stored in the timeline will be returned.  If the tweet is
* not found, a 'not found message' will be printed, and
* the value -1 will be returned.
* If timeline is empty, an 'empty' message will be printed, and
* the value -1 will be returned.
*/
int selectTweet(const Tweet timeline[], int usedSize);



int main()
{
	Tweet timeline[CAPACITY];	// Twitter timeline
	int choice;					// User's menu choice
	int usedSize = 0;			// Num of tweets in the timeline
	int selected = -1;			// Currently selected tweet
	int tmp;					// Temporary variable

	// Add some starter entries for testing purposes
	selected = addTweet(timeline, usedSize, "Where do they get the seeds to plant seedless watermelons?");
	selected = addTweet(timeline, usedSize, "Waffles are just pancakes with convenient boxes to hold your syrup.");
	selected = addTweet(timeline, usedSize, "Last night I even struck up a conversation with a spider. Turns out he's a web designer.");



	do
	{
		cout << "1. Display Timeline\n";
		cout << "2. Select Tweet\n";
		cout << "3. Add New Tweet\n";
		cout << "4. Edit Selected Tweet\n";
		cout << "5. Like Selected Tweet\n";
		cout << "6. Delete Tweet\n";
		cout << "7. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Get the numeric entry from the menu
		cin >> choice;

		// Corrects issues where user might enter a non-integer value
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Select: ";
			cin >> choice;
		}

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		// Should be used after getting any numeric input from the keyboard
		cin.ignore();

		switch (choice)
		{
		case 1:
			displayTimeline(timeline, usedSize, selected);
			break;
		case 2:
			tmp = selectTweet(timeline, usedSize);
			// if selected tweet exists, update selected variable;
			// otherwise leave it unchanged
			if (tmp > -1)
				selected = tmp;
			break;
		case 3:
			tmp = doAddTweet(timeline, usedSize);
			// if tweet was added, make it be the selected tweet;
			// otherwise leave it unchanged
			if (tmp > -1)
				selected = tmp;
			break;
		case 4:
			doEditTweet(timeline, usedSize, selected);
			break;
		case 5:
			doLikeTweet(timeline, usedSize, selected);
			break;
		case 6:
			doDeleteTweet(timeline, usedSize, selected);
			break;
		}

	} while (choice != 7);

	return 0;
}

int doAddTweet(Tweet timeline[], int& usedSize)
{
	// Check if timeline is full
	if (usedSize >= CAPACITY)
	{
		cout << "\nERROR: Timeline is full\n";
		return -1;
	}

	// Get new tweet from user
	char newTweet[MSGSIZE];
	cout << "Enter a new tweet: \n";
	cin.getline(newTweet, MSGSIZE);

	// return -1 if timeline full, otherwise return usedSize - 1
	if (addTweet(timeline, usedSize, newTweet) == -1)
	{
		return -1;
	}
	else
		return usedSize - 1;
}

void doEditTweet(Tweet timeline[], int usedSize, int selected)
{
	//To-be edited Tweet
	char newTweet[MSGSIZE];

	//Checks if a tweet was selected
	if (selected < 0 || selected >= usedSize)
	{
		cout << "No tweet is selected." << endl;
		return;
	}
	else if (selected > 0)
	{
		//If tweet is selected, edits and updates into new message in the timeline
		cout << "Enter a new tweet message:" << endl;
		cin.getline(newTweet, MSGSIZE);
		snprintf(timeline[selected].msg, MSGSIZE, "%s", newTweet);
	}
}

void doLikeTweet(Tweet timeline[], int usedSize, int selected)
{
	// Check if selected tweet is valid, add like
	if (selected >= 0 && selected < usedSize)
	{
		timeline[selected].likes += 1;
	}
	else
		cout << "No tweet is selected.\n";
}

void displayTimeline(const Tweet timeline[], int usedSize, int selected)
{
	// Header
	cout << "\nTweets: \n\n";
	printf("%s %6s %7s %7s\n", "Sel", "ID", "Likes", "Tweet");

	//Checks if the timeline is empty
	if (usedSize == 0)
	{
		printf("%25s", "***** Empty *****");
		cout << endl;
	}

	// Loop to check if counter is on selected tweet
	// print arrow if true, print spaces if false
	for (int count = 0; count < usedSize; count++)
	{
		if (count == selected)
		{
			printf("%-7s", "-->");
		}
		else
			printf("%-7s", "   ");
		printf("%-9d %-3d %-99s\n", timeline[count].id, timeline[count].likes, timeline[count].msg);
	}

	cout << "\n";
}


int addTweet(Tweet timeline[], int& usedSize, const char message[])
{
	// Check if there is space in the timeline array
	if (usedSize < CAPACITY)
	{
		// add the message to the timeline array, assign an ID, and set likes = 0
		strncpy_s(timeline[usedSize].msg, message, MSGSIZE);

		timeline[usedSize].id = getNextId(timeline, usedSize);
		timeline[usedSize].likes = 0;

		usedSize++;

		// return the index of the added tweet
		return usedSize - 1;
	}

	// if timeline full return -1 to indicate failure
	return -1;
}


int getNextId(Tweet timeline[], int usedSize)
{
	// starting ID number
	int maxID = 99;

	// Loop to go through all current ID's and find the largest
	for (int count = 0; count < usedSize; count++)
	{
		if (timeline[count].id > maxID)
		{
			maxID = timeline[count].id;
		}
	}

	return maxID + 1;
}


void doDeleteTweet(Tweet timeline[], int& usedSize, int& selected)
{
	// Check if selected tweet is valid
	if (selected < 0 || selected >= usedSize)
	{
		cout << "No tweet is selected.\n";
		return;
	}

	// If selected tweet is valid, replace selected tweet with the next in the array,
	// repeat for all tweets
	for (int count = selected; count < usedSize - 1; count++)
	{
		timeline[count] = timeline[count + 1];
	}

	// Update user on status, remove selection
	cout << "Selected tweet has been deleted.\n";
	usedSize--;
	selected = -1;
}

int selectTweet(const Tweet timeline[], int usedSize)
{
	// Check if timeline has tweets in it
	if (usedSize == 0)
	{
		cout << "Timeline is empty.\n";
		return -1;
	}

	int givenID;
	cout << "Enter an ID for the tweet to be selected:\n";
	cin >> givenID;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error: Invalid ID\n";
		cout << "Enter an ID for the tweet to be selected:\n";
		cin >> givenID;
	}

	// Loop to find selected ID and return that index position, otherwise error
	for (int count = 0; count < usedSize; count++)
	{
		if (givenID == timeline[count].id)
		{
			return count;
		}
	}

	cout << "ID was not found.\n\n";
	return -1;
}