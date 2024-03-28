#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// Constants
const int MAX_TWEET_LENGTH = 180;

// Function prototypes
void valid(string str);
void viewTweets(string username);
void followUser(string username);

int main()
{
    int choice, exit = 0;
    string ans, psd, name, fname, bio, usern, pw, line, nusn;
    ofstream fileo;
    ifstream filei;
    string username;
    string tweet;

    ofstream outfile;
    outfile.open("Users.txt", ios_base::app);
    outfile.close();
    outfile.open("Passwords.txt", ios_base::app);
    outfile.close();
    outfile.open("Followers.txt", ios_base::app);
    outfile.close();
    outfile.open("Tweets.txt", ios_base::app);
    outfile.close();

    // Define outfile variable

    // Display menu until user chooses to exit
    while (exit == 0)
    {
        cout << "----------------------------------------------Welcome to Twitter!----------------------------------------------" << endl;
        cout << "1. Create an Account" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Add a Tweet" << endl;
        cout << "4. View Tweets" << endl;
        cout << "5. Follow a User" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Create a username: ";
            cin >> usern;
            valid(usern);
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your password: ";
            cin >> psd;
            cout << "Enter your full name: ";
            cin >> fname;
            cout << "Enter your bio: ";
            cin >> bio;
            fileo.open("Users.txt", ios_base::app);
            fileo << usern << endl;
            fileo.close();
            fileo.open("Passwords.txt", ios_base::app);
            fileo << usern << " " << psd << endl;
            fileo.close();
            cout << "Account created!" << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter your username: ";
            cin >> usern;
            cout << "Enter your password: ";
            cin >> pw;
            filei.open("Passwords.txt");
            if (!filei.is_open())
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                bool found = false;
                while (filei >> line)
                {
                    if (line == usern)
                    {
                        filei >> line;
                        if (line == pw)
                        {
                            cout << "Login successful!" << endl;
                            username = usern;
                            found = true;
                            break;
                        }
                    }
                }
                filei.close();
                if (!found)
                {
                    cout << "Invalid username or password." << endl;
                }
            }
        }
        else if (choice == 3)
        {
            cout << "Enter your tweet (max 180 characters): ";
            cin.ignore(); // Ignore newline character left in stream by previous input
            getline(cin, tweet);
            if (tweet.length() > MAX_TWEET_LENGTH)
            {
                cout << "Your tweet is too long. It will be truncated to 180 characters. Continue? (y/n) ";
                cin >> ans;
                if (ans == "y")
                {
                    tweet = tweet.substr(0, MAX_TWEET_LENGTH);
                    cout << "Tweet added!" << endl;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                cout << "Tweet added!" << endl;
            }
            outfile.open("Tweets.txt", ios_base::app);
            outfile << username << ": " << tweet << endl;
            outfile.close();
        }
        else if (choice == 4)
        {
            if (username.empty())
            {
                cout << "You must be logged in to view tweets." << endl;
            }
            else
            {
                viewTweets(username);
            }
        }
        else if (choice == 5)
        {
            if (username.empty())
            {
                cout << "You must be logged in to follow a user." << endl;
            }
            else
            {
                followUser(username);
            }
        }
        else if (choice == 6)
        {
            exit = 1;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}

// Check if a username is already in use
void valid(string str)
{
    string dir, user;
    ifstream file;
    dir = str + ".txt";
    file.open(dir.c_str());
    if (!file.is_open() && file.fail())
    {
        return;
    }
    else
    {
        cout << "\nThis username already exists!\nCreate a username:";
        cin >> str;
        valid(str);
    }
}

// View tweets from users that the input user is following
void viewTweets(string username)
{
    // Get a list of users that the input user is following
    string following[100];
    int numFollowing = 0;
    ifstream infile("Followers.txt");
    string line;
    while (getline(infile, line))
    {
        int pos = line.find(": ");
        string user = line.substr(pos + 2);
        if (user == username)
        {
            string userToFollow = line.substr(0, pos);
            following[numFollowing] = userToFollow;

            numFollowing++;
        }
    }
    infile.close();

    // Print up to 10 tweets from the users that the input user is following
    int numTweets = 0;
    ifstream infile2("Tweets.txt");
    cout << "Tweets:\n";
    while (getline(infile2, line) && numTweets < 10)
    {
        int pos = line.find(": ");
        string user = line.substr(0, pos);
        bool found = false;
        for (int i = 0; i < numFollowing; i++)
        {
            if (following[i] == user)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            cout << line << endl;
            numTweets++;
        }
    }

    // Print the rest of the tweets from the "Tweets.txt" file
    while (getline(infile2, line) && numTweets < 10)
    {
        cout << line << endl;
        numTweets++;
    }
    infile2.close();
}

// Follow a user
void followUser(string username)
{
    string userToFollow;
    cout << "Enter the username of the user you want to follow: ";
    cin >> userToFollow;
    ifstream infile("Users.txt");
    if (!infile.is_open())
    {
        cout << "Error: could not open file Users.txt" << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(infile, line))
    {
        if (line == userToFollow)
        {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found)
    {
        cout << "User not found." << endl;
        return;
    }

    ofstream outfile("Followers.txt", ios_base::app);
    outfile << userToFollow << ": " << username << endl;
    outfile.close();
    cout << "You are now following " << userToFollow << "." << endl;
}