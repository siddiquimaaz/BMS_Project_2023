#include <iostream>  // Include the input/output stream library for standard I/O operations.
#include <string>    // Include the string library for string-related operations.
#include <conio.h>   // Include the conio.h header for _getch() function to read a single character from the console.
#include <stdio.h>   // Include the stdio.h header for standard input and output operations.
#include <stdlib.h>  // Include the stdlib.h header for general utility functions.
#include <windows.h> // Include the windows.h header for Windows-specific functions.
#include <ctime>     // Include the ctime header for time-related functions.
#include <cmath>     // Include the cmath header for mathematical functions.

#pragma warning(disable : 4996)// Disable warning 4996 (deprecated functions) to suppress certain compiler warnings.
using namespace std;


/*
* ============launching the functions that will ultimately be used throughout the application.(i.e: Declarations)(section-i)==============
*/
void startScreen(tm* tPtr);
void endScreen(tm* tPtr);
void bankEnterScreen(tm* tPtr, int& opt);
void screenBank(tm* tPtr, int& opt);
void screenATMone(tm* tPtr, long& userCardNumber, int& userPINnumber);
void screenATMtwo(tm* tPtr, int& opt);
void screenAdminOne(tm* tPtr, string& adminUserName, string& adminPassword);
void screenAdminTwo(tm* tPtr, int& opt);
void screenAdminAccountOpenings(tm* tPtr, int& opt);
void screenAdminBillPayments(tm* tPtr, int& opt);

/*
* ============== Omitting functions that are put into effect throughout the programme.(i.e: Declarations)(section-i)==================
*/


/*
===============Positioning up the functionality implementing classes and structures ( Section-ii)================
*/


/*<========Attention: Please refrain from rearranging the hierarchy of these parts, as doing so may cause some functions to become unclear.============>*/
struct payBillNode
{
	string billType;              // Holds the type of the bill (e.g., electricity, water).
	long billInvoiceNumber = 0;   // Initialize to 0.
	long double billAmount = 0.0;  // Initialize to 0.0.
	payBillNode* next = nullptr;   // Initialize to nullptr.
	payBillNode* prev = nullptr;   // Initialize to nullptr.

	// Constructor to initialize the members explicitly.
	payBillNode() : billInvoiceNumber(0), billAmount(0.0), next(nullptr), prev(nullptr) {}
};

class address
{
public:
	// Data members to store address information
	int houseNumber;
	string townName;
	int streetNumber;
	string city;

	// Constructor with default values for the address
	address(int hN = 0, string tN = "", int sN = 0, string c = "")
	{
		houseNumber = hN;
		townName = tN;
		streetNumber = sN;
		city = c;
	}

	// Method to set the address information
	void setAddress()
	{
		cout << "\t\t\t\t House# = ", cin >> houseNumber;
		cout << "\t\t\t\t Town Name = ", cin >> townName;
		cout << "\t\t\t\t Street# = ", cin >> streetNumber;
		cout << "\t\t\t\t City = ", cin >> city;
	}

	// Getter methods to retrieve individual components of the address
	int getHouseNumber()
	{
		return houseNumber;
	}

	int getStreetNumber()
	{
		return streetNumber;
	}

	string getCity()
	{
		return city;
	}

	string getTownName()
	{
		return townName;
	}

	// Method to display the complete address
	void displayAddress()
	{
		cout << "\t\t\t\t House# = " << houseNumber << endl;
		cout << "\t\t\t\t Town Name = " << townName << endl;
		cout << "\t\t\t\t Street# = " << streetNumber << endl;
		cout << "\t\t\t\t City = " << city << endl;
	}
};

struct newAccountNode
{
	// Structure to represent a node containing information for a new account

	// Personal information
	string firstName;
	string lastName;
	string accountStatus; // Active, inactive, etc.
	long long phoneNumber;
	long long CNIC; // Computerized National Identity Card number
	long double cash; // Account balance
	string emailAddress;

	// Home address information using the previously defined 'address' class
	address homeAddress;

	// Additional account features
	bool debitCard;
	bool chequeBook;
	int debitCardPin;

	// Login credentials
	string username;
	string password;

	// Account details
	long accountNumber;

	// Pointers to the next and previous nodes in the structure
	newAccountNode* next;
	newAccountNode* prev;
};

class billPaymentQueue
{
private:
	payBillNode* front;     // Pointer to the front of the bill payment queue.
	payBillNode* rear;      // Pointer to the rear of the bill payment queue.

public:
	// Constructor to initialize the front and rear pointers.
	billPaymentQueue()
	{
		front = rear = NULL;
	}

	// Checks if the bill payment queue is empty.
	bool isEmpty()
	{
		return (rear == NULL && front == NULL);
	}

