#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Struct to store account information
struct Account {
    string user;
    string pass;
};

// Function prototypes
int login();
int registerAccount(Account* input);
int insideAccount(const string& username);
int writeMessage(const string& sender);
int readMessages(const string& username);

int main()
{
    char menuChoice = '0';
    Account input;

    do {
        system("CLS");

        cout << "\n\t\t Messenger\n\t\t____________\n";
        cout << "\t\t 1. Login \n\t\t 2. Register\n\t\t 3. Exit\n\t\t____________\n\t   ";
        cout << "Enter your selection : ";
        cin >> menuChoice;

        if (menuChoice == '3') {
            return 0;
        }

        //loop keeps running if user input is invalid
        while (menuChoice != '1' && menuChoice != '2') {
            cout << "\t   Error: Invalid user input\n\t\t";
            cin >> menuChoice;
        }

        if (menuChoice == '1') {
            login();
        }
        else if (menuChoice == '2') {
            registerAccount(&input);
        }

        menuChoice = '0';
    } while (menuChoice == '0');
    /* the while condition above loops the menu display 
    after returning from login or register function */

    return 0;
}

int login()
{
    system("CLS");

    string username, password;
    cout << "\n\t\tUsername: ";
    cin >> username;
    cout << "\t\tPassword: ";
    cin >> password;
    cout << "\t\t________________";

    ifstream file("account_data.txt");
    string line;
    bool confirmUsername = false, confirmPassword = false;

    if (!file) {
        cout << "\n\t\tUser data file not found\n\t\tYou have to create an account first\n\t\t";
        system("pause");
        return 0;
    }

    //gets one line from file and compares it with username input
    while (confirmUsername == false && getline(file, line)) {
        if (line == username) {
            confirmUsername = true;
        }
    }

    //once username is found this check the password which is in the line after username
    if (getline(file, line) && line == password) {
        confirmPassword = true;
    }
    else {
        cout << "\n\t     Account not found\n\t   ";
        system("pause");
    }

    //calls inside the account function after confirming username and password
    if (confirmUsername == true && confirmPassword == true) {
        cout << "\n\t\tLogin confirm\n\t\tWelcome " << username << "\n\n\t   ";
        system("pause");
        system("CLS");
        insideAccount(username);
    }

    file.close();
    return 0;
}

int registerAccount(Account* input)
{
    system("CLS");
    cout << "\n\t\tUsername: ";
    cin >> input->user;
    cout << "\t\tPassword: ";
    cin >> input->pass;
    cout << "\t_______________________________";

    //appends new username password to file
    ofstream accountData;
    accountData.open("account_data.txt", ios::app);
    accountData << input->user << '\n' << input->pass << '\n';
    accountData.close();

    cout << "\n\tAccount successfully registered\n\t";
    system("pause");

    return 0;
}

int insideAccount(const string& username)
{
    char choice = '0';

    do {
        cout << "\n\t\tAccount: " << username << "\n\t\t________________";
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

        //calls functions for reading and writing message
        system("CLS");
        if (choice == '1') {
            writeMessage(username);
        }
        else if (choice == '2') {
            readMessages(username);
        }
    } while (choice == '1' || choice == '2');

    return 0;
}

int writeMessage(const string& sender)
{
    system("CLS");

    string receiver, text;
    cout << "\n\t\tEnter recipient's username: ";
    cin >> receiver;
    cout << "\n\t\tEnter your message: \n\t\t";

    // getline will not work without cin.ignore() before it to clean input buffer
    cin.ignore();
    getline(cin, text);

    //saves sender's username, recipient's username and message in a program readable format
    ofstream file("Messages.txt", ios::app);
    file << receiver << '\n' << "Message from " << sender << ": " << text << '\n';
    file.close();

    cout << "\n\t\t______________________________";
    cout << "\n\t\tMessage delivered successfully\n\t\t";
    system("pause");
    system("CLS");

    return 0;
}

int readMessages(const string& username)
{
    system("CLS");
    ifstream file("Messages.txt");

    bool noMessages = true;
    string line;

    if (!file) {
        cout << "\n\t\tMessages file not found. No messages available.\n\t\t";
        system("pause");
        system("CLS");
        return 0;
    }

    cout << "\n\t\t__________________________________________________________________________\n";

    while (getline(file, line)) {
        if (username == line) {
            noMessages = false;
            getline(file, line);
            cout << "\t\t" << line << endl;
            cout << "\t\t__________________________________________________________________________\n";
        }
    }

    if (noMessages) {
        cout << "\n\t\tNo messages available\n";
    }

    cout << "\n\t\t";
    system("pause");
    system("CLS");

    return 0;
}
