#include<iostream>
#include<cmath>
#include<string>
#include<vector>
using namespace std;

vector<unsigned long long> sb;

unsigned long long convertToDecimal(string skewedBinary)
{
    unsigned long long decimal = 0;
    for (int i = 0; i < skewedBinary.length(); i++)
    {
        unsigned long long digit = skewedBinary[skewedBinary.length() - i - 1] - '0';
        decimal = decimal + digit * (pow(2, i + 1) - 1);
    }
    return decimal;
}

unsigned long long convertToSkewedBinary(unsigned long long decimal)
{
    sb.clear();
    sb.push_back(0);

    unsigned long long  index = 1;
    unsigned long long position = 2;

    while (position <= decimal)
    {
        position = position * 2;
        index = index + 1;
    }

    for (int j = 1; j <= index; j++)
    {
        unsigned long long power = pow(2, j);
        for (int m = 0; m <= power - 1; m++)
        {
            sb.push_back(pow(10, j - 1) + sb[m]);
        }
    }
    return sb[decimal];
}

int main()
{
    int testcases;
    cin >> testcases;
    for (int i = 0; i < testcases; i++)
    {
        string BinaryOne;
        string BinaryTwo;
        cin >> BinaryOne >> BinaryTwo;
        unsigned long long totalDecimal = convertToDecimal(BinaryOne) + convertToDecimal(BinaryTwo);
        unsigned long long Binary = convertToSkewedBinary(totalDecimal);
        string finalBinary = "";
        while (Binary >= 1)
        {
            finalBinary = to_string(Binary % 10) + finalBinary;
            Binary = Binary / 10;
        }
        cout << "#" << " ";
        for (int j = 0; j < finalBinary.length(); j++)
        {
            if (j % 10 == 0 && j / 10 > 0)
            {
                cout << " ";
            }
            cout << finalBinary[j];
        }
        cout << endl;
    }
    return 0;
}