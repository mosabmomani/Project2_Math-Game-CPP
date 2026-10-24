
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

enum enlevel { esey = 1, mid = 2, hard = 3, max_level = 4 };
enum enoptype { add = 1, sub = 2, mul = 3, div1 = 4, mix = 5 };

struct stinpot {
    short round;
    short optype;
    short level;
};

struct stresult {
    short trueansor = 0;
    short folseansor = 0;
};

int ReadPosatveNumber(string massege) {
    short number;
    do {
        cout << massege << endl;
        cin >> number;
    } while (number < 0);
    return number;
}

int RandomNumber(int from, int to) {
    int random = rand() % (to - from + 1) + from;
    return random;
}

stinpot ReadInfo() {
    stinpot inpot;
    inpot.round = ReadPosatveNumber("How many rounds do you want?");
    inpot.level = ReadPosatveNumber("Enter questions level [1] Easy, [2] Mid, [3] Hard, [4] Mix:");
    inpot.optype = ReadPosatveNumber("Enter questions type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix:");
    return inpot;
}

enoptype GetaCtualopType(enoptype optype) {
    if (optype == enoptype::mix) {
        return (enoptype)RandomNumber(1, 4);
    }
    return optype;
}

enlevel GetaCtualLevel(enlevel level) {
    if (level == enlevel::max_level) {
        return (enlevel)RandomNumber(1, 3);
    }
    return level;
}

void ChoicNumber(int& number1, int& number2, enlevel level) {
    int from = 1;
    int to = 10;

    enlevel actualLevel = GetaCtualLevel(level);

    for (int i = 1; i < actualLevel; i++) {
        to = to * 10;
        from = from * 10;
    }
    number1 = RandomNumber(from, to);
    number2 = RandomNumber(from, to);
}

float CorrectAnswer(int number1, int number2, enoptype optype) {
    switch (optype) {
    case enoptype::add:
        return number1 + number2;
    case enoptype::sub:
        return number1 - number2;
    case enoptype::mul:
        return number1 * number2;
    case enoptype::div1:
        return (number2 != 0) ? ((float)number1 / number2) : 0;
    default:
        return number1 + number2;
    }
}

bool ChechResult(float userAns, float correctAns) {
    return userAns == correctAns;
}

void PrintResult(bool check, float correct) {
    if (check) {
        cout << "Correct answer!\n";
    }
    else {
        cout << "Wrong answer! \a\n";
        cout << "The correct answer is: " << correct << "\n";
    }
}

string GetOptypeChar(enoptype optype) {
    switch (optype) {
    case enoptype::add: return "+";
    case enoptype::sub: return "-";
    case enoptype::mul: return "*";
    case enoptype::div1: return "/";
    default: return "+";
    }
}

void PrintQuestion(int number1, int number2, enoptype optype) {
    cout << number1 << endl;
    cout << number2 << " " << GetOptypeChar(optype) << endl;
    cout << "----------------\n";
}

stresult TheResult(bool check, stresult there) {
    if (check) {
        there.trueansor++;
    }
    else {
        there.folseansor++;
    }
    return there;
}

string PassOrNot(stresult theresult) {
    if (theresult.trueansor >= theresult.folseansor) {
        cout << "\nPASS \n\n";
        return "";
    }
    else {
        cout << "\nFAIL \n\n";
        return "";
    }
}

void PrintResult2(stresult there) {
    cout << "-----------------------------------\n";
    cout << "Final Results:\n";
    cout << "True answers: " << there.trueansor << endl;
    cout << "False answers: " << there.folseansor << endl;
    PassOrNot(there);
    cout << "-----------------------------------\n";
}

void GameBord() {
    stinpot inpot = ReadInfo();
    stresult there;
    int number1 = 0, number2 = 0;

    for (int i = 0; i < inpot.round; i++) {
        cout << "\nRound [" << (i + 1) << "/" << inpot.round << "]:\n";

        enoptype currentOp = GetaCtualopType((enoptype)inpot.optype);
        ChoicNumber(number1, number2, (enlevel)inpot.level);

        PrintQuestion(number1, number2, currentOp);

        float userAns;
        cin >> userAns;

        float correctAns = CorrectAnswer(number1, number2, currentOp);
        bool check = ChechResult(userAns, correctAns);

        there = TheResult(check, there);
        PrintResult(check, correctAns);
        cout << "\n";
    }
    PrintResult2(there);
}

int main() {
    srand((unsigned)time(NULL));
    GameBord();
    return 0;
}
