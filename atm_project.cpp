#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <nlohmann/json.hpp>
#include <fstream> 

using namespace std;
using namespace nlohmann;


string EnteredNumber;

class Card
{
public:
    string name, surname;
    int nubmer,balance_card = 0,balance_deposit = 0;

    Card() {}

    Card(string name1, string surname1)
    {
        name = name1;
        surname = surname1;
    }


};

Card CreateCard()
{
    system("cls");
    string name, surname;
    cout << "Enter your name" << endl;
    cin >> name;
    cout << endl;
    cout << "Enter your surname" << endl;
    cin >> surname;
    cout << endl;
    system("cls");
    Card card(name, surname);

    fstream CardData;
    CardData.open("CardData.txt");
    string LastNum;
    while (true)
    {
        if (!CardData.eof())
        {
            getline(CardData, LastNum);
        }
        else
            break;
        
    }

    CardData.close();

    card.nubmer = atoi(LastNum.c_str()) + 1;

    string CardNumber = to_string(atoi(LastNum.c_str()) + 1);

    ofstream CardData1;
    CardData1.open("CardData.txt", ios_base::app);
    CardData1 <<endl<< CardNumber;
    CardData1.close();

    return card;
}

int Createjsonfile()
{
    Card cardd = CreateCard();
    string FileName = to_string(cardd.nubmer) + ".json";
    ofstream card1;
    card1.open(FileName.c_str());

    
    json card;
    
    card["name"] = cardd.name;
    card["surname"] = cardd.surname;
    card["balance_card"] = cardd.balance_card;
    card["number"] = cardd.nubmer;
    card["balance_deposit"] = cardd.balance_deposit;

    card1 << card << endl;
    card1.close();

    return cardd.nubmer;
}

void load()
{
    Sleep(100);
    cout << ". ";
    Sleep(100);
    cout << ". ";
    Sleep(100);
    cout << "." << endl;
}

Card TakejsonInfo(string filename)
{
    fstream f(filename.c_str());
    json Cardj = json::parse(f);

    Card card;
    card.name = Cardj["name"];
    card.nubmer = Cardj["number"];
    card.surname = Cardj["surname"];
    card.balance_card = Cardj["balance_card"];
    card.balance_deposit = Cardj["balance_deposit"];

    f.close();
    return card;
}

