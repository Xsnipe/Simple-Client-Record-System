#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

int i = 0, j;
std::string Search;

void slowtype(const char text[], int time, bool endl_After) //Slow Type function
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		std::cout << text[i];
		Sleep(time);
	}
	if (endl_After) 
	{
		std::cout << std::endl;
	}
}

void ThreeDotLoading(int RepeatAmount, int speed) //Three dot loading animation function
{
	system("cls");
	for (; RepeatAmount != 0; RepeatAmount--)
	{
		std::cout << "\n\n\n\t\tWelcome\n\t\t   to\n\t     Client Records\n\n\n\n";
		slowtype("...", speed, false);
		system("cls");
	}
}

void TitleScreen() //Title screen animation function
{
	slowtype("\n\n\n\t\tWelcome\n\t\t   to\n\t     Client Records\n\n\n\n", 70, true);
	ThreeDotLoading(3, 300);
	system("cls");
}

void PrintMenu(std::vector<std::string> options, int choice, int ChoiceColor = 3, int AltColor = 7) //Prints a static Menu
{

	for (int i = 0; i < options.size(); i++)
	{
		if (i == (choice - 1))
		{
			SetConsoleTextAttribute(h, ChoiceColor);
			std::cout << "[> " << options[i] << std::endl;
			SetConsoleTextAttribute(h, 7);
		}
		else
		{
			std::cout << "[> " << options[i] << std::endl;
		}
	}
}

int ActiveMenu(std::vector<std::string> options, int ChoiceColor = 3, int AltColor = 7) //Interactive Menu
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int input_select = 1;
	int input = 0;
	int total = options.size();

	PrintMenu(options, input_select, ChoiceColor, AltColor);

	while (true)
	{
		input = _getch();

		if ((input == 72) && (input_select == 1))
		{
		}
		else if ((input == 80) && (input_select == total))
		{
		}
		else if (input == 80)
		{
			input_select++;
		}
		else if (input == 72)
		{
			input_select--;
		}
		else if (input == 13)
		{
			return input_select;
		}
		system("cls");
		PrintMenu(options, input_select, ChoiceColor, AltColor);
	}
}

struct Clients
{
	std::string FName;
	std::string LName;
	int ID;
	int IYear;
}ClientData;

void AddClient(std::string FirstName, std::string LastName, int ID, int InductionYear) //Adds Clients to Clients.txt
{
	std::ofstream file("Clients.txt",std::ios::app);
	file << ':' << FirstName << ':' << LastName << ':' << ID << ':' << InductionYear << std::endl;
	file.close();
}

std::vector<std::string> SearchClients(std::string FirstName) //Searches for Clients in Clients.txt
{
	std::ifstream input;
	input.open("Clients.txt");
	if (!input.is_open()) {
		exit(-1);
	}

	while (input)
	{

		std::string line;
		std::getline(input, line, ':');


		if (!input)
		{
			ClientData.FName = "No";
			break;
		}

		if (line == FirstName)
		{
			int lineint;
			ClientData.FName = line;
			std::getline(input, line, ':');
			ClientData.LName = line;
			input >> lineint;
			ClientData.ID = lineint;
			std::getline(input, line, ':');
			input >> lineint;
			ClientData.IYear = lineint;
			break;
		}
	}
	input.close();


	std::string ID = std::to_string(ClientData.ID);
	std::string IYear = std::to_string(ClientData.IYear);
	return { ClientData.FName, ClientData.LName, ID, IYear};
}

bool RemoveClient(std::string FirstName) //Removes Clients from Clients.txt
{
	std::vector<std::string> content;

	std::ifstream input;
	input.open("Clients.txt");
	if (!input.is_open()) {
		exit(-1);
	}
	
	if (SearchClients(FirstName)[0] == "No")
	{
		return false;
	}

	std::string deleteLine = ":" + FirstName + ":" + SearchClients(FirstName)[1] + ":" + SearchClients(FirstName)[2] + ":" + SearchClients(FirstName)[3];
	
	while (input)
	{
		std::string line;
		std::getline(input, line);
		if ((line != deleteLine) && (line != ""))
		{
			content.push_back(line);
		}
	}
	input.close();
	
	std::ofstream file("Clients.txt");

	for (size_t n = 0; n < content.size(); n++)
	{
		file << content[n] << std::endl;
		//std::cout << content[n] << std::endl;
	}
	file.close();

	return true;
}

bool EditClient(std::string OldFirstName, std::string NewFirstName, std::string NewLastName, int NewIDNum, int NewIYear) //Deletes old client and add new one(edits)
{
	if (SearchClients(OldFirstName)[0] == "No")
	{
		return false;
	}
	RemoveClient(OldFirstName);
	AddClient(NewFirstName, NewLastName, NewIDNum, NewIYear);
	return true;
}

int main()
{
	TitleScreen();
	while (true)
	{
		int MainSelection = ActiveMenu({ "Add Clients", "Remove Clients" , "Search Client Records" , "Edit Client Record" , "Exit" }, 2, 4);
		system("cls");
		
		switch (MainSelection)
		{
		case 1:
			std::cout << "First Name: ";
			std::cin >> ClientData.FName;
			std::cout << "Last Name: ";
			std::cin >> ClientData.LName;
			std::cout << "ID: ";
			std::cin >> ClientData.ID;
			std::cout << "Induction Year: ";
			std::cin >> ClientData.IYear;

			AddClient(ClientData.FName, ClientData.LName, ClientData.ID, ClientData.IYear);
			system("cls");
			break;
		case 2:
		{
			std::string Fname;
			std::cout << "Enter First Name: ";
			std::cin >> Fname;

			if (RemoveClient(Fname))
			{
				std::cout << "Successfully Removed Client" << std::endl;
			}
			else
			{
				std::cout << "Unable to Find Client " << Fname << std::endl;
			}
			
			break;
		}
		case 3:
		{
			std::string Fname;
			std::cout << "Enter First Name: ";
			std::cin >> Fname;

			if (SearchClients(Fname)[0] == "No")
			{
				std::cout << "No Client Found with the Name " << Fname << std::endl;
				break;
			}

			std::cout << "First Name: " << SearchClients(Fname)[0] << "\nLast Name: " << SearchClients(Fname)[1] << "\nID: " << SearchClients(Fname)[2] << "\nInduction Year: " << SearchClients(Fname)[3] << std::endl;

			break;
		}
		case 4:
		{
			std::string Fname;
			std::cout << "Enter First Name: ";
			std::cin >> Fname;

			if (SearchClients(Fname)[0] == "No")
			{
				std::cout << "Unable to Find Client " << Fname << std::endl;
				break;
			}
			else
			{
				std::cout << "First Name: ";
				std::cin >> ClientData.FName;
				std::cout << "Last Name: ";
				std::cin >> ClientData.LName;
				std::cout << "ID: ";
				std::cin >> ClientData.ID;
				std::cout << "Induction Year: ";
				std::cin >> ClientData.IYear;

				if (EditClient(Fname, ClientData.FName, ClientData.LName, ClientData.ID, ClientData.IYear))
				{
					std::cout << "Succesfully changed Client info" << std::endl;
				}
				else
				{
					std::cout << "Error" << std::endl;
				}
			}

			break;
		}
		case 5:
			exit(-1);
			break;
		default:
			break;
		}
	}
	return 0;
}