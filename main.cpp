#include <iostream>
#include <bitset>
#include <ctime>
#include <chrono>

const int max_size = 60;
const int UNIVERSE_SIZE = 52;
using namespace std;

struct Node {
    char data;
    Node *next;
};


Node *createNode(char data) {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

void insertAtEnd(Node **head, char data) {
    Node *newNode = createNode(data);
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node *arrayToList(const char arr[], int size) {
    Node *head = nullptr;
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            insertAtEnd(&head, arr[i]);
        }
    }
    return head;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

Node *setUnion(Node *A, Node *B) {
    Node *result = nullptr;
    Node *tempA = A;

    while (tempA != nullptr) {
        insertAtEnd(&result, tempA->data);
        tempA = tempA->next;
    }

    Node *tempB = B;
    while (tempB != nullptr) {
        bool found = false;
        Node *tempResult = result;
        while (tempResult != nullptr) {
            if (tempB->data == tempResult->data) {
                found = true;
                break;
            }
            tempResult = tempResult->next;
        }
        if (!found) {
            insertAtEnd(&result, tempB->data);
        }
        tempB = tempB->next;
    }

    return result;
}

Node *setIntersection(Node *A, Node *B) {
    Node *result = nullptr;
    Node *tempA = A;

    while (tempA != nullptr) {
        Node *tempB = B;
        while (tempB != nullptr) {
            if (tempA->data == tempB->data) {
                insertAtEnd(&result, tempA->data);
                break;
            }
            tempB = tempB->next;
        }
        tempA = tempA->next;
    }

    return result;
}

Node *setDifference(Node *A, Node *B) {
    Node *result = nullptr;
    Node *tempA = A;

    while (tempA != nullptr) {
        bool found = false;
        Node *tempB = B;
        while (tempB != nullptr) {
            if (tempA->data == tempB->data) {
                found = true;
                break;
            }
            tempB = tempB->next;
        }
        if (!found) {
            insertAtEnd(&result, tempA->data);
        }
        tempA = tempA->next;
    }

    return result;
}

//                                           ДЛЯ МАССИВОВ

void Union(const char A[], const char B[], char res[]) {
    int k = 0;
    for (int i = 0; i < A[i] != 0; i++) {
        res[k++] = A[i];
    }
    for (int i = 0; i < B[i] != 0; i++) {
        bool fl = false;
        for (int j = 0; j < k; j++) {
            if (B[i] == res[j]) {
                fl = true;
                break;
            }
        }
        if (fl == false) {
            res[k++] = B[i];
        }
    }
}

void Intersection(const char A[], const char B[], char res[]) {
    int k = 0;
    for (int i = 0; A[i] != 0; i++) {

        for (int j = 0; j < max_size; j++) {
            if (A[i] == B[j]) {
                res[k++] = A[i];
                break;
            }
        }
    }
}

void Difference(const char A[], const char B[], char res[]) {
    int k = 0;
    for (int i = 0; i < A[i] != 0; i++) {
        bool fl = false;
        for (int j = 0; j < max_size; j++) {
            if (A[i] == B[j]) {
                fl = true;
                break;
            }
        }
        if (fl == false) {
            res[k++] = A[i];
        }
    }
}

void print(char set[]) {
    for (int i = 0; i < set[i] != 0; i++) {
        cout << set[i] << " ";
    }
    cout << endl;
}
//                                  МАШИННОЕ СЛОВО

unsigned long long arrayToMachineWord(const char arr[], int size) {
    unsigned long long word = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            int charIndex;
            if (arr[i] >= 'a' && arr[i] <= 'z') {
                charIndex = arr[i] - 'a';
            } else if (arr[i] >= 'A' && arr[i] <= 'Z') {
                charIndex = arr[i] - 'A' + 26;
            }
            word |= (1ULL << charIndex);
        }
    }
    return word;
}

void printMachineWord(unsigned long long word) {
    bitset<UNIVERSE_SIZE> bits(word);
    cout << bits << " (";
    for (int i = 0; i < UNIVERSE_SIZE; i++) {
        if (bits[i]) {
            if (i < 26) {
                cout << (char) ('a' + i) << ' ';
            } else {
                cout << (char) ('A' + i - 26) << ' ';
            }
        }
    }
    cout << ")" << endl;
}

//                    УНИВЕРСУМ


void mapToUniverse(const char *str, bool *bitVector) {
    for (int i = 0; i < UNIVERSE_SIZE; ++i)
        bitVector[i] = false;

    for (int i = 0; str[i]; ++i) {
        int index;
        if (islower(str[i])) {
            index = str[i] - 'a';
        } else {
            index = str[i] - 'A' + 26;
        }
        if (index >= 0 && index < UNIVERSE_SIZE) {
            bitVector[index] = true;
        }
    }
}

void unionSets(const bool *A, const bool *B, bool *result) {
    for (int i = 0; i < UNIVERSE_SIZE; ++i)
        result[i] = A[i] || B[i];
}

void differenceSets(const bool *A, const bool *B, bool *result) {
    for (int i = 0; i < UNIVERSE_SIZE; ++i)
        result[i] = A[i] && !B[i];
}

void intersectionSets(const bool *A, const bool *B, bool *result) {
    for (int i = 0; i < UNIVERSE_SIZE; ++i)
        result[i] = A[i] && B[i];
}

