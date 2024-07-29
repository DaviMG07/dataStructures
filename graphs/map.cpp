#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <list>
#include <iostream>
using namespace std;

class Graph{
    public:
    int size;
    map<string, list<string>> adj;

    Graph(int size) : size(size) {}

    void add_edge(string start, string end){
        for (auto i : adj){
            for (auto j : i.second){
                if (j == end) return;
            }
        }
        adj[start].push_back(end);
    }

    void print(){
        for (auto i : adj){
            cout << i.first;
            for (auto j : i.second){
                cout << " -> " << j;
            }
            cout << endl;
        }
    }

    void bfs(string start){
        map<string, bool> visited;
        queue<string> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()){
            string curr = q.front();
            cout << curr << " ";
            q.pop();

            for (auto neighbor : adj[curr]){
                if (!visited[neighbor]){
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    void dfs(string start){
        map<string, bool> visited;
        stack<string> s;

        visited[start] = true;
        s.push(start);

        while (!s.empty()){
            string curr = s.top();
            cout << curr << " ";
            s.pop();

            for (auto neighbor : adj[curr]){
                if (!visited[neighbor]){
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main(){
    srand(time(nullptr));
    system("cls||clear");
    auto rand_str = [](int size){
        string str;
        for (int i = 0; i < size; ++i){
            int x = rand() % 26;
            str.push_back((char)(x + 65));
        }
        return str;
    };
    Graph graph(5);
    for (int i = 0; i < (graph.size * graph.size); ++i){
        graph.add_edge(rand_str(1), rand_str(1));
    }
    graph.print();
    return 0;
}