#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>

const int TOTAL_GUESS_NUM = 5;
const int MIN_LIMIT = 1;
const int MAX_LIMIT = 100;

int main() {
    srand (time(0));
    int randomNum = (rand() % MAX_LIMIT) + MIN_LIMIT;

    int numOfGuessLeft;
    int guessNum;
    int leftLimit = MIN_LIMIT;
    int rightLimit = MAX_LIMIT;


    cout << "I thought of a number between " << MIN_LIMIT << " and " << MAX_LIMIT << "! Try to guess it." << endl;

    for (numOfGuessLeft = TOTAL_GUESS_NUM; numOfGuessLeft >= 1; numOfGuessLeft--) {
        cout << "Range: [" << leftLimit << ", " << rightLimit << "], Number of guesses left: " << numOfGuessLeft << endl;
        cout << "Your guess: ";
        cin >> guessNum;

        if (guessNum == randomNum) {
            cout << "Congrats! You guessed my number in " << TOTAL_GUESS_NUM - numOfGuessLeft + 1 << " guesses. "
                 << endl;
            return 0;
        } else if (numOfGuessLeft == 1){
            cout << "Out of guesses! My number is " << randomNum << endl;
        }
        else if (guessNum < randomNum) {
            cout << "Wrong! My number is bigger." << endl << endl;
            if (guessNum >= leftLimit) {
                leftLimit = guessNum + 1;
            }
        }
        else if (guessNum > randomNum) {
            cout << "Wrong! My number is smaller." << endl << endl;
            if (guessNum <= rightLimit) {
                rightLimit = guessNum - 1;
            }
        }
    }
    return 0;
}
