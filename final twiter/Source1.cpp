#include <iostream>
#include<string>
#include<fstream>

using namespace std;

int main()
{
	int marks;
	ofstream myfile("userinfo.txt");
	for (int i = 0;i < 10; i++) 
	{
		cout << endl;
		cin >> marks;
	}
	myfile.close();

	cout << "your subjects marks are";
	ifstream read("userinfo.txt");
	while (read.peek() != EOF && marks != 0);
	{
		cout << endl << marks << endl;


		read.close();
	}


}