void printUniverse(const bool *bitVector) {
    cout << "(";
    for (int i = 0; i < UNIVERSE_SIZE; i++) {
        if (bitVector[i]) {
            if (i < 26) {
                cout << (char) (L'a' + i) << ' ';
            } else {
                cout << (char) (L'A' + (i - 26)) << ' ';
            }
        }
    }
    cout << ")" << endl;
}

int n;

void generateArray(char arr[], int size) {
    for (int i = 0; i < n/*(rand()%49)+3*/; i++) {
        if (rand() % 2) {
            arr[i] = 'a' + rand() % 26;
        } else {
            arr[i] = 'A' + rand() % 26;
        }

    }
}

int main() {
    cout << "Count:";

    cin >> n;
    srand(time(0));
    char A_arr[max_size] = {0};
    char B_arr[max_size] = {0};
    char C_arr[max_size] = {0};
    char D_arr[max_size] = {0};

    generateArray(A_arr, max_size);
    generateArray(B_arr, max_size);
    generateArray(C_arr, max_size);
    generateArray(D_arr, max_size);

    Node *A = arrayToList(A_arr, max_size);
    Node *B = arrayToList(B_arr, max_size);
    Node *C = arrayToList(C_arr, max_size);
    Node *D = arrayToList(D_arr, max_size);

    cout << "A = ";
    printList(A);
    cout << "B = ";
    printList(B);
    cout << "C = ";
    printList(C);
    cout << "D = ";
    printList(D);

    auto list_t1 = chrono::high_resolution_clock::now();
    Node *rez1 = setIntersection(B, C);
    Node *rez2 = setDifference(A, rez1);
    Node *E = setUnion(rez2, D);
    auto list_t2 = chrono::high_resolution_clock::now();
    auto list_time_res = chrono::duration_cast<chrono::duration<double, nano>>(list_t2 - list_t1).count();
    cout << "LIST \n";
    cout << "E = ";
    printList(E);
    cout << "Time " << list_time_res << " nanoseconds\n";
    char res_arr1[max_size] = {0};
    char res_arr2[max_size] = {0};
    char E_arr[max_size] = {0};
    auto arr_t1 = chrono::high_resolution_clock::now();
    Intersection(B_arr, C_arr, res_arr1);
    Difference(A_arr, res_arr1, res_arr2);
    Union(res_arr2, D_arr, E_arr);
    auto arr_t2 = chrono::high_resolution_clock::now();
    auto arr_time_res = chrono::duration_cast<chrono::duration<double, nano>>(arr_t2 - arr_t1).count();

    cout << "ARRAY \n";
    cout << "E = ";
    print(E_arr);
    cout << "Time " << arr_time_res << " nanoseconds\n";
    unsigned long long A_word = arrayToMachineWord(A_arr, max_size);
    unsigned long long B_word = arrayToMachineWord(B_arr, max_size);
    unsigned long long C_word = arrayToMachineWord(C_arr, max_size);
    unsigned long long D_word = arrayToMachineWord(D_arr, max_size);

    cout << "MACHINE WORDS \n";
    cout << "A = ";
    printMachineWord(A_word);
    cout << "B = ";
    printMachineWord(B_word);
    cout << "C = ";
    printMachineWord(C_word);
    cout << "D = ";
    printMachineWord(D_word);
    auto mw_t1 = chrono::high_resolution_clock::now();
    unsigned long long res_word1 = (B_word & C_word);
    unsigned long long res_word2 = (A_word & ~(res_word1));
    unsigned long long E_word = (res_word2 | D_word);
    auto mw_t2 = chrono::high_resolution_clock::now();
    auto mw_time_res = chrono::duration_cast<chrono::duration<double, nano>>(mw_t2 - mw_t1).count();
    cout << "E = ";
    printMachineWord(E_word);
    cout << "Time " << mw_time_res << " nanoseconds\n";

    //             УНИВЕРСУМ
    bool bitA[UNIVERSE_SIZE], bitB[UNIVERSE_SIZE], bitC[UNIVERSE_SIZE], bitD[UNIVERSE_SIZE];
    bool bit_res1[UNIVERSE_SIZE], bit_res2[UNIVERSE_SIZE], E_bit[UNIVERSE_SIZE];

    // Отображаем строки на векторы битов
    mapToUniverse(A_arr, bitA);
    mapToUniverse(B_arr, bitB);
    mapToUniverse(C_arr, bitC);
    mapToUniverse(D_arr, bitD);

    cout << "UNIVERSE REPRESENTATION \n";
    cout << "A = ";
    printUniverse(bitA);
    cout << "B = ";
    printUniverse(bitB);
    cout << "C = ";
    printUniverse(bitC);
    cout << "D = ";
    printUniverse(bitD);
    auto uni_t1 = chrono::high_resolution_clock::now();
    intersectionSets(bitB, bitC, bit_res1);
    differenceSets(bitA, bit_res1, bit_res2);
    unionSets(bit_res2, bitD, E_bit);
    auto uni_t2 = chrono::high_resolution_clock::now();
    auto uni_time_res = chrono::duration_cast<chrono::duration<double, nano>>(uni_t2 - uni_t1).count();
    cout << "E = ";
    printUniverse(E_bit);
    cout << "Time " << uni_time_res << " nanoseconds\n";
    return 0;
}