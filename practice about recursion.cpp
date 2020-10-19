#include <iostream>
using namespace std;
//hanoi
void hanoi(int src, int dst, int n) {
    int temp = 6- src - dst;
    if(n == 1)
        cout << src << " to " << dst << endl;
    else {
        hanoi(src, temp, n - 1);
        hanoi(src, dst, 1);
        hanoi(temp, dst, n - 1);
    }
}

//merge sort
void mergeSort(int* arr, int leftStart, int rightEnd) {
    int leftEnd = (leftStart + rightEnd) / 2;
    int rightStart = leftEnd + 1;
    int l = leftStart, r = rightStart;
    int* temp = new int[rightEnd - leftStart + 1];
    int ind = 0;
    while(l <= leftEnd && r <= rightEnd) {
        if (arr[l] <= arr[r])
            temp[ind++] = arr[l++];
        else
            temp[ind++] = arr[r++];
    }
    if (l <= leftEnd) {
        for(int i = l; i <= leftEnd; i++)
            temp[ind++] = arr[i];
    }
    if (r <= rightEnd) {
        for(int i = r; i <= rightEnd; i++)
            temp[ind++] = arr[i];
    }
    for(int i = leftStart; i <= rightEnd; i++)
        arr[i] = temp[i - leftStart];
}
void printArray(int* arr, int arrSize) {
    for(int i = 0; i < arrSize; i++)
        cout << arr[i] << ' ';
}
void mergeArray(int* arr, int leftStart, int rightEnd) {
    int middle = (leftStart + rightEnd) / 2;
    if(leftStart < rightEnd) {
        mergeArray(arr, leftStart, middle);
        mergeArray(arr, middle + 1, rightEnd);
        mergeSort(arr, leftStart, rightEnd);
    }
}


//combination
void combine(int start, int end, int k, string str, char* arr) {
    int n = end - start + 1;
    if (k > n || k < 0)
        return;
    else if (k == 0)
        cout << str << endl;
    else {
        for(int i = start; i <= end - k + 1; i++) {
            combine(i + 1, end, k - 1, str + arr[i], arr);

        }
    }
}

void combination(int* arr, int* temp, int start, int end, int index, int r) {
    if (index == r) {
        for(int i = 0; i < r; i++)
            cout << temp[i] <<' ';
        cout << endl;
        return;
    }
        //from the index position to r - 1, we choose (r - index) elements
        //so the last elements we choose in array is (end - ( r - index) + 1)
    else if ( index < r) {
        for(int i = start; i <= end - r + index + 1; i++) {

            temp[index] = arr[i];
            combination(arr, temp, start + 1, end, index + 1, r);
        }
    }
}

void printCombination(int* arr, int n, int r) {
    int* temp = new int[r - 1];
    combination(arr, temp, 0, n -1, 0, r);

}

//permutation
void swap(int& a, int& b) {
    int temp = a; a = b; b = temp;
}
void permute (string str, int left, int right) {
    if (left == right)
        cout << str << endl;
    if (left < right) {
        for(int i = left; i <= right; i++) {
            swap(str[i], str[left]);
            permute(str, left + 1, right);
        }
    }
}
void permutation(string str, int left, int right) {
    if (left == right)
        cout << str << endl;
    if(left < right) {
        for(int i = left; i <= right; i++) {
            swap(str[i], str[left]);
            permutation(str, left + 1, right);
            swap(str[i], str[left]);
        }
    }
}
//0-1 maxValue
int maxVal(int ind, int leftWeight, int* wt, int* val) {
    int maxValue = 0;
    if(ind < 5) {
        if(wt[ind] > leftWeight)
            maxValue = maxVal(ind + 1, leftWeight, wt, val);
        else
            maxValue = max(
                    maxVal(ind + 1, leftWeight, wt, val),
                    maxVal(ind + 1 , leftWeight - wt[ind], wt, val) + val[ind]
            );
    }
    return maxValue;
}
//No.1
void printTriangle(int n) {
    if (n <= 0)
        return;
    else {
        printTriangle(n - 1);
        for(int i = 0; i < n; i++)
            cout << '*';
        cout << endl;
    }
}

