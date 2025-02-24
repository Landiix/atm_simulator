#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <nlohmann/json.hpp>
#include <fstream> 

using namespace std;
using namespace nlohmann;

class Card
{
public:
    string name, surname;
    int nubmer, balance_card = 0, balance_deposit = 0;

    Card() {}

    Card(string name1, string surname1)
    {
        name = name1;
        surname = surname1;
    }


};


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

void UpdateJson(Card card, string number)
{
    remove(number.c_str());
    ofstream card1;
    card1.open(number.c_str());

    json CardNew;

    CardNew["name"] = card.name;
    CardNew["surname"] = card.surname;
    CardNew["number"] = card.nubmer;
    CardNew["balance_card"] = card.balance_card;
    CardNew["balance_deposit"] = card.balance_deposit;

    card1 << CardNew << endl;

    card1.close();
}

int main()
{

        string line;

        while (true)
        {
            ifstream CardData;
            CardData.open("../CardData.txt");
            while (true)
            {
                if (!CardData.eof())
                {
                    getline(CardData, line);
                    line = "../" + line + ".json";
                    Card card = TakejsonInfo(line);

                    card.balance_deposit *= 1.1;

                    UpdateJson(card, line);
                }
                else
                    break;
            }

            CardData.close();
            Sleep(1000000);
        }
        
        
}

