#include <vector>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

template <typename T>
using matrix = vector<vector<T>>;

class Graph{
    public:
    int size;
    matrix<int> adj;

    Graph (int size) : size(size), adj(size, vector<int>(size, 0)) {}

    void print(){
        cout << "  ";
        for (int i = 0; i < size; ++i){
            cout << (char)(i + 65) << " ";
        }
        cout << endl;
        for (int p = 0; p < size; ++p){
            cout << (char)(p + 65) << " ";
            for (int q = 0; q < size; ++q){
              if (adj[p][q]) cout << "• ";
              else cout << "  ";
            }
            cout << endl;
        }
    }

    void addEdge(int start, int end){
        if (start >= size || end >= size || start < 0 || end < 0 || start == end) return;
        adj[start][end] = 1;
    }

    void bfs(int start){
        vector<bool> visited(size, false);
        queue<int> q;
        int curr;

        visited[start] = true;
        q.push(start);
        cout << "  ";

        while (!q.empty()){
            curr = q.front();
            cout << (char)(curr + 65) << " ";
            q.pop();

            for (int i = 0; i < size; ++i){
                if (adj[curr][i] && !visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void dfs(int start){
        vector<bool> visited(size, false);
        stack<int> s;
        int curr;

        visited[start] = true;
        s.push(start);
        cout << "  ";

        while (!s.empty()){
            curr = s.top();
            cout << (char)(curr + 65) << " ";
            s.pop();

            for (int i = 0; i < size; ++i){
                if (adj[curr][i] && !visited[i]){
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
    cout << "Enter graph size: ";
    cin >> sz;
    Graph graph(sz);

    for (int i = 0; i < (graph.size * graph.size); ++i){
        int x = rand() % graph.size;
        int y = rand() % graph.size;
        graph.addEdge(x, y);
    }
    graph.print();
    graph.bfs(0);
    graph.dfs(0);
    return 0;
}