	// Enqueues a new bill payment request to the queue.
	void enqueue()
	{
		payBillNode* temp = new payBillNode();  // Create a new payBillNode.
		char confirmation;                      // Variable to store user confirmation.

		// User inputs for bill details.
		cout << "\t\t\t\t Kindly write down your bill type from the following: Electricity, Gas, Internet -> ";
		cin >> temp->billType;
		cout << "\t\t\t\t Kindly write down the 10 digit Invoice Number -> ";
		cin >> temp->billInvoiceNumber;
		cout << "\t\t\t\t Kindly write down the bill amount -> ";
		cin >> temp->billAmount;

		// Display bill details for user confirmation.
		cout << "\t\t\t\t----------" << endl;
		cout << "\t\t\t\tBill Type : " << temp->billType << endl;
		cout << "\t\t\t\tBill Invoice# : " << temp->billInvoiceNumber << endl;
		cout << "\t\t\t\tBill Amount : " << temp->billAmount << endl;
		cout << "\t\t\t\t----------" << endl;
		cout << "\t\t\t\t Press 'Y' to confirm, or 'N' to exit" << endl;
		cout << "\t\t\t\t ", cin >> confirmation;
		temp->next = NULL;

		// Process user confirmation.
		if (confirmation == 'y' || confirmation == 'Y')
		{
			// Check if the queue is empty and adjust pointers accordingly.
			if (isEmpty())
			{
				temp->prev = NULL;
				front = rear = temp;
				cout << "\t\t\t\t Transaction Completed, Bill payment in process." << endl;
			}
			else
			{
				temp->prev = rear;
				rear->next = temp;
				rear = temp;
				cout << "\t\t\t\t Transaction Completed, Bill payment in process." << endl;
			}
		}
		else if (confirmation == 'n' || confirmation == 'N')
		{
			temp = NULL;
			cout << "\t\t\t\t Transaction not Completed." << endl;
		}
		else
		{
			cout << "\t\t\t\t ERROR ERROR ERROR!!! Wrong input entered, transaction failed!" << endl;
			temp = NULL;
		}

		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	// Dequeues the front bill payment request from the queue.
	void dequeue()
	{
		payBillNode* temp = front;

		// Check if the queue is empty.
		if (isEmpty())
		{
			cout << "\t\t\t\t Bill Payment Queue is empty, nothing left to process" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}
		else if (front == rear)
		{
			cout << "\t\t\t\t Bill# " << temp->billInvoiceNumber << " has been paid" << endl;
			front = rear = NULL;
		}
		else
		{
			front = front->next;
			cout << "\t\t\t\t Bill# " << temp->billInvoiceNumber << " has been paid." << endl;
		}

		delete temp;
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	// Displays all the bill payment requests in the queue.
	void displayBillPaymentQueue()
	{
		payBillNode* temp = front;

		// Check if the queue is empty.
		if (isEmpty())
		{
			cout << "\t\t\t\t Bill Payment Queue is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}

		int count = 0;

		// Display details of each bill payment request.
		while (temp != NULL)
		{
			cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl;
			cout << "\t\t\t\tBill Type : " << temp->billType << endl;
			cout << "\t\t\t\tBill Invoice# : " << temp->billInvoiceNumber << endl;
			cout << "\t\t\t\tBill Amount : " << temp->billAmount << endl;
			cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl << endl;
			temp = temp->next;
		}

		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	// Displays the details of the front bill payment request.
	void displayFront()
	{
		payBillNode* temp = front;

		// Check if the queue is empty.
		if (isEmpty())
		{
			cout << "\t\t\t\t Bill Payment Queue is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}
		cout << "\t\t\t\t------------------------------" << endl;
		cout << "\t\t\t\t----------" << endl;
		cout << "\t\t\t\tBill Amount: " << temp->billAmount << endl;
		cout << "\t\t\t\tBill Invoice#: " << temp->billInvoiceNumber << endl;
		cout << "\t\t\t\tBill Type: " << temp->billType << endl;
		cout << "\t\t\t\t------------------------------" << endl << endl;

		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}
};

class bankAccountsDatabase {
public:
	newAccountNode* head, * tail;

public:
	bankAccountsDatabase() { head = tail = NULL; }//constructor
	void insertNewAccount() {//New Account process
		newAccountNode* temp = new newAccountNode();

		char confirmation;
		int debitCardOpt = 0;
		int chequeBookOpt = 0;
		time_t t = time(NULL);//funtion of time
		tm* tPtr = localtime(&t);// function of time

		cout << "\t\t\t\t Kindly write down your First Name -> ";
		cin >> temp->firstName;
		cout << "\t\t\t\t Kindly write down your Last Name -> ";
		cin >> temp->lastName;
		cout << "\t\t\t\t Kindly write down your Email Address -> ";
		cin >> temp->emailAddress;
		cout << "\t\t\t\t Kindly write down your Home Address -> " << endl;
		temp->homeAddress.setAddress();
		cout << "\t\t\t\t Kindly write down your Phone Number -> ";
		cin >> temp->phoneNumber;
		cout << "\t\t\t\t Kindly write down your CNIC -> ";
		cin >> temp->CNIC;
		cout << "\t\t\t\t Do you want to get a Debit Card: write Yes(1) or No(0)-> ";
		cin >> debitCardOpt;

		if (debitCardOpt == 1) {
			temp->debitCard = true;
			cout << "\t\t\t\t Kindly write down your Debit Card PIN (4 Digits) -> ";
			cin >> temp->debitCardPin;
		}
		else if (debitCardOpt == 0) {
			temp->debitCard = false;
			temp->debitCardPin = 0;
			cout << "\t\t\t\t Debit card is set as No(0)" << endl;
		}
		else {
			temp->debitCard = false;
			temp->debitCardPin = 0;
			cout << "\t\t\t\t Invalid Option entered, debit card is set as No(N)" << endl;
		}
		cout << "\t\t\t\t Do you want to get a ChequeBook: write Yes(1) or No(0)-> ";
		cin >> chequeBookOpt;
		if (chequeBookOpt == 1) {
			temp->chequeBook = true;
		}
		else if (chequeBookOpt == 0) {
			temp->chequeBook = false;
		}
		else {
			cout << "\t\t\t\t Invalid Option entered, cheque book is set as No(N)" << endl;
		}

	TYPEAGAINUSNM://to show again this!
		cout << "\t\t\t\t Kindly write down your desired Username(NO Space Allowed) -> ";
		cin >> temp->username;

		if (checkUsernameClash(temp->username)) {
			cout << "\t\t\t\t Username has already been taken.!" << endl;
			goto TYPEAGAINUSNM;
		}
		cout << "\t\t\t\t Kindly write down your desired Password(NO Space Allowed) -> ";
		cin >> temp->password;
		system("cls");
		cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
		cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
		cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
		cout << "\t\t\t\t----------" << endl;
		cout << "\t\t\t\tFirst Name: " << temp->firstName << endl;
		cout << "\t\t\t\tLast Name: " << temp->lastName << endl;
		cout << "\t\t\t\tEmail Address: " << temp->emailAddress << endl;
		cout << "\t\t\t\tCNIC: " << temp->CNIC << endl;
		cout << "\t\t\t\tPhone#: " << temp->phoneNumber << endl;
		cout << "\t\t\t\t ---Address--- " << endl;
		temp->homeAddress.displayAddress();
		cout << "\t\t\t\t -------------" << endl;
		cout << "\t\t\t\tUsername: " << temp->username << endl;
		cout << "\t\t\t\tPassword: " << temp->password << endl;
		cout << "\t\t\t\tDebit Card: " << temp->debitCard << endl;
		cout << "\t\t\t\tCheque Book: " << temp->chequeBook << endl;
		cout << "\t\t\t\tDebit Card PIN: " << temp->debitCardPin << endl;
		cout << "\t\t\t\t Press 'Y' to confirm, or 'N' to exit" << endl;
		cout << "\t\t\t\t ", cin >> confirmation;
		temp->next = NULL;

		temp->accountStatus = "In Process";
		temp->accountNumber = 0;

		if (confirmation == 'y' || confirmation == 'Y') {
			if (head == NULL) {
				temp->prev = NULL;
				temp->cash = 900000;
				temp->accountStatus = "Completed"; // Set the account status to "Completed"
				temp->accountNumber = generateAccountNumber();
				head = tail = temp;
				cout << "\t\t\t\t Account Details Completed, in process now." << endl;
			}
			else {
				temp->cash = 900000;
				temp->accountStatus = "Completed"; // Set the account status to "Completed"
				temp->accountNumber = generateAccountNumber();
				temp->prev = tail;
				tail->next = temp;
				tail = temp;
				cout << "\t\t\t\t Account Details Completed, in process now." << endl;
			}
		}
		else if (confirmation == 'n' || confirmation == 'N') {
			temp = NULL;
			cout << "\t\t\t\t Account not Completed." << endl;
		}
		else {
			cout << "\t\t\t\t ERROR ERROR ERROR!!! Wrong input entered, account opening failed!" << endl;
			temp = NULL;
		}
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}//helper function
	bool isAccountNumberValid(long accountNumber) {
		newAccountNode* temp = head;
		while (temp != NULL) {
			if (temp->accountNumber == accountNumber) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	void viewAccountsToBeProcessed() {//helper function
		newAccountNode* temp = head;

		if (head == NULL) {
			cout << "\t\t\t\t Account Database is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}

		int count = 1;

		while (temp != NULL) {
			// Update the condition to handle both variations of account status
			if (temp->accountStatus == "In Process" || temp->accountStatus == "InProcess") {
				cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl;
				cout << "\t\t\t\t----------" << endl;
				cout << "\t\t\t\tFirst Name: " << temp->firstName << endl;
				cout << "\t\t\t\tLast Name: " << temp->lastName << endl;
				cout << "\t\t\t\tCNIC: " << temp->CNIC << endl;
				cin.ignore();
				cout << "\t\t\t\t ---Address--- " << endl;
				temp->homeAddress.displayAddress();
				cout << "\t\t\t\t -------------" << endl;
				cout << "\t\t\t\tUsername: " << temp->username << endl;
				cout << "\t\t\t\tPassword: " << temp->password << endl;
				cout << "\t\t\t\t--------------- #" << count << " ---------------" << endl << endl;
			}
			temp = temp->next;
		}
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	void processAccounts() {
		newAccountNode* temp = head;

		if (head == NULL) {
			cout << "\t\t\t\t Account Database is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}
		int count = 1;
		int opt;
		while (temp != NULL) {
			if (temp->accountStatus == "In Process" || temp->accountStatus == "InProcess") {
				cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl;
				cout << "\t\t\t\t----------" << endl;
				cout << "\t\t\t\tFirst Name: " << temp->firstName << endl;
				cout << "\t\t\t\tLast Name: " << temp->lastName << endl;
				cout << "\t\t\t\tCNIC: " << temp->CNIC << endl;
				cin.ignore();
				cout << "\t\t\t\t ---Address--- " << endl;
				temp->homeAddress.displayAddress();
				cout << "\t\t\t\t -------------" << endl;
				cout << "\t\t\t\tUsername: " << temp->username << endl;
				cout << "\t\t\t\tPassword: " << temp->password << endl;
				cout << "\t\t\t\t--------------- #" << count << " ---------------" << endl << endl;
				cout << "\t\t\t\t Do you want to process this account or not? Yes(1) No(0)" << endl;
				cin >> opt;
				if (opt == 1) {
					temp->accountStatus = "Completed";
					temp->accountNumber = generateAccountNumber();
				}
				else if (opt == 0) {
					// Correct the assignment here
					temp->accountStatus = "Declined";
				}
				else {
					cout << "\t\t\t\t Wrong option entered, account not completed nor declined." << endl;
				}
			}
			temp = temp->next;
		}
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}
	//check-in balance of number of accounts
	int countNodes() {
		int count = 0;

		if (head == NULL) {
			return count;
		}
		else {
			newAccountNode* temp = head;

			while (temp != NULL) {
				if (temp->accountStatus == "Completed") {
					count++;
				}
				temp = temp->next;
			}
			return count;
		}
	}//Generate Account number after 100775*
	long generateAccountNumber() {
		long accNumber = 1007750 + countNodes();

		return accNumber;
	}
	void deleteAccount(long accountNum) {
		newAccountNode* temp = head;
		newAccountNode* findAndDelete = nullptr;

		if (head == NULL) {
			cout << "\t\t\t\tAccount Database is empty, nothing is available to delete!!!!" << endl;
			return; // No need to proceed further if the list is empty
		}

		// Check if the head node needs to be deleted
		if (head->accountNumber == accountNum) {
			findAndDelete = head;
			head = head->next;
			if (head != NULL) {
				head->prev = NULL;
			}
			delete findAndDelete;
			cout << "\t\t\t\tAccount found in database and successfully deleted !!!!" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}

		// Iterate through the list to find the node to delete
		while (temp != NULL) {
			if (temp->accountNumber == accountNum) {
				findAndDelete = temp;
				temp->prev->next = temp->next;
				if (temp->next != NULL) {
					temp->next->prev = temp->prev;
				}
				delete findAndDelete;
				cout << "\t\t\t\tAccount found in database and successfully deleted !!!!" << endl;
				cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
				_getch();
				return;
			}
			temp = temp->next;
		}

		// If the function reaches this point, the account was not found
		cout << "\t\t\t\tAccount not found in database !!!!" << endl;
		_getch();
	}


	void depositCash(long accountNumber, long double amount) {
		newAccountNode* account = findAccount(accountNumber);

		if (account != nullptr) {
			// Update account balance
			account->cash += amount;
		}
	}

	// Function to withdraw cash from an account
	void withdrawCash(long accountNumber, long double amount) {
		newAccountNode* account = findAccount(accountNumber);

		if (account != nullptr && account->cash >= amount) {
			// Update account balance
			account->cash -= amount;
		}
	}

	//check-in balance of the number of completed accounts
	int countCompletedAccounts() {
		int count = 0;
		if (head == NULL) {
			return count;
		}
		else {
			newAccountNode* temp = head;

			while (temp != NULL) {
				if (temp->accountStatus == "Completed") {
					count++;
				}
				temp = temp->next;
			}
			return count;
		}
	}
	newAccountNode* checkIfAccountPresent(string usernm, string paswd) {
		newAccountNode* temp = head;
		while (temp != NULL) {
			// Check for matching username, password, and account status "Completed"
			if (temp->username == usernm && temp->password == paswd &&
				temp->accountStatus == "Completed") {
				cout << "\t\t\t\t Account found in Database." << endl;
				return temp;
			}
			temp = temp->next;
		}
		cout << "\t\t\t\t Account not found in Database." << endl;
		return nullptr;
	}

	// Helper function to find an account by account number
	newAccountNode* findAccount(long accountNumber) {
		newAccountNode* temp = head;

		while (temp != nullptr) {
			if (temp->accountNumber == accountNumber) {
				return temp;
			}
			temp = temp->next;
		}

		return nullptr; // Account not found
	}

	bool checkATMCredentials(int pn, long accNum) {
		if (head == NULL) {
			return false;
		}

		newAccountNode* temp = head;

		while (temp != NULL) {
			if (temp->debitCardPin == pn && temp->accountNumber == accNum &&
				temp->accountStatus == "Completed") {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool checkUsernameClash(string usernameEnt) {
		if (head == NULL) {
			return false;
		}

		newAccountNode* temp = head;

		while (temp != NULL) {
			if (temp->username == usernameEnt) {
				return true;
			}
			temp = temp->next;
		}

		return false;
	}
	//<============Withdraw-cash From ATM=============>

	void withDrawCash(string usernm, string paswd, long double amount) {
		newAccountNode* withDrawAcc = checkIfAccountPresent(usernm, paswd);

		if (withDrawAcc == NULL) {
			cout << "\t\t\t\tAccount not found in database, transaction failed !!!!" << endl;
		}
		else {
			if (amount > withDrawAcc->cash) {
				cout << "\t\t\t\tAccount does not contain this much cash, transaction failed !!!!" << endl;
				cout << "\t\t\t\tPress any key to return to Bank Menu" << endl;
				_getch();
				return;
			}

			withDrawAcc->cash = withDrawAcc->cash - amount;
			cout << "\t\t\t\tTransaction successful!" << endl;
			cout << "\t\t\t\tRemaining Balance -> " << withDrawAcc->cash << endl;
		}
		cout << "\t\t\t\tPress any key to return to Bank Menu" << endl;
		_getch();
	}
	void changeATMpin(string usernm, string paswd, int oldPin, int newPin) {

		newAccountNode* changePinAcc = checkIfAccountPresent(usernm, paswd);

		if (changePinAcc == NULL) {
			cout << "\t\t\t\tAccount not found in database, transaction failed !!!!" << endl;
		}
		else {
			if (newPin > 9999 || changePinAcc->debitCardPin != oldPin) {
				cout << "\t\t\t\tNew PIN is not 4 digits or Old PIN is invalid, process failed!!!!" << endl;
				return;
			}

			changePinAcc->debitCardPin = newPin;
			cout << "\t\t\t\tProcess successful!" << endl;
			cout << "\t\t\t\tPin Updated " << endl;
		}
		cout << "\t\t\t\tPress any key to return to Bank Menu" << endl;
		_getch();
	}
	void balanceEnquiry(string usernm, string paswd) {
		newAccountNode* balanceEnquiryAcc = checkIfAccountPresent(usernm, paswd);
		if (balanceEnquiryAcc == NULL) {
			cout << "\t\t\t\tAccount not found in database, process failed !!!!" << endl;
		}
		else {
			cout << "\t\t\t\tAccount# -> " << balanceEnquiryAcc->accountNumber << endl;
			cout << "\t\t\t\tBalance -> " << balanceEnquiryAcc->cash << endl;
		}
		cout << "\t\t\t\tPress any key to return to Bank Menu" << endl;
		_getch();
	}
	void displayAccountDetails(string usernm, string paswd) {
		newAccountNode* accountDisplay = checkIfAccountPresent(usernm, paswd);
		if (accountDisplay == NULL) {
			cout << "\t\t\t\tAccount not found in database, process failed !!!!" << endl;
		}
		else {
			cout << "\t\t\t\t------------------------------" << endl;
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\tAccount#: " << accountDisplay->accountNumber << endl;
			cout << "\t\t\t\tAccount Status: " << accountDisplay->accountStatus << endl;
			cout << "\t\t\t\tFirst Name: " << accountDisplay->firstName << endl;
			cout << "\t\t\t\tLast Name: " << accountDisplay->lastName << endl;
			cout << "\t\t\t\tEmail Address: " << accountDisplay->emailAddress << endl;
			cout << "\t\t\t\tCNIC: " << accountDisplay->CNIC << endl;
			cout << "\t\t\t\tPhone#: " << accountDisplay->phoneNumber << endl;
			cout << "\t\t\t\tCash: " << accountDisplay->cash << endl;
			cout << "\t\t\t\t ---Address--- " << endl;
			accountDisplay->homeAddress.displayAddress();
			cout << "\t\t\t\t -------------" << endl;
			cout << "\t\t\t\tUsername: " << accountDisplay->username << endl;
			cout << "\t\t\t\tPassword: " << accountDisplay->password << endl;
			cout << "\t\t\t\tDebit Card: " << accountDisplay->debitCard << endl;
			cout << "\t\t\t\tCheque Book: " << accountDisplay->chequeBook << endl;
			cout << "\t\t\t\tDebit Card PIN: " << accountDisplay->debitCardPin << endl;
			cout << "\t\t\t\t------------------------------" << endl << endl;
		}
		cout << "\t\t\t\tPress any key to return to Bank Menu" << endl;
		_getch();
	}
	void displayAllAccounts() {
		newAccountNode* temp = head;

		if (head == NULL) {
			cout << "\t\t\t\t Account Database is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}

		int count = 1;

		while (temp != NULL) {
			cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl;
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\tAccount Status: " << temp->accountStatus << endl;
			cout << "\t\t\t\tAccount Number: " << temp->accountNumber << endl;
			cout << "\t\t\t\tFirst Name: " << temp->firstName << endl;
			cout << "\t\t\t\tLast Name: " << temp->lastName << endl;
			cout << "\t\t\t\tEmail Address: " << temp->emailAddress << endl;
			cout << "\t\t\t\tCNIC: " << temp->CNIC << endl;
			cout << "\t\t\t\tPhone#: " << temp->phoneNumber << endl;
			cout << "\t\t\t\t ---Address--- " << endl;
			temp->homeAddress.displayAddress();
			cout << "\t\t\t\t -------------" << endl;
			cout << "\t\t\t\tUsername: " << temp->username << endl;
			cout << "\t\t\t\tPassword: " << temp->password << endl;
			cout << "\t\t\t\tDebit Card: " << temp->debitCard << endl;
			cout << "\t\t\t\tCheque Book: " << temp->chequeBook << endl;
			cout << "\t\t\t\tDebit Card PIN: " << temp->debitCardPin << endl;
			temp = temp->next;
		}
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}
};

struct withdrawDepositNode
{
	long accountNumber;            // Holds the account number for the transaction.
	long double cashAmount;        // Holds the amount of cash for the transaction.
	bool withdrawCash;             // Indicates whether it is a cash withdrawal transaction.
	bool depositCash;              // Indicates whether it is a cash deposit transaction.
	withdrawDepositNode* next;     // Pointer to the next node in the linked list.
	withdrawDepositNode* prev;     // Pointer to the previous node in the linked list.
};

class withdrawDepositQueue
{
private:
	withdrawDepositNode* front; // Pointer to the front of the queue
	withdrawDepositNode* rear;  // Pointer to the rear of the queue

public:
	withdrawDepositQueue()
	{
		front = rear = NULL; // Initializing front and rear pointers to NULL
	}

	bool isEmpty()
	{
		return (front == NULL && rear == NULL);
	}

	void enqueue(bankAccountsDatabase& accDatabase)
	{
		withdrawDepositNode* temp = new withdrawDepositNode(); // Create a new node for the queue

		int opt = 0;
		string flag = "";

		cout << "\t\t\t\t Kindly choose from the following two options: 1) Withdraw Cash or 2) Deposit Cash -> ";
		cin >> opt;

		// Set transaction type based on user input
		if (opt == 1)
		{
			temp->withdrawCash = true;
			temp->depositCash = false;
			flag = "Withdraw Cash";
		}
		else if (opt == 2)
		{
			temp->depositCash = true;
			temp->withdrawCash = false;
			flag = "Deposit Cash";
		}
		else
		{
			// Display an error message for invalid input and return
			cout << "\t\t\t\t Wrong option entered, press any key to return to menu." << endl;
			_getch();
			delete temp;  // Free memory occupied by the new node
			return;
		}

		char confirmation;

		// Gather information from the user
		cout << "\t\t\t\t Kindly write down the 10 digit Account Number -> ";
		cin >> temp->accountNumber;

		// Check if the account number exists in the database
		if (!accDatabase.isAccountNumberValid(temp->accountNumber))
		{
			cout << "\t\t\t\t Account does not exist, transaction failed!" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			delete temp; // Free memory occupied by the new node
			return;
		}

		cout << "\t\t\t\t Enter the cash amount: ";
		cin >> temp->cashAmount;

		// Link the new node into the queue
		temp->next = NULL;
		if (isEmpty())
		{
			// If the queue is empty, set both front and rear to the new node
			front = rear = temp;
		}
		else
		{
			// If the queue is not empty, link the new node to the rear and update the rear pointer
			rear->next = temp;
			rear = temp;
		}

		// Update account balance in the database
		if (opt == 1)
		{
			// Withdrawal
			accDatabase.withdrawCash(temp->accountNumber, temp->cashAmount);
		}
		else if (opt == 2)
		{
			// Deposit
			accDatabase.depositCash(temp->accountNumber, temp->cashAmount);
		}

		cout << "\t\t\t\t Transaction added to the Withdraw/Deposit Queue." << endl;
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	void dequeue(bankAccountsDatabase& accDatabase)
	{
		withdrawDepositNode* temp = front; // Get the front node

		if (isEmpty())
		{
			// Display a message if the queue is empty and return to the menu
			cout << "\t\t\t\t Withdraw/Deposit Queue is empty, nothing left to process" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}
		else if (front == rear)
		{
			// If there is only one node in the queue, display its information and update front and rear
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\t " << temp->accountNumber << endl;
			cout << "\t\t\t\t " << temp->cashAmount << endl;
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\t Transaction has been done." << endl;
			front = rear = NULL;
		}
		else
		{
			// If there are multiple nodes, update front and display information of the dequeued node
			front = front->next;
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\t " << temp->accountNumber << endl;
			cout << "\t\t\t\t " << temp->cashAmount << endl;
			cout << "\t\t\t\t----------" << endl;
			cout << "\t\t\t\t Transaction has been done." << endl;
		}

		// Update account balance in the database
		if (temp->withdrawCash)
		{
			// Withdrawal
			accDatabase.withdrawCash(temp->accountNumber, temp->cashAmount);
		}
		else if (temp->depositCash)
		{
			// Deposit
			accDatabase.depositCash(temp->accountNumber, temp->cashAmount);
		}

		// Free memory occupied by the dequeued node
		delete temp;
		cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
		_getch();
	}

	void displayWithdrawDepositQueue()
	{
		withdrawDepositNode* temp = front; // Get the front node

		if (isEmpty())
		{
			// Display a message if the queue is empty and return to the menu
			cout << "\t\t\t\t Withdraw/Deposit Payment Queue is empty" << endl;
			cout << "\t\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			return;
		}

		int count = 0;

		// Display information of each node in the queue
		while (temp != NULL)
		{
			cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl;
			cout << "\t\t\t\t " << temp->accountNumber << endl;
			cout << "\t\t\t\t " << temp->cashAmount << endl;
			cout << "\t\t\t\t Withdraw =" << temp->withdrawCash << endl;
			cout << "\t\t\t\t Deposit =" << temp->depositCash << endl;
			cout << "\t\t\t\t--------------- #" << count++ << " ---------------" << endl << endl;
			temp = temp->next;
		}
	}
};

class admin
{
private:
	const string username = "admin";
	const string password = "admin";
public:
	void viewAccountDetails(const newAccountNode* head)
	{
		const newAccountNode* temp = head;

		while (temp != nullptr)
		{
			// Display relevant account information here, e.g., account number and cash amount
			cout << "Account holder's First Name " << temp->firstName << "Account holder's Last Name " << temp->lastName << " Account Number: " << temp->accountNumber << ", Cash Amount: " << temp->cash << endl;

			temp = temp->next;
		}
	}
	string getUserName() const
	{
		return username;
	}
	string getPassWord() const
	{
		return password;
	}
	bool checkCredentials(string userNm, string passWd)
	{
		if (userNm == username && passWd == password)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

/*
===============Disarrange the functionality implementing classes and structures ( Section-ii)================
*/

/*<========Attention: Please refrain from rearranging the hierarchy of these parts, as doing so may cause some functions to become unclear.============>*/

/*Entry points of an application */
int main()
{
	time_t t = time(nullptr); // for time 
	tm* tPtr = localtime(&t);
	int bankEnterOption = 0; //Member variables for system
	int optionInBankOne = 0;
	int optionInBankTwo = 0;
	int optionInATMone = 0;
	int optionInATMtwo = 0;
	int optionInAdmin = 0;
	int optionInAdminAccOpen = 0;
	int optionInAdminBillPaymt = 0;
	long userCardNumber = 0;
	int userCardPIN = 0;
	string accountViewUsnm = "";
	string accountViewPaswd = "";
	string adminUserName;
	string adminPassword;
	int flag = 0;
	admin administrator;
	long double withdrawCash = 0.00;
	int oldPinChange = 0;
	int newPinChange = 0;
	bankAccountsDatabase accDatabase;
	billPaymentQueue billPaymentLine;
	withdrawDepositQueue withDwDepstLine;
	string usnmATM = "";
	string pssdATM = "";


	startScreen(tPtr);
	system("cls");

BANKSCREEN:bankEnterScreen(tPtr, bankEnterOption);
	system("cls");
	switch (bankEnterOption)
	{
	case 1:
	INSIDEBANK:screenBank(tPtr, optionInBankOne);
		system("cls");

		cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
		cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
		cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
		switch (optionInBankOne)
		{
		case 1:
			billPaymentLine.enqueue();
			system("cls");
			goto INSIDEBANK;
			break;
		case 2:
			withDwDepstLine.enqueue(accDatabase);
			system("cls");
			goto INSIDEBANK;
			break;
		case 3:
			accDatabase.insertNewAccount();
			system("cls");
			goto INSIDEBANK;
			break;
		case 4:
			cout << "\t\t\t Enter Username: ", cin >> accountViewUsnm, cout << endl;
			cout << "\t\t\t Enter Password: ", cin >> accountViewPaswd, cout << endl;
			accDatabase.displayAccountDetails(accountViewUsnm, accountViewPaswd);
			system("cls");
			goto INSIDEBANK;
			break;

		case 5: // Add a new case for account deletion
			long deleteAccountNum;
			cout << "\t\t\t Enter Account Number to Delete: ";
			cin >> deleteAccountNum;
			accDatabase.deleteAccount(deleteAccountNum);
			cout << "\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			system("cls");
			goto INSIDEBANK;
			break;
		case 6:
			system("cls");
			goto BANKSCREEN;
			break;
		default:
			system("cls");
			cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
			cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
			cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
			cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
			_getch();
			system("cls");
			goto INSIDEBANK;
			break;
		}
		break;
	case 2:
	MAINATMSCREEN:screenATMone(tPtr, userCardNumber, userCardPIN);
		system("cls");

		if (accDatabase.checkATMCredentials(userCardPIN, userCardNumber))
		{
		ATMSCREEN:screenATMtwo(tPtr, optionInATMtwo);
			system("cls");
			cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
			cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
			cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;

			switch (optionInATMtwo)
			{
			case 1:
				cout << "\t\t\t # Enter amount you wish to withdraw -> ", cin >> withdrawCash;
				cout << "\t\t\t # Enter your username -> ", cin >> usnmATM;
				cout << "\t\t\t # Enter your password -> ", cin >> pssdATM;
				accDatabase.withDrawCash(usnmATM, pssdATM, withdrawCash);
				system("cls");
				goto ATMSCREEN;
				break;
			case 2:
				cout << "\t\t\t # Enter your username -> ", cin >> usnmATM;
				cout << "\t\t\t # Enter your password -> ", cin >> pssdATM;
				accDatabase.balanceEnquiry(usnmATM, pssdATM);
				system("cls");
				goto ATMSCREEN;
				break;
			case 3:
				cout << "\t\t\t # Enter your username -> ", cin >> usnmATM;
				cout << "\t\t\t # Enter your password -> ", cin >> pssdATM;
				cout << "\t\t\t # Enter old pin -> ", cin >> oldPinChange;
				cout << "\t\t\t # Enter new pin (4 Digits) -> ", cin >> newPinChange;
				accDatabase.changeATMpin(usnmATM, pssdATM, oldPinChange, newPinChange);
				system("cls");
				goto ATMSCREEN;
				break;
			case 4:
				system("cls");
				goto BANKSCREEN;
				break;
			default:
				system("cls");
				cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
				cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
				cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
				cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
				_getch();
				system("cls");
				goto ATMSCREEN;
				break;
			}
		}
		else
		{
			cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
			cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
			cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
			cout << "\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			system("cls");
			goto BANKSCREEN;
		}
		break;
	case 3:
		screenAdminOne(tPtr, adminUserName, adminPassword);
		system("cls");
		if (administrator.checkCredentials(adminUserName, adminPassword))
		{
		ADMINSCREEN:screenAdminTwo(tPtr, optionInAdmin);
			system("cls");

			switch (optionInAdmin)
			{
			case 1:
			ACCOPPSCREN:screenAdminAccountOpenings(tPtr, optionInAdminAccOpen);
				system("cls");
				cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
				cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;

				cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
				switch (optionInAdminAccOpen)
				{
				case 1:
					accDatabase.viewAccountsToBeProcessed();
					system("cls");
					goto ACCOPPSCREN;
					break;
				case 2:
					accDatabase.processAccounts();
					system("cls");
					goto ACCOPPSCREN;
					break;
				case 3:
					accDatabase.displayAllAccounts();
					system("cls");
					goto ACCOPPSCREN;
				case 4:
					system("cls");
					goto ADMINSCREEN;
					break;
				default:
					system("cls");
					cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
					cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
					cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;


					cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
					_getch();
					system("cls");
					goto ACCOPPSCREN;
					break;
				}
			case 2:
			BILLPAYSCREEN:screenAdminBillPayments(tPtr, optionInAdminBillPaymt);
				system("cls");
				cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
				cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
				cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;


				switch (optionInAdminBillPaymt)
				{
				case 1:
					billPaymentLine.displayBillPaymentQueue();
					system("cls");
					goto BILLPAYSCREEN;
					break;
				case 2:
					billPaymentLine.displayFront();
					system("cls");
					goto BILLPAYSCREEN;
					break;
				case 3:
					billPaymentLine.dequeue();
					system("cls");
					goto BILLPAYSCREEN;
					break;
				case 4:
					system("cls");
					goto ADMINSCREEN;
					break;
				default:
					system("cls");
					cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
					cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
					cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;


					cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
					_getch();
					system("cls");
					goto BILLPAYSCREEN;
					break;
				}
				break;
			case 3:
				system("cls");
				goto BANKSCREEN;
				break;
			default:
				system("cls");
				cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
				cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
				cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
				cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
				_getch();
				system("cls");
				goto ADMINSCREEN;
				break;
			}
		}
		else
		{
			cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
			cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
			cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;


			cout << "\t\t\t # Invalid Credentials Added" << endl;
			cout << "\t\t\t Press any key to return to Bank Menu" << endl;
			_getch();
			system("cls");
			goto BANKSCREEN;
		}
		break;
	case 4:
		system("cls");
		endScreen(tPtr);
		break;
	default:
		system("cls");
		cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
		cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
		cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;


		cout << "\t\t\t  Wrong Option Entered, press any key to go back to Main Menu " << endl;
		_getch();
		system("cls");
		goto BANKSCREEN;
		break;
	}

	cout << "\t\t\t ", system("pause");
	return 0;
}

void startScreen(tm* tPtr)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t\tWelcome\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t\t  to\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;

	cout << "\t\t\t #" << "\t\t\t\t\t\t\t\t\t\t\t\tDeveloped  by\n \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Maaz Siddiqui, Zain Naved & Bilal Huzaifa" << endl;
	cout << "\t\t\t ";
	system("pause");
}

void endScreen(tm* tPtr)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t\tThank you\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t\tfor using\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;

	cout << "\t\t\t #" << "\t\t\t\t\t\t\t\t\t\t\t\tDeveloped  by Maaz, Zain, and Bilal Huzaifa  #" << endl;
}

void bankEnterScreen(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;

	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Enter Bank\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Enter ATM\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) Admin Login\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    4) Exit\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}

void screenBank(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t     Welcome to Bank\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Pay Bills\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Deposits/Cheques\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) Open up Account\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    4) View your Account\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    5) Delete your Account\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    6) Exit\t\t\t\t\t\t\t\t  #" << endl;

	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}

void screenATMone(tm* tPtr, long& userCardNumber, int& userPINnumber)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t     Welcome to ATM\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\tEnter Following Details:\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Account Number\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Debit Card PIN\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t Enter Account Number: ", cin >> userCardNumber, cout << endl;
	cout << "\t\t\t Enter Debit Card PIN: ", cin >> userPINnumber, cout << endl;
}

void screenATMtwo(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t     Welcome to ATM\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Withdraw Cash\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Balance Inquiry\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) Change Pin\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    4) Exit\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}

void screenAdminOne(tm* tPtr, string& adminUserName, string& adminPassword)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    Welcome to Admin\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\tEnter Following Details:\t\t\t\t\t #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Username\t\t\t\t\t\t\t\t #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Password\t\t\t\t\t\t\t#" << endl;
	cout << "\t\t\t Enter Username: ", cin >> adminUserName, cout << endl;
	cout << "\t\t\t Enter Password: ", cin >> adminPassword, cout << endl;
}
void screenAdminTwo(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    Welcome to Admin\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) Process Account Openings\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Process Bill Payments\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) Exit\t\t\t\t\t\t\t\t  #" << endl;

	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}
void screenAdminAccountOpenings(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\tWelcome to Account Openings\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) View Account Openings\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) Process Accounts\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) View Accounts in Database\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    4) Exit\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}
void screenAdminBillPayments(tm* tPtr, int& opt)
{
	cout << "\n\n\n\t\t\t Date: " << (tPtr->tm_mday) << "/" << (tPtr->tm_mon) + 1 << "/" << (tPtr->tm_year) + 1900 << endl;
	cout << "\t\t\t Time: " << (tPtr->tm_hour) << ":" << (tPtr->tm_min) << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t Horizon Union Bank Ltd.\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    Welcome to Bill Payments\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t   Choose an option:\t\t\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    1) View Bill Payments\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    2) View Bill Payment at Front\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    3) Process Bill Payment at Front\t\t\t\t          #" << endl;
	cout << "\t\t\t #" << "\t\t\t\t\t\t    4) Exit\t\t\t\t\t\t\t\t  #" << endl;
	cout << "\t\t\t Enter Option: ", cin >> opt, cout << endl;
}

/*Application's entry points has been terminated.*/