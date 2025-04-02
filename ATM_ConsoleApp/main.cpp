#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

enum enATM
{
	eQuickWithdraw = 1,
	eNormalWithdraw = 2,
	eDeposit = 3,
	eCheckBalance = 4,
	eLogout = 5
};

enum enQuickWithdraw
{
	e20 = 1,
	e50 = 2,
	e100 = 3,
	e200 = 4,
	e400 = 5,
	e600 = 6,
	e800 = 7,
	e1000 = 8,
	eExit = 9
};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

void ClearScreen()
{
	system("cls");
}

string ReadString(string Message = "Please enter a text\n", bool IgnoreEnterPress = 0, bool FirstInLoop = 0)
{
	string Text;
	cout << Message;
	if (FirstInLoop && IgnoreEnterPress)
	{
		cin.ignore(1, '\n');
		getline(cin >> ws, Text);
		return Text;
	}
	if (FirstInLoop)
	{
		getline(cin >> ws, Text);
		return Text;
	}
	if (IgnoreEnterPress)
	{
		cin.ignore(1, '\n');
		getline(cin, Text);
	}
	else
	{
		getline(cin, Text);
	}
	return Text;
}

double ReadDouble(string Message = "Please enter a valid number\n")
{
	double Number = 0;

	cout << Message;
	cin >> Number;

	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Number, Enter a valid one:" << endl;
		cin >> Number;
	}

	return Number;
}

double ReadIntToWithdraw(string Message = "Please enter a valid number\n")
{
	int Number = 0;

	cout << Message;
	cin >> Number;

	while (cin.fail() || cin.peek() != '\n' || Number % 5 != 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Number, Enter a valid one:" << endl;
		cin >> Number;
	}

	return Number;
}

short ReadValidateShortInRange(string Message, short From, short To)
{
	short Number;
	cout << Message;
	cin >> Number;
	while ((!(Number >= From && Number <= To)) || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Number\n";
		cout << Message;
		cin >> Number;
	}
	return Number;
}

void PrintATMScreen()
{
	cout << "\n==========================================\n";
	cout << "           ATM Main Menu Screen           ";
	cout << "\n==========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "==========================================\n";
}

enATM ReadMainMenu(string Message = "Choose what do you want to do? [1 to 5]?  ")
{
	return (enATM)ReadValidateShortInRange(Message, 1, 5);
}

enQuickWithdraw ReadQuickWithdraw(string Message = "\n\nChoose what do you want to do? [1 to 8]?  ")
{
	return (enQuickWithdraw)ReadValidateShortInRange(Message, 1, 9);
}

vector<string> SplitEachWordToVector(string Text, string Separator = "#//#")
{
	vector<string> vContent;
	short Pos = 0;
	string sWord;
	while ((Pos = Text.find(Separator)) != std::string::npos)
	{
		sWord = Text.substr(0, Pos);
		if (sWord != "")
		{
			vContent.push_back(sWord);
		}
		Text.erase(0, Pos + Separator.length());
	}
	if (Text != "")
	{
		vContent.push_back(Text);
	}
	return vContent;
}

stClient AssignEachPartToClientsStruct(string Text, string Separator = "#//#")
{
	vector<string> vString = SplitEachWordToVector(Text, Separator);
	stClient Client;
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}

vector<stClient> LoadClientsDataFromFileToStVector(string FileName)
{
	fstream File;
	vector<stClient> vClients;
	stClient sClient;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			sClient = AssignEachPartToClientsStruct(Line, "#//#");
			vClients.push_back(sClient);
		}
		File.close();
	}
	return vClients;
}

bool CheckClientByAccountNumber(vector<stClient> vClients, string AccountNumber, stClient& sClient)
{
	for (stClient Client : vClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			sClient = Client;
			return true;
		}
	}
	return false;
}

void PrintClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccount Number  : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

string ConvertClientRecordToLine(stClient Client, string Separator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

vector<stClient> SaveClientsDataToFile(string ClientsFileName, vector<stClient>& vClients)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			DataLine = ConvertClientRecordToLine(C, "#//#");
			MyFile << DataLine << endl;
		}
		MyFile.close();
	}
	return vClients;
}

