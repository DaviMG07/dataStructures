#include <vector>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <utility>
#include <set>
#include <iostream>
using namespace std;

class Graph{
    public:
        set<string> vertices;
        map<pair<string, string>, int> adj;

        void add_edge(const string& src, const string& dst, const int& weight){
            if (src == dst) return;
            adj[{src, dst}] = weight;
            vertices.insert(src);
            vertices.insert(dst);
        }
};

string rand_str(int size = 5){
    string new_str;
    for (int i = 0; i < size; ++i){
        new_str.push_back((char)((rand() % 26) + 97));
    }
    return new_str;
}

int main(){
    srand(time(nullptr));
    system("clear");
    cout << rand_str(100);
    cout << endl;
    return 0;
}
