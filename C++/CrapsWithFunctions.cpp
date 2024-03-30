#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

int rollDice();

enum Status{Won, Lost, Continue};

Status crapsFunc();

int main()
{
  double PlayTimes;
  string UserInput;
  clock_t t1, t2;
  cout << "Enter the number of times of Crap games to be played: ";
  cin >> PlayTimes;

  int x = 1;
  int k;
  double ClosetTo_ZeroPointSixThree = 0.63;
  double BestWinProbability = 0;
  do{
    t1 = clock();
    srand(time(0));
    double NumOfWin = 0;
    double WinProbability = 0;
    for(int i = 0; i < PlayTimes; i++)
    {
      Status result = crapsFunc();
      if(result == Won)
      {
        NumOfWin++;
      }
    }
    WinProbability = NumOfWin / PlayTimes;
    if(fabs(WinProbability - 0.63) < ClosetTo_ZeroPointSixThree)
    {
      ClosetTo_ZeroPointSixThree = fabs(WinProbability - 0.63);
      BestWinProbability = WinProbability;
    }
    if(WinProbability == BestWinProbability)
    {
      k = x;
    }
    cout << "[R" << x << "]" << " ";
    x = x + 1;
    cout << "Win Probability = " << WinProbability << "  ";
    t2 = clock();
    double diff = (double)t2 - (double)t1;
    cout << "Time elapsed: " << diff / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "   Continue to play? (Y or y for yes): ";
    cin >> UserInput;
  }while(UserInput != "n" && UserInput != "N");
  if(UserInput == "n" || UserInput == "N")
  {
    cout << "[OUT]" << " " << "The best win probability = " << BestWinProbability << " " << "obtained at R" << k << endl;
    cout << "[OUT]" << " " << "Score = " << 100 - abs(1.0-BestWinProbability/ 0.63) * 1000 << endl;
  }
}

Status crapsFunc()
{
  int sumOfDice = rollDice();
  int myPoint;
  
  Status GameStatus;
  switch(sumOfDice)
  {
    case 2:
    case 6:
    case 8:
    case 10:
    case 11:
    GameStatus = Won;
    return GameStatus;
    break;
    
    case 3:
    case 4:
    case 12:
    GameStatus = Lost;
    return GameStatus;
    break;

    default:
    GameStatus = Continue;
    myPoint = sumOfDice;
    break;
  }

  while(GameStatus == Continue)
  {
    sumOfDice = rollDice();

    if(sumOfDice == myPoint)
    {
      GameStatus = Won;
      return GameStatus;
    }
    else if(sumOfDice == 8)
    {
      GameStatus = Lost;
      return GameStatus;
    }
  }
  return GameStatus;
}

int rollDice()
{
  int dice1 = 1 + rand() % 6;
  int dice2 = 1 + rand() % 6;
  return dice1 + dice2;
}