void Deposit(string FileName, vector<stClient>& vClients, stClient& sClient)
{
	ClearScreen();
	cout << "\n================================\n";
	cout << "         Deposit Screen         ";
	cout << "\n================================\n";

	double AmountOfDeposit, EndAmount;
	char Ans;

	AmountOfDeposit = ReadDouble("\n\nEnter a Deposit Amount ");
	cout << "Are you sure you want to deposit " << AmountOfDeposit << " to your Account? (Y/n)  ";
	cin >> Ans;
	if (Ans == 'y' || Ans == 'Y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == sClient.AccountNumber)
			{
				C.AccountBalance += AmountOfDeposit;
				EndAmount = C.AccountBalance;
				vClients = SaveClientsDataToFile(FileName, vClients);
				cout << "\nDeposit Added Successfully Account balance = " << EndAmount << "\n";
				sClient.AccountBalance = EndAmount;
				break;
			}
		}
	}
	else
	{
		cout << "\nNo Deposit Added\n";
	}
}

void NormalWithdraw(string ClientsFileName, vector<stClient>& vClients, stClient& sClient)
{
	ClearScreen();
	cout << "\n================================\n";
	cout << "         Withdraw Screen         ";
	cout << "\n================================\n";

	double AmountOfWithdraw, EndAmount;
	char Ans;

	do
	{
		AmountOfWithdraw = ReadIntToWithdraw("\n\nEnter a Withdraw Amount ");
		if (AmountOfWithdraw > sClient.AccountBalance)
		{
			cout << "Maximum amount you can withdraw is " << sClient.AccountBalance << " \n";
		}
		else
		{
			cout << "Are you sure you want to  Withdraw " << AmountOfWithdraw << " to your Account? (Y/n)  ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y')
			{
				for (stClient& C : vClients)
				{
					if (C.AccountNumber == sClient.AccountNumber)
					{
						C.AccountBalance = C.AccountBalance - AmountOfWithdraw;
						EndAmount = C.AccountBalance;
						vClients = SaveClientsDataToFile(ClientsFileName, vClients);
						cout << "\n Withrawend Successfully Account balance = " << EndAmount << "\n";
						sClient.AccountBalance = EndAmount;
						break;
					}
				}
			}
			else
			{
				cout << "\nNo Withdraw Added\n";
				break;
			}
		}
	} while (AmountOfWithdraw > sClient.AccountBalance);
}

void PrintQuickWithdrawList()
{
	cout << "\n================================\n";
	cout << "         Quick Withdraw         ";
	cout << "\n================================\n";
	cout << "\t[1] 20      [2] 50\n";
	cout << "\t[3] 100     [4] 200\n";
	cout << "\t[5] 400     [6] 600\n";
	cout << "\t[7] 800     [8] 1000\n";
	cout << "\t[9] Exit";
	cout << "\n================================\n";
}

void Withdraw(string ClientsFileName, vector<stClient>& vClients, stClient& sClient, short AmountOfWithdraw)
{

	double EndAmount;
	char Ans;

	do
	{
		if (AmountOfWithdraw > sClient.AccountBalance)
		{
			cout << "Maximum amount you can withdraw is " << sClient.AccountBalance << " \n";
		}
		else
		{
			cout << "Are you sure you want to  Withdraw " << AmountOfWithdraw << " to your Account? (Y/n)  ";
			cin >> Ans;
			if (Ans == 'y' || Ans == 'Y')
			{
				for (stClient& C : vClients)
				{
					if (C.AccountNumber == sClient.AccountNumber)
					{
						C.AccountBalance = C.AccountBalance - AmountOfWithdraw;
						EndAmount = C.AccountBalance;
						vClients = SaveClientsDataToFile(ClientsFileName, vClients);
						cout << "\n Withrawid Successfully Account balance = " << EndAmount << "\n";
						sClient.AccountBalance = EndAmount;
						break;
					}
				}
			}
			else
			{
				cout << "\nNo Withdraw Added\n";
				break;
			}
		}
	} while (AmountOfWithdraw > sClient.AccountBalance);
}

void ATMProcedures(string ClientsFileName, vector<stClient>& vClients, stClient& sClient);