void printOpositeTriangles(int n) {
    if (n <= 0)
        return;
    else {
        for(int i = 1; i <= n; i++)
            cout << '*';
        cout << endl;
        if(n - 1 >0) // this is not needed
            printOpositeTriangles(n - 1);
        for(int i = 1; i <= n; i++)
            cout << '*';
        cout << endl;
    }
}

void printRuler(int n) {
    if(n == 1)
        cout << "- " << endl;
    else {
        printRuler(n - 1);
        for(int i = 1; i <= n; i++)
            cout << "- ";
        cout << endl;
        printRuler(n - 1);
    }

    return;
}

//No.2
int sumOfSquares (int arr[], int arrSize) {
    int sum = 0;
    if (arrSize == 1)
        sum = arr[0] * arr[0];
    else {
        sum = sumOfSquares(arr, arrSize - 1) + arr[arrSize - 1] * arr[arrSize - 1];
    }
    return sum;
}

bool isSorted(int arr[], int arrSize) {
    if (arrSize == 1)
        return true;
    else if(arrSize > 1 ){
        if (isSorted(arr,arrSize - 1) && arr[arrSize - 1] >= arr[arrSize - 2] )
            return true;
        else
            return false;
    }
}

bool isSorted2(int arr[], int arrSize) {
    if (arrSize == 1 || arrSize == 0)
        return true;
    if (arr[arrSize - 1] < arr[arrSize - 2])
        return false;
    return isSorted2(arr, arrSize - 1);
}

//No.3
int minInArray1(int arr[], int arrSize) {
    int min;
    if (arrSize == 1)
        min = arr[0];
    else {
        int temp = minInArray1(arr, arrSize - 1);
        if (arr[arrSize - 1] <= temp)
            min = arr[arrSize - 1];
        else
            min = temp;
    }
    return min;
}

int minInArray2(int arr[], int low, int high) {
    int min;
    if (high == low)
        min = arr[low];
    else {
        int temp = minInArray2(arr, low, high - 1);
        if (arr[high] <= temp)
            min = arr[high];
        else
            min = temp;
    }
    return min;
}

//No.4
int lowestCostOfJump(int arr[],int n) {
    int min;
    if (n == 1)
        min = 0;
    else if (n == 2 || n == 3)
        min = arr[n - 1];
    else {
        int temp1 = lowestCostOfJump(arr, n - 2);
        int temp2 = lowestCostOfJump(arr, n - 1);
        if (temp1 <= temp2)
            min = temp1 + arr[n - 1];
        else
            min = temp2 + arr[n - 1];
    }
    return min;
}
int main() {
    //No.1
    int inputInteger;
    cout << "Please enter a positive integer:" ;
    cin >> inputInteger;
    cout << endl << "Triangle:" << endl;
    printTriangle(inputInteger);
    cout << endl << "OpositeTriangle:" << endl;
    printOpositeTriangles(inputInteger);
    cout << endl << "Ruler:" << endl;
    printRuler(inputInteger);

    //No.2
    int num[4] = {-1, 3, 2, 10};
    cout << sumOfSquares(num, 4) << endl;
    if(isSorted(num, 4))
        cout << "The elements are sorted in an ascending order";
    else
        cout << "The elements are not sorted in an ascending order";

    //No.3
    int arr[10] = {9, -2, 14, 12, 3, 6, 2, 1, -9, 15};
    int res1, res2, res3, res4;

    res1 = minInArray1(arr, 10);
    res2 = minInArray2(arr, 0 ,9);
    cout << res1 << " " << res2 << endl;

    res3 = minInArray2(arr, 2, 5);
    res4 = minInArray1(arr + 2, 4);
    cout << res3 << " " << res4 << endl;

    //No.4
    int arr[6] = {0, 3, 80, 6, 57, 10};
    cout << lowestCostOfJump(arr, 6);
    return 0;
}
