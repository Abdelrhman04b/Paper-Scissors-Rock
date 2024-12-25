#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

static int NumOfRound, Counter;

char ReadContinue(string Message)
{
    char Continue;
    do
    {
        cout << Message;
        cin >> Continue;
        Continue = tolower(Continue);
    } while (Continue != 'y' && Continue != 'n');
    return Continue;
}

enum enElements
{
    Paper = 1,
    Scissors = 2,
    Rock = 3
};

struct stResultsNum
{
    int Dual = 0, PlayWin = 0, ComWin = 0;
};

int ReadRandomNumber(int From, int To)
{
    int Number;
    Number = rand() % (To - From + 1) + From;
    return Number;
}

int ReadNumberInRange(int From, int To, string Message)
{
    int Number;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

enElements ReadPlayChoice()
{
    int PlayerChoice;
    PlayerChoice = ReadNumberInRange(1, 3, "\nYour choice: [1]:Paper, [2]:Scissors, [3]:Rock ?");
    return enElements(PlayerChoice);
}

enElements ReadComChoice()
{
    int ComChoice;
    ComChoice = ReadRandomNumber(1, 3);
    return enElements(ComChoice);
}

void PrintComWin(string PlayerChoice, string ComChoice, stResultsNum &ResultsNum)
{
    system("color 4F");
    cout << "\a\n________Round [" << Counter << "]________\n";
    cout << "\nPlayer Choice: " << PlayerChoice;
    cout << "\nComputer Choice: " << ComChoice;
    cout << "\nRound winner: [Computer]\n";
    cout << "\n_________________________________________\n";
    ResultsNum.ComWin++;
}

void PrintDual(string PlayerChoice, string ComChoice, stResultsNum &ResultsNum)
{
    system("color 6F");
    cout << "\n________Round [" << Counter << "]________\n";
    cout << "\nPlayer Choice: " << PlayerChoice;
    cout << "\nComputer Choice: " << ComChoice;
    cout << "\nRound winner: [No Winner]\n";
    cout << "\n_________________________________________\n";
    ResultsNum.Dual++;
}

void PrintPlayerWin(string PlayerChoice, string ComChoice, stResultsNum &ResultsNum)
{
    system("color 2F");
    cout << "\n________Round [" << Counter << "]________\n";
    cout << "\nPlayer Choice: " << PlayerChoice;
    cout << "\nComputer Choice: " << ComChoice;
    cout << "\nRound winner: [Player]\n";
    cout << "\n_________________________________________\n";
    ResultsNum.PlayWin++;
}

void PrintResult(stResultsNum &ResultNum)
{
    int PlayerChoice = ReadPlayChoice();
    int ComChoice = ReadComChoice();
    system("cls");
    switch (PlayerChoice)
    {
    case enElements::Paper:
        switch (ComChoice)
        {
        case enElements::Paper:
            PrintDual("Paper", "Paper", ResultNum);
            break;
        case enElements::Scissors:
            PrintComWin("Paper", "Scissors", ResultNum);
            break;
        case enElements::Rock:
            PrintPlayerWin("Paper", "Rock", ResultNum);
        default:
            break;
        }
        break;
    case enElements::Scissors: // Scissors
        switch (ComChoice)
        {
        case enElements::Paper:
            PrintPlayerWin("Scissors", "Paper", ResultNum);
            break;
        case enElements::Scissors:
            PrintDual("Scissors", "Scissors", ResultNum);
            break;
        case enElements::Rock:
            PrintComWin("Scissors", "Rock", ResultNum);
            break;
        default:
            break;
        }
        break;
    case enElements::Rock: // Rock
        switch (ComChoice)
        {
        case enElements::Paper:
            PrintComWin("Rock", "Paper", ResultNum);
            break;
        case enElements::Scissors:
            PrintPlayerWin("Rock", "Scissors", ResultNum);
            break;
        case enElements::Rock:
            PrintDual("Rock", "Rock", ResultNum);
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void PrintFinalResults(stResultsNum ResultsNum)
{
    cout << "\t\t\tGame Rounds\t\t: " << NumOfRound << endl;
    cout << "\t\t\tPlayer won times\t: " << ResultsNum.PlayWin << endl;
    cout << "\t\t\tComputer won times\t: " << ResultsNum.ComWin << endl;
    cout << "\t\t\tDraw times\t\t: " << ResultsNum.Dual << endl;
    cout << "\t\t\tFinal Winner\t\t: ";
    if (ResultsNum.PlayWin > ResultsNum.ComWin)
    {
        system("color 2F");
        cout << "Player\n";
    }
    else if (ResultsNum.PlayWin == ResultsNum.ComWin)
    {
        system("color 6F");
        cout << "Dual\n";
    }
    else
    {
        system("color 4F");
        cout << "\aComputer\n";
    }
}

void PrintGameOver(stResultsNum ResultsNum)
{
    system("cls");
    cout << "\n\t\t\t____________________________________________________\n";
    cout << "\n\t\t\t\t\t*** G a m e Over ***\n";
    cout << "\n\t\t\t____________________________________________________\n";
    cout << "\n\t\t\t___________________[Game Results]___________________\n";
    PrintFinalResults(ResultsNum);
    cout << "\n\t\t\t____________________________________________________\n";
}

int main()
{
    srand((unsigned)time(NULL));
    char Continue;
    do
    {
        system("color 0F");
        system("cls");
        Counter = 1;
        stResultsNum ResultsNum;
        NumOfRound = ReadNumberInRange(1, 10, "Enter the number of round [1] to [10]");
        do
        {
            PrintResult(ResultsNum);
            Counter++;
        } while (Counter <= NumOfRound);
        PrintGameOver(ResultsNum);
        Continue = ReadContinue("\nDo you want to continue? ");
    } while (Continue == 'y');
    return 0;
}