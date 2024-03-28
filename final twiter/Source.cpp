#include<iostream>
#include<string>
#include<fstream>
using namespace std;
void signup();
bool login();
void tweet();
void view_tweets();
string follower_name;
string user;
bool deci = false;
int main()
{
	string choice;

	cout << "---------- WELCOME TO SOCIAL LIGHT ----------" << endl;
	cout << endl;
	cout << "   PRESS [1] FOR SIGNUP   \n" << endl;
	cout << "   PRESS [2] FOR LOGIN   \n" << endl;
	cout << "Please Enter your choice :) ";
	cin >> choice;
	cout << endl;

	if (choice == "1")
	{

		signup();

		cout << "You Have signed up successfully" << endl;
		cout << " Now Login Again" << endl;
		system("pause");
		system("cls");
		main();
	}

	// LOGIN MODULE

	else if (choice == "2")
	{
		bool status = login();

		if (!status)
		{
			cout << "Invalid credentials, Try Again! " << endl;
			system("pause");
			system("cls");
			main();
		}

		else
		{
			cout << "Login Successful!" << endl;
			system("pause");
			system("cls");

		}

	}

	// CHECK FOR INVALID CHOICE

	else
	{
		cout << "You have entered wrong choice" << endl;
		system("pause");
		system("cls");
		main();
	}


	do
	{
		cout << "Current User : " << user;
		deci = false;
		string decision;
		cout << endl;
		cout << "--------------- MAIN MENU ---------------\n" << endl;
		cout << "What you want to do now??" << endl;
		cout << "Press [1] to enter ideas." << endl;
		cout << "Press [2] to follow others." << endl;
		cout << "Press [3] to view tweets." << endl;
		cout << "Press [4] to sign out." << endl;
		cout << "Enter your choice = ";
		cin >> decision;
		cout << endl;
		system("cls");
		if (decision == "1")
		{
			tweet();
		}

		else if (decision == "2")
		{
			cout << "--------------- FOLLOW OTHERS ---------------\n" << endl;
			char follow_choice;
			//string follower_name;
			cout << "Do you want to follow someone (Y/N) ??";
			cin >> follow_choice;
			if (follow_choice == 'y' || follow_choice == 'Y')
			{
				cout << "Please enter the name of user = ";
				cin >> follower_name;
				ifstream read("user.txt");
				string	folllow_check;
				while (read.peek() != EOF && (folllow_check != follower_name))
				{

					read >> folllow_check;
				}


				if (folllow_check == user)
				{
					cout << "You cannot follow yourself" << endl;
				}

				else if (folllow_check == follower_name)
				{
					cout << "Username exists" << endl;
					cout << "You are now following " << follower_name << endl;
					ofstream follwer("follwer.txt", ios::app);
					follwer << user << " " << follower_name << endl;
					ofstream follwer2(user + ".txt", ios::app);
					follwer2 << follower_name << endl;
				}
				else
				{
					cout << "Username does not exist" << endl;
				}
			}

		}

		else if (decision == "3")
		{
			view_tweets();
		}

		else if (decision == "4")
		{
			cout << "Thanks for using SOCIAL LIGHT." << endl;
			break;
			exit(0);
			deci = true;

		}

		else
		{
			cout << "Due to wrong entry of choice, You are signed out of your account." << endl;
			cout << "Please login again" << endl;
			system("pause");
			system("cls");
			main();
		}
	} while (deci == false);


	system("pause");
	return 0;
}

void signup()
{
	string username, password;
	bool flag = false;

	do
	{
		flag = false;
		cout << "NOTE: Minimun length should be 4 characters and have no spaces and special characters." << endl;
		cout << "Select a username : ";
		cin.ignore();
		getline(cin, username);
		int username_length = username.length();
		ifstream read("user.txt");
		while (read.peek() != EOF && (user != username))

			read >> user;

		// CHECK FOR ALREADY EXISTENCE

		if (user == username)
		{
			cout << "Username Already Exists" << endl;
			flag = true;
		}

		// CHECK FOR USERNAME LENGTH

		else if (username_length < 4)
		{
			cout << "Username length is insufficient. You username should contain atleast 4 Characters " << endl;;
			flag = true;
		}

		// CHECK FOR SPACE IN USERNAME

		for (int i = 0; i < username_length; i++)
		{
			if (isspace(username[i]))
			{
				cout << "Your Username contain spaces, which is not acceptable" << endl;
				flag = true;
			}

		}
	} while (flag == true);

	//PASSWORD SELECTION

	bool len = false;
	do
	{
		len = false;
		cout << "NOTE: Minimun length should be 5 characters and have no spaces." << endl;
		cout << "Create a password : ";
		getline(cin, password);
		int password_length = password.length();

		// CHECK FOR PASSWORD LENGTH

		if (password_length < 5)
		{
			cout << "Your password is of in sufficient length" << endl;
			cout << "Please enter it again" << endl;
			len = true;

		}
		for (int i = 0; i < password_length; i++)
		{
			if (isspace(password[i]))
			{
				cout << "Your password contain spaces, which is not acceptable" << endl;
				len = true;
			}

		}
	} while (len == true);

	// FILE WRITING FOR USER

	ofstream userfile;
	userfile.open("user.txt", ios::app);

	// WRITING USERNAME AND PASSWORD IN FILE

	userfile << username << " " << password << endl;
	userfile.close();
}

