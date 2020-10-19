#include <iostream>
#include <string>
using namespace std;
int* getPosNums1(int* arr, int arrSize, int& outPosArrSize);
void getPosNums2(int* arr, int arrSize, int*& outPosArr, int& outPosArrSize);
int* getPosNums3(int* arr, int arrSize, int* outPosArrSizePtr);
void getPosNums4(int* arr, int arrSize, int** outPosArrPtr, int* outPosArrSizePtr);
void printArray(int* arr, int arrSize);

int main() {
    int arrSize;
    cout << "Please enter the size of your array (at least 1):";
    cin >> arrSize;
    int inputNum;
    cout << "Please enter the number of your array, separate each number by a space:";
    int* arr = new int[arrSize];
    for(int i = 0; i < arrSize; i++) {
        cin >> inputNum;
        arr[i] = inputNum;
    }
    int outPosArrSize;

    //test function 1
    cout << "test function 1" << endl;
    int* outPosArr1 = getPosNums1(arr, arrSize, outPosArrSize);
    printArray(outPosArr1, outPosArrSize);

    //test function 2
    cout << "test function 2" << endl;
    int* outPosArr2;
    getPosNums2(arr, arrSize, outPosArr2, outPosArrSize);
    printArray(outPosArr2,outPosArrSize);

    //test function 3
    cout << "test function 3" << endl;
    outPosArrSize = 0;
    int* outPosArr3 = getPosNums3(arr, arrSize, &outPosArrSize);
    printArray(outPosArr3, outPosArrSize);

    //test function 4
    cout << "test function 4" << endl;
    outPosArrSize = 0;
    int* outPosArr4;
    getPosNums4(arr, arrSize, &outPosArr4, &outPosArrSize);
    printArray(outPosArr4, outPosArrSize);

    return 0;
}

int* getPosNums1(int* arr, int arrSize, int& outPosArrSize) {
    outPosArrSize = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            outPosArrSize++;
    }
    int *outPosArr = new int[outPosArrSize];
    int count = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            outPosArr[count++] = arr[i];
    }
    return outPosArr;
}

void getPosNums2(int* arr, int arrSize, int*& outPosArr, int& outPosArrSize){
    outPosArrSize = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            outPosArrSize++;
    }
    outPosArr = new int[outPosArrSize];
    int count = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            outPosArr[count++] = arr[i];
    }

}

int* getPosNums3(int* arr, int arrSize, int* outPosArrSizePtr){
    (*outPosArrSizePtr) = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            (*outPosArrSizePtr)++;
    }
    int *outPosArr = new int[(*outPosArrSizePtr)];
    int count = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            outPosArr[count++] = arr[i];
    }
    return outPosArr;
}

void getPosNums4(int* arr, int arrSize, int** outPosArrPtr, int* outPosArrSizePtr) {
    *outPosArrSizePtr = 0;
    for(int i = 0; i < arrSize; i++) {
        if ( arr[i] > 0)
            (*outPosArrSizePtr)++;
    }
    (*outPosArrPtr) = new int[*outPosArrSizePtr];
    int count = 0;
    for(int i = 0; i < arrSize; i++) {
        if (arr[i] > 0)
            (*outPosArrPtr)[count++] = arr[i];
    }
}

void printArray(int* arr, int arrSize) {
    cout << '[' << arr[0];
    for(int i = 1; i < arrSize; i++)
        cout << ", " << arr[i];
    cout << "]" << endl;
}





















