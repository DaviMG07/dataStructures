#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <iostream>
#include <utility>
using namespace std;

const int INF = 1e9;

class Graph{
    public:
    int size;
    vector<list<int>> adj;

    Graph(int size) : size(size), adj(size){}

    void add_edge(int start, int end){
        if (start >= size || end >= size || start < 0 || end < 0 || start == end) return;
        for (auto i : adj[start]){
            if (i == end) return;
        }
        adj[start].push_back(end);
    }

    void print(){
        for (int i = 0; i < size; ++i){
            cout << (char)(i + 65);
            for (auto j : adj[i]){
                cout << " -> " << (char)(j + 65);
            }
            cout << endl;
        }
    }

    void bfs(int start){
        vector<bool> visited(size);
        queue<int> q;
        int curr;

        visited[start] = true;
        q.push(start);

        while (!q.empty()){
            curr = q.front();
            q.pop();
            cout << (char)(curr + 65) << " ";

            for (auto i : adj[curr]){
                if (!visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void dfs(int start){
        vector<bool> visited(size);
        stack<int> s;
        int curr;

        visited[start] = true;
        s.push(start);

        while (!s.empty()){
            curr = s.top();
            s.pop();
            cout << (char)(curr + 65) << " ";

            for (auto i : adj[curr]){
                if (!visited[i]){
                    s.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }
};

int main(){
    srand(time(nullptr));
    system("cls||clear");
    int sz;
    cout << "Enter the size of the graph: ";
    cin >> sz;
    Graph graph(sz);
    for (int i = 0; i < (sz * sz); ++i){
        int x = rand() %  sz;
        int y = rand() % sz;
        graph.add_edge(x, y);
    }
    graph.print();
    graph.bfs(0);
    graph.dfs(0);
    return 0;
}