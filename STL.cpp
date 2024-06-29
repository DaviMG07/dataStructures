#include <bits/stdc++.h>
using namespace std;

void learningPair(){
    pair<int, int> p;
    p.first = 10;
    p.second = p.first / 2;
    cout << p.first << p.second << endl;

    pair<string, int> x = {"a", 10};
    cout << x.first << x.second << endl;

    pair<string, pair<int, int>> pS = {"b", {10, 20}};
    cout << pS.first << pS.second.first << pS.second.second << endl;
}

void learningVector(){
    vector<int> v = {0, 10, 2};
    cout << v.size() << endl;
}

int main(void){
    srand(time(nullptr));
    system("cls||clear");

    learningPair();
    learningVector();

    cout << endl;
    return 0;
}