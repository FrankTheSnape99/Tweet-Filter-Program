#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
                                             //by reference
										//gives it the location       //by value
void findingBannedFile(string bannedWords[], int& bannedCounter, const int allBannedWords, const string& fileName)
{
	//------- if banned(1).txt isnt infile, show error -------
	ifstream bannedFile("banned(1).txt");
	if (!bannedFile)
	{
		cout << "Error: Can't open banned(1).txt file" << endl;
	}
	//--------------------------------------------------------

	//while words can be taken from bannedfile 
	//and put into banned words array 
	//&& the counter is less than 11 (size of array)
	//increment bannedcounter.
	//--------------------------------------------------------
	while (bannedFile >> bannedWords[bannedCounter] && bannedCounter < allBannedWords)// >> here just means it extracts words from bannedfile and puts them into the array 'bannedwords' until its gone through all 11.
	{
		bannedCounter++;
	}
	bannedFile.close();
	//--------------------------------------------------------
}

void findingTweetsFileAndOutputting(string bannedWords[], int bannedWordsAmount[], int bannedCounter, const string& filename)
{
	string currentTweet;
	string changedTweet;
	string tweetWord;

	//ifstream for reading from a file
	//----------- if tweets1.txt isnt infile, show error -----
	ifstream tweetsFile("tweets1.txt");
	if (!tweetsFile)
	{
		cout << "Error: Can't open tweets1.txt file" << endl;
	}
	//--------------------------------------------------------

	//ofstream for writing to a file
	//---- if tweets1Filtered.txt isnt infile, show error ----
	ofstream filteredTweetsFile("tweets1Filtered.txt");
	if (!filteredTweetsFile)
	{
		cout << "Error: Could not open filteredTweetsFile.txt" << endl;
	}
	//--------------------------------------------------------

	//------- output tweets, increments 
	// amount of times said word shows up in both files ------
	cout << "TWEETS:" << endl;
	//getline gets lines of tweets from tweetsfile and stores them in current tweets until theres no more tweets. 
	while (getline(tweetsFile, currentTweet))
	{
		stringstream stringstream(currentTweet);
		//"" because through each loop it resetys the tweeted word to be empty ready for being changed.
		changedTweet = "";
		//while ss reads the word in tweetWord
		//it runs through a for loop to see if words match
		//from file to file and if they do then it adds
		//numbers to represent occurances
		while (stringstream >> tweetWord)
		{
			bool isBannedWord = false;
			for (int i = 0; i < bannedCounter; i++)
			{
				//if a word in tweets and banned match, then increment bannedwordsamount and set isBannedWord to treu.
				if (tweetWord == bannedWords[i])
				{
					bannedWordsAmount[i]++;
					isBannedWord = true;
				}
			}
			if (isBannedWord)
			{
				changedTweet += "*** ";
			}
			else
			{
				//space between words even if its not a banned word
				changedTweet += tweetWord + " ";
			}
		}
		//output the tweets with astericks inplace 
		cout << changedTweet << endl;
		//write the changedtweets to the output file.
		filteredTweetsFile << changedTweet << endl;
	}
	//--------------------------------------------------------

	//--------------- closes the tweetsfile ------------------
	tweetsFile.close();
	filteredTweetsFile.close();
	cout << " " << endl;
	cout << "----------------------------------" << endl;
	cout << " " << endl;
	//--------------------------------------------------------

	//-------------- output the bannedwords ------------------
	cout << "BANNED WORDS:" << endl;
	for (int i = 0; i < bannedCounter; i++)
	{
		cout << "'" << bannedWords[i] << "' found " << bannedWordsAmount[i] << " times\n";
	}
	//--------------------------------------------------------
}

int main()
{
	const int allBannedWords = 11;

	string bannedWords[allBannedWords];

	int bannedWordsAmount[allBannedWords] = { 0 };
	int bannedCounter = 0;

	findingBannedFile(bannedWords, bannedCounter, allBannedWords, "banned(1).txt");

	findingTweetsFileAndOutputting(bannedWords, bannedWordsAmount, bannedCounter, "tweets1.txt");
}