void TopUp_card()
{
    system("cls");
    cout << "Enter banknotes (from 100 to 5000)" << endl;
    int EnteredValue;
    cin >> EnteredValue;
    
    
    if (EnteredValue > 0)
    {
        load();

        Card card = TakejsonInfo(EnteredNumber);

        card.balance_card += EnteredValue;

        remove(EnteredNumber.c_str());

        ofstream card1;
        card1.open(EnteredNumber.c_str());

        json CardNew;

        CardNew["name"] = card.name;
        CardNew["surname"] = card.surname;
        CardNew["number"] = card.nubmer;
        CardNew["balance_card"] = card.balance_card;
        CardNew["balance_deposit"] = card.balance_deposit;

        card1 << CardNew << endl;

        card1.close();

        Sleep(500);
        cout << "Operation completed!" << endl;
        Sleep(500);
        cout << "Now your card balance is " << card.balance_card << endl;
        Sleep(3000);
        load();
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void TopUp_deposit_cash()
{
    system("cls");
    cout << "Enter banknotes (from 100 to 5000)" << endl;
    int EnteredValue;
    cin >> EnteredValue;
    load();

    Card card = TakejsonInfo(EnteredNumber);

    if (EnteredValue > 0)
    {

        card.balance_deposit += EnteredValue;

        remove(EnteredNumber.c_str());

        ofstream card1;
        card1.open(EnteredNumber.c_str());

        json CardNew;

        CardNew["name"] = card.name;
        CardNew["surname"] = card.surname;
        CardNew["number"] = card.nubmer;
        CardNew["balance_card"] = card.balance_card;
        CardNew["balance_deposit"] = card.balance_deposit;

        card1 << CardNew << endl;

        card1.close();

        Sleep(500);
        cout << "Operation completed!" << endl;
        Sleep(500);
        cout << "Now your deposit balance is " << card.balance_deposit << endl;
        Sleep(3000);
        load();
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void TopUp_deposit_card()
{
    system("cls");
    cout << "Enter banknotes (from 100 to 5000)" << endl;
    int EnteredValue;
    cin >> EnteredValue;
    load();

    Card card = TakejsonInfo(EnteredNumber);

    if (EnteredValue > 0)
    {
        if (EnteredValue <= card.balance_card)
        {
            card.balance_card -= EnteredValue;
            card.balance_deposit += EnteredValue;

            remove(EnteredNumber.c_str());

            ofstream card1;
            card1.open(EnteredNumber.c_str());

            json CardNew;

            CardNew["name"] = card.name;
            CardNew["surname"] = card.surname;
            CardNew["number"] = card.nubmer;
            CardNew["balance_card"] = card.balance_card;
            CardNew["balance_deposit"] = card.balance_deposit;

            card1 << CardNew << endl;

            card1.close();

            cout << "Completed!" << endl;
            Sleep(1000);
            cout << "Now your deposit balance is " << card.balance_deposit << endl;
            Sleep(1000);
            load();
        }
        else
        {
            cout << "Not enough balance" << endl;
            Sleep(1000);
            load();
        }
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void cashout_card()
{
    system("cls");

    int EnteredValue;

    cout << "Enter value u want cashout" << endl;
    cin >> EnteredValue;

    ifstream card(EnteredNumber.c_str());

    Card card1 = TakejsonInfo(EnteredNumber);

    if (EnteredValue > 0)
    {
        if (card1.balance_card >= EnteredValue)
        {

            card1.balance_card -= EnteredValue;

            remove(EnteredNumber.c_str());

            ofstream card2;
            card2.open(EnteredNumber.c_str());

            json CardNew;

            CardNew["name"] = card1.name;
            CardNew["surname"] = card1.surname;
            CardNew["number"] = card1.nubmer;
            CardNew["balance_card"] = card1.balance_card;
            CardNew["balance_deposit"] = card1.balance_deposit;

            card2 << CardNew << endl;

            card2.close();

            Sleep(500);
            cout << "Operation completed!" << endl;
            Sleep(500);
            cout << "Now your deposit balance is " << card1.balance_card << endl;
            Sleep(3000);
            load();
        }

        else
        {
            cout << "Not enough balance" << endl;
            Sleep(1000);
            load();
        }
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void cashout_deposit()
{
    system("cls");

    int EnteredValue;

    cout << "Enter value u want cashout" << endl;
    cin >> EnteredValue;

    ifstream card(EnteredNumber.c_str());

    Card card1 = TakejsonInfo(EnteredNumber);

    if (EnteredValue > 0)
    {
        if (card1.balance_deposit >= EnteredValue)
        {

            card1.balance_deposit -= EnteredValue;

            remove(EnteredNumber.c_str());

            ofstream card2;
            card2.open(EnteredNumber.c_str());

            json CardNew;

            CardNew["name"] = card1.name;
            CardNew["surname"] = card1.surname;
            CardNew["number"] = card1.nubmer;
            CardNew["balance_card"] = card1.balance_card;
            CardNew["balance_deposit"] = card1.balance_deposit;

            card2 << CardNew << endl;

            card2.close();

            Sleep(500);
            cout << "Operation completed!" << endl;
            Sleep(500);
            cout << "Now your deposit balance is " << card1.balance_deposit << endl;
            Sleep(3000);
            load();
        }

        else
        {
            cout << "Not enough balance" << endl;
            Sleep(1000);
            load();
        }
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void transfer_card2card()
{
    system("cls");

    string TransferToNumber;
    int TransferValue;
    system("cls");
    cout << "Enter number of card u want to transfer" << endl;
    cin >> TransferToNumber;
    TransferToNumber = TransferToNumber + ".json";


    
        if (TransferToNumber == EnteredNumber)
        {
            cout << "Numbers of card are the same" << endl;
            Sleep(1000);
            load();
        }
        else {
            ifstream card(TransferToNumber.c_str());

            if (card.is_open())
            {


                cout << "Enter value" << endl;
                cin >> TransferValue;

                if (TransferValue > 0)
                {


                    Card cardto = TakejsonInfo(TransferToNumber);


                    Card cardfrom = TakejsonInfo(EnteredNumber);







                    if (cardfrom.balance_card >= TransferValue)
                    {
                        cardfrom.balance_card -= TransferValue;
                        cardto.balance_card += TransferValue;


                        remove(EnteredNumber.c_str());

                        ofstream card2;
                        card2.open(EnteredNumber.c_str());

                        json CardNewfrom;

                        CardNewfrom["name"] = cardfrom.name;
                        CardNewfrom["surname"] = cardfrom.surname;
                        CardNewfrom["number"] = cardfrom.nubmer;
                        CardNewfrom["balance_card"] = cardfrom.balance_card;
                        CardNewfrom["balance_deposit"] = cardfrom.balance_deposit;

                        card2 << CardNewfrom << endl;

                        card2.close();

                        remove(TransferToNumber.c_str());

                        ofstream card3;
                        card3.open(TransferToNumber.c_str());

                        json CardNewto;

                        CardNewto["name"] = cardto.name;
                        CardNewto["surname"] = cardto.surname;
                        CardNewto["number"] = cardto.nubmer;
                        CardNewto["balance_card"] = cardto.balance_card;
                        CardNewto["balance_deposit"] = cardto.balance_deposit;

                        card3 << CardNewto << endl;

                        card3.close();

                        Sleep(500);
                        cout << "Operation completed!" << endl;
                        Sleep(500);
                        cout << "Now your card balance is " << cardfrom.balance_card << endl;
                        Sleep(3000);
                        load();
                    }
                    else
                    {
                        cout << "Not enough balance" << endl;
                        Sleep(1000);
                        load();
                    }
                }
                else
                {
                    cout << "Invalid value" << endl;
                    Sleep(1000);
                    load();
                }

            }
            else
            {
                cout << "Invalid card number" << endl;
                Sleep(1000);
                load();
            }
        }
    
    

}

void transfer_deposit2card()
{
    system("cls");
    int EnteredValue;
    cout << "Enter value u want to transfer" << endl;
    cin >> EnteredValue;
    Card card = TakejsonInfo(EnteredNumber);
    if (EnteredValue > 0)
    {
        if (EnteredValue <= card.balance_deposit)
        {
            card.balance_card += EnteredValue;
            card.balance_deposit -= EnteredValue;

            remove(EnteredNumber.c_str());

            ofstream card1;
            card1.open(EnteredNumber.c_str());

            json CardNew;

            CardNew["name"] = card.name;
            CardNew["surname"] = card.surname;
            CardNew["number"] = card.nubmer;
            CardNew["balance_card"] = card.balance_card;
            CardNew["balance_deposit"] = card.balance_deposit;

            card1 << CardNew << endl;

            card1.close();

            cout << "Completed!" << endl;
            Sleep(1000);
            cout << "Now your deposit balance is " << card.balance_deposit << " and card balance is " << card.balance_card << endl;
            Sleep(3000);
            load();
        }
        else
        {
            cout << "Not enough balance" << endl;
            Sleep(1000);
            load();
        }
    }
    else
    {
        cout << "Invalid value" << endl;
        Sleep(1000);
        load();
    }
}

void gotoxy(short x, short y)
{
    COORD p = { x,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

bool LogIn()
{
    system("cls");
    cout << "enter your card number" << endl;
    cin >> EnteredNumber;
    EnteredNumber = EnteredNumber + ".json";

    ifstream card(EnteredNumber.c_str());
    if (card.is_open())
        return true;
    else return false;
}

void ShowAccountInfo()
{
    system("cls");
    ifstream f(EnteredNumber.c_str());
    json Card = json::parse(f);

    cout << "Name: " << Card["name"] << endl << "Surname: " << Card["surname"] << endl << "Card balance: " << Card["balance_card"]<<endl<<"Deposit balance: "<<Card["balance_deposit"] << endl << "Card Number: " << Card["number"] << endl;
    f.close();
}

void ShowDepositMenu()
{
    system("cls");
    cout << " top up deposit w cash" << endl;
    cout << " top up deposit from card balance" << endl;
    cout << " transfer to card" << endl;
    cout << " cashout" << endl;
    cout << " back to account menu" << endl;
}

void ShowAccountMenu()
{
    system("cls");
    cout << " show account info" << endl;
    cout << " show deposit menu" << endl;
    cout << " top up card" << endl;
    cout << " transfer" << endl;
    cout << " cashout" << endl;
    cout << " back to main menu" << endl;

}

void ShowMainMenu()
{
    system("cls");
    cout << " Log In" << endl;
    cout << " Create a Card" << endl;
    cout << " Exit" << endl;
}

int main()
{


    int ch = 0;
    int MenuItem = 0;
    bool exit = false, exitToMainMenu = false, exitToAccMenu = false;

    ShowMainMenu();

    while (!exit)
    {

        ShowMainMenu();
        gotoxy(0, MenuItem);

        ch = _getch();
        if (ch == 224)
            ch = _getch();

        switch (ch)
        {
        case 27: exit = true; break;
        case 72: MenuItem--; break;
        case 80: MenuItem++; break;
        case 13:
            if (MenuItem == 0) // Log In
            {

                exitToMainMenu = false;
                if (LogIn()) {
                    ShowAccountMenu();

                    while (!exitToMainMenu)
                    {
                        ShowAccountMenu();
                        gotoxy(0, MenuItem);
                        ch = _getch();
                        if (ch == 224)
                            ch = _getch();
                        switch (ch)
                        {
                        case 27: exitToMainMenu = true; break;
                        case 72: MenuItem--; break;
                        case 80: MenuItem++; break;
                        case 13:
                            if (MenuItem == 0) // show account info
                            {
                                exitToAccMenu = false;
                                while (!exitToAccMenu)
                                {
                                    ch = _getch();
                                    if (ch == 224)
                                        ch = _getch();
                                    ShowAccountInfo();
                                    switch (ch)
                                    {
                                    case 27: exitToAccMenu = true; break;
                                    }
                                }
                                exitToAccMenu = false;
                            }
                            else if (MenuItem == 1) // deposit menu
                            {
                                exitToAccMenu = false;
                                while (!exitToAccMenu)
                                {
                                    ShowDepositMenu();
                                    gotoxy(0, MenuItem);
                                    ch = _getch();
                                    if (ch == 224)
                                        ch = _getch();
                                    switch (ch)
                                    {
                                    case 27: exitToMainMenu = true; break;
                                    case 72: MenuItem--; break;
                                    case 80: MenuItem++; break;
                                    case 13:
                                        if (MenuItem == 0) // top up deposit w cash
                                        {
                                            TopUp_deposit_cash();
                                        }
                                        else if (MenuItem == 1) // top up deposit from card
                                        {
                                            TopUp_deposit_card();
                                        }
                                        else if (MenuItem == 2) // transfer to card
                                        {
                                            transfer_deposit2card();
                                        }
                                        else if (MenuItem == 3) // cashout
                                        {
                                            cashout_deposit();
                                        }
                                        else if (MenuItem == 4) // exit to acc menu
                                        {
                                            exitToAccMenu = true;
                                        }
                                    }
                                    if (MenuItem < 0)
                                    {
                                        MenuItem = 0;
                                    }
                                    if (MenuItem > 4)
                                    {
                                        MenuItem = 4;
                                    }
                                }
                            }
                            else if (MenuItem == 2) // top up card 
                            {
                                TopUp_card();
                            }
                            else if (MenuItem == 3) // transfer
                            {
                                transfer_card2card();
                            }
                            else if (MenuItem == 4) // cashout
                            {
                                cashout_card();
                            }
                            else if (MenuItem == 5) // exit to main menu
                            {
                                exitToMainMenu = true;
                            }

                            
                        }
                        if (MenuItem < 0)
                        {
                            MenuItem = 0;
                        }
                        if (MenuItem > 5)
                        {
                            MenuItem = 5;
                        }
                    }
                }
            }
                            else if (MenuItem == 1) // Create a card
                            {
                                cout << "Your card number is: " << Createjsonfile();
                                Sleep(5000);

                            }
                            else if (MenuItem == 2) // Exit
                            {
                                exit = true;
                            }
                            break;
        }
                        if (MenuItem < 0)
                        {
                            MenuItem = 0;
                        }
                        if (MenuItem > 2)
                        {
                            MenuItem = 2;
                        }
    }
}
