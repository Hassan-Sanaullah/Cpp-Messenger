#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct account {
	string user;
	string pass;
};

int login();
int Register(account input);
int inside_account(string username_input);
int write_messages(string sender);
int read_messages(string username_input);

int main()
{
	char menu_choice = '0';
	account input;

	do {
		system("CLS");

		cout << "\n\t\t Messenger\n\t\t____________\n";
		cout << "\t\t 1. Login \n\t\t 2. Register\n\t\t 3. Exit\n\t\t____________\n\t   ";
		cout << "Enter your selection : ";
		cin >> menu_choice;

		if (menu_choice == '3') {
			return 0;
		}
		//loop for invalid input
		while (menu_choice != '1' && menu_choice != '2') {
			cout << "\t   Error: Invalid user input\n\t\t";
			cin >> menu_choice;
		}

		//main menu input
		if (menu_choice == '1') {
			login();
		}
		else if (menu_choice == '2') {
			Register(input);
		}
		menu_choice = '0';
	} while (menu_choice == '0');


}

int login()
{
	system("CLS");

	string username_input, password_input;
	cout << "\n\t\tUsername: ";
	cin >> username_input;
	cout << "\t\tPassword: ";
	cin >> password_input;
	cout << "\t\t________________";

	ifstream file("User_data.txt");
	string line;

	//checks if user data file is available
	if (!file) {
		cout << "\n\t\tuser data file not found\n\t\tyou have to create an account first\n\t\t";
		system("pause");
		return 0;
	}

	//confirms username and password
	bool confirm_username = 0, confirm_password = 0;

	while (confirm_username == 0 && !file.eof()) {
		getline(file, line);
		if (line == username_input) {
			confirm_username = 1;

		}
	}
	getline(file, line);
	if (line == password_input) {
		confirm_password = 1;
	}
	else {
		cout << "\n\t     Account not found\n\t   ";
		system("pause");
	}
	
	if (confirm_username == 1 && confirm_password == 1) {

		cout << "\n\t\tLogin confirm\n\t\tWelcome  " << username_input << "\n\n\t   ";
		system("pause");
		system("CLS");
		inside_account(username_input);

	}
	
	file.close();
	return 0;
}

int Register(account input)
{
	;
	system("CLS");
	cout << "\n\t\t Username: ";
	cin >> input.user;
	cout << "\t\t Password: ";
	cin >> input.pass;
	cout << "\t_______________________________";

	ofstream Data;
	Data.open("User_data.txt", ios::app);
	Data << input.user << endl << input.pass << endl;
	Data.close();

	cout << "\n\tAccount successfully registered\n\t";
	system("pause");

	return 0;
}

int inside_account(string username_input)
{
	char choice = '0';

	do {
		cout << "\n\t\tAccount:  " << username_input << "\n\t\t________________";
		cout << "\n\t\tChoose an option\n\n\t     1. Write a new message\n\t     2. View your messages\n\t     3. Log out\n\t     ______________________\n\t     ";
		cin >> choice;

		if (choice == '3') {
			return 0;
		}

		//while loop for invalid input
		while (choice != '1' && choice != '2') {
			cout << "\t\tError: Invalid input\n\t\t";
			cin >> choice;
		}

		//calls functions for reading and writing
		system("CLS");
		if (choice == '1') {
			write_messages(username_input);
		}
		else if (choice == '2') {
			read_messages(username_input);
		}
	} while (choice == '1' || choice == '2');

	return 0;
}

int write_messages(string sender)
{
	system("CLS");

	string receiver, text;
	cout << "\n\t\tEnter recipient's username: ";
	cin >> receiver;
	cout << "\n\t\tEnter your message: \n\t\t";

	// getline will not work without cin.ignore() before it
	cin.ignore();
	getline(cin, text);

	//saves sender's username, recipient's username and message in a program readable format
	ofstream file;
	file.open("Messages.txt", ios::app);

	file << receiver << endl << "Message from " << sender << ":  " << text << endl;
	file.close();

	cout << "\n\t\t______________________________";
	cout << "\n\t\tMessage delivered successfully\n\t\t";
	system("pause");
	system("CLS");

	return 0;
}

int read_messages(string username_input)
{
	system("CLS");
	ifstream file("Messages.txt");

	bool no_messages = 1;

	//If messages file in not found
	if (!file) {
		cout << "\n\t\tMessages file not found. no messages available.\n\t\t";
		system("pause");
		system("CLS");
		return 0;
	}

	string line;
	cout << "\n\t\t__________________________________________________________________________\n";

	while (!file.eof()) {
		getline(file, line);
		if (username_input == line) {
			no_messages = 0;
			getline(file, line);
			cout << "\t\t" << line << endl;
			cout << "\t\t__________________________________________________________________________\n";
		}
	}

	if (no_messages == 1) {
		cout << "\n\t\tNo messages available\n";
	}

	cout << "\n\t\t";
	system("pause");
	system("CLS");
	return 0;
}
