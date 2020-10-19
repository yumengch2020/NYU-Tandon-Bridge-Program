#include <iostream>
#include <cmath>
using namespace std;
//a.
void analyzeDividors(int num, int& outCountDiv, int& outSumDivs) {
    int divisor;
    double sqrtOfNum = sqrt(num);
    int count, sum1;
    count = 0;
    sum1 = 0;
    for(divisor = 1; divisor <= (int)sqrtOfNum; divisor++) {
        if(num % divisor == 0) {
            count++;
            sum1 += divisor;
        }
    }
    int sum = sum1;
    if ((int)sqrtOfNum == sqrtOfNum) {
        divisor = (int)sqrtOfNum - 1;
    }
    else if ((int)sqrtOfNum != sqrtOfNum) {
        divisor = (int)sqrtOfNum;
    }
    while (divisor > 1) {
        if (num % divisor == 0) {
            sum = sum + num / divisor;
            count++;
        }
        divisor--;
    }
    outCountDiv = count;
    outSumDivs = sum;
}
//b.
bool isPerfect(int num) {
    int countDivs, sumDivs;
    analyzeDividors(num, countDivs, sumDivs);
    return (num == sumDivs);
}
int main() {
    int inputInteger;
    int currentNumber;
    int countDivs_current, sumDivs_current;
    int pairNumber;
    int countDivs_pair, sumDivs_pair;

    cout << "Please enter a positive integer >=2:";
    cin >> inputInteger;
    cout << "The perfect number between 2 and " << inputInteger << " are: " << endl;
    for (currentNumber = 2; currentNumber <= inputInteger; currentNumber++) {
        if(isPerfect(currentNumber) == true)
            cout << currentNumber << '\t';
    }
    cout << endl << "The pairs of amicable numbers that are between 2 and " << inputInteger << " are: " << endl;
    for (currentNumber = 2; currentNumber <= inputInteger; currentNumber++) {
        analyzeDividors(currentNumber, countDivs_current, sumDivs_current);
        if (sumDivs_current <= inputInteger)
            pairNumber = sumDivs_current;
        analyzeDividors(pairNumber, countDivs_pair, sumDivs_pair);
        if (pairNumber != currentNumber && sumDivs_pair == currentNumber && pairNumber < currentNumber)
            cout << currentNumber << '\t' << pairNumber << endl;
    }
    return 0;
}