void QuickWithdraw(string ClientsFileName, vector<stClient>& vClients, stClient& sClient)
{
	ClearScreen();
	PrintQuickWithdrawList();
	cout << "Your Balance is " << sClient.AccountBalance;
	short AmountOfWithdraw = 0;
	enQuickWithdraw Choice;
	Choice = ReadQuickWithdraw();

	switch (Choice)
	{
	case enQuickWithdraw::e20:
		AmountOfWithdraw = 20;
		break;
	case enQuickWithdraw::e50:
		AmountOfWithdraw = 50;
		break;
	case enQuickWithdraw::e100:
		AmountOfWithdraw = 100;
		break;
	case enQuickWithdraw::e200:
		AmountOfWithdraw = 200;
		break;
	case enQuickWithdraw::e400:
		AmountOfWithdraw = 400;
		break;
	case enQuickWithdraw::e600:
		AmountOfWithdraw = 600;
		break;
	case enQuickWithdraw::e800:
		AmountOfWithdraw = 800;
		break;
	case enQuickWithdraw::e1000:
		AmountOfWithdraw = 1000;
		break;
	default:
		ATMProcedures(ClientsFileName, vClients, sClient);
		break;
	}
	Withdraw(ClientsFileName, vClients, sClient, AmountOfWithdraw);
}

bool CheckCorrectPinCode(stClient Client, string Password)
{
	return Password == Client.PinCode;
}

void LoginScreen(string ClientsFileName, vector<stClient>& vClients, stClient& Client)
{
	cout << "\n==========================================\n";
	cout << "               Login Screen               ";
	cout << "\n==========================================\n";
	vClients = LoadClientsDataFromFileToStVector(ClientsFileName);

	Client.AccountNumber = ReadString("Enter Account Number ? ");
	while (!CheckClientByAccountNumber(vClients, Client.AccountNumber, Client))
	{
		cout << Client.AccountNumber << " Invalid Account Number\n";
		Client.AccountNumber = ReadString("Enter Account Number? ");
	}

	string Password = ReadString("Enter Pin Code? ");
	while (!CheckCorrectPinCode(Client, Password))
	{
		cout << "Incorrect Pin Code\n";
		Password = ReadString("Enter Pin Code? ");
	}
}

void Login(string ClientsFileName, vector<stClient>& vClients, stClient& sClient);

void CheckBalance(stClient Client)
{
	ClearScreen();
	cout << "\nYour account balance is : " << Client.AccountBalance << endl;
}

void ATMProcedures(string ClientsFileName, vector<stClient>& vClients, stClient& sClient)
{
	enATM Choice;
	do
	{
		ClearScreen();
		PrintATMScreen();
		Choice = ReadMainMenu();
		switch (Choice)
		{
		case enATM::eQuickWithdraw:
			QuickWithdraw(ClientsFileName, vClients, sClient);
			cout << "\nPress Enter to go to main menu  ";
			cin.get();
			cin.get();
			break;
		case enATM::eNormalWithdraw:
			NormalWithdraw(ClientsFileName, vClients, sClient);
			cout << "\nPress Enter to go to main menu  ";
			cin.get();
			cin.get();
			break;
		case enATM::eDeposit:
			Deposit(ClientsFileName, vClients, sClient);
			cout << "\nPress Enter to go to main menu  ";
			cin.get();
			cin.get();
			break;
		case enATM::eCheckBalance:
			CheckBalance(sClient);
			cout << "\nPress Enter to go to main menu  ";
			cin.get();
			cin.get();
			break;
		default:
			Choice = enATM::eLogout;
			break;
		}
	} while (Choice != enATM::eLogout);
	cin.get();
	Login(ClientsFileName, vClients, sClient);
}

void Login(string ClientsFileName, vector<stClient>& vClients, stClient& sClient)
{
	ClearScreen();
	LoginScreen(ClientsFileName, vClients, sClient);
	ATMProcedures(ClientsFileName, vClients, sClient);
}

int main()
{
	string ClientsFileName = "Clients.txt";
	vector<stClient> vClients = LoadClientsDataFromFileToStVector(ClientsFileName);
	stClient Client;

	Login(ClientsFileName, vClients, Client);

	return 0;
}