bool login()
{
	string username, password, pass;
	bool flag = false;

	cout << "Enter Username : ";
	cin.ignore();
	getline(cin, username);
	cout << "Enter Password : ";
	getline(cin, password);

	ifstream read("user.txt");
	while (read.peek() != EOF)//&& (user != username && pass != password))
	{
		read >> user >> pass;

		if (user == username && pass == password)
		{
			return 1;
		}
		else
		{
			flag = true;
		}

	}
	if (flag)
	{
		return 0;
	}
	read.close();
}

void tweet()
{
	cout << "--------------- IDEA EXPRESS ---------------\n" << endl;
	ofstream mytweetfile("tweet.txt", ios::app);
	int length = 0;
	char tweet_num;
	char input;
	string tweet;
	bool check = true;
	// TWEET WRITING
	while (check == true)
	{

		cout << "Please express your IDEA :";
		cin.get();
		getline(cin, tweet);
		length = tweet.size();
		cout << endl;
		// CHECK FOR TWEET LENGTH

		if (length > 180)
		{
			cout << "Your IDEA contains more than 180 characters. " << endl;
			cout << "Do you want to print it to 180 characters (Y/N) = ";
			cin >> input;
			if (input == 'Y' || input == 'y')
			{
				tweet.resize(180);
				mytweetfile << user << endl;
				mytweetfile << tweet << " (An IDEA by " << user << " )" << endl;
			}
			else
			{
				cout << "Sorry, We cannot write your IDEA in the file. " << endl;
			}
		}

		if (length <= 180)
		{
			mytweetfile << user << endl;
			//mytweetfile << tweet << endl;
			mytweetfile << tweet << " (An IDEA by " << user << " )" << endl;
		}

		// CHOICE TO ENTER MORE TWEET

		cout << "Do you want to express more IDEA (Y/N) ?? ";
		cin >> tweet_num;
		//cin.get();
		if (tweet_num == 'y' || tweet_num == 'Y')
		{
			check = true;
		}

		else
		{
			check = false;
			system("cls");
		}
	}
}

void view_tweets()
{
	cout << "--------------- IDEAS ---------------\n" << endl;
	ifstream mytweetfile2;
	mytweetfile2.open("tweet.txt");

	if (!mytweetfile2)
	{
		cout << "File doesn’t exist ";
	}

	else
	{
		ifstream read2;
		read2.open(user + ".txt");
		string user_follower;
		string tweet_written;

		//Followers Tweets
		cout << "-------------- Followers IDEAS ------------\n" << endl;
		while (read2.peek() != EOF)
		{

			getline(read2, user_follower);
			mytweetfile2.close();
			mytweetfile2.open("tweet.txt");
			while (mytweetfile2.peek() != EOF)
			{
				getline(mytweetfile2, tweet_written);
				if (tweet_written == user_follower)
				{
					getline(mytweetfile2, tweet_written);
					cout << tweet_written << endl;

				}
			}
		}
		mytweetfile2.close();

		//NON Followers Tweets
		cout << "-------------- Non Followers IDEA ------------\n" << endl;
		mytweetfile2.open("tweet.txt");
		while (mytweetfile2.peek() != EOF)
		{
			bool flag = true;
			getline(mytweetfile2, tweet_written);
			read2.close();
			read2.open(user + ".txt");
			while (read2.peek() != EOF)
			{
				getline(read2, user_follower);
				if (tweet_written == user_follower)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				getline(mytweetfile2, tweet_written);
				cout << tweet_written << endl;
			}
			else
			{
				getline(mytweetfile2, tweet_written);
			}
		}

		mytweetfile2.close();

	}
}