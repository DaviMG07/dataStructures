#include <vector>
#include <list>
#include <string>
#include <map>
#include <utility>
#include <set>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;
class Graph{
    public:
    map<pair<string, string>, int> adj;
    set<string> vertices;

    void add_edge(string src, string dst, int weight){
        if (src == dst) return;
        adj[{src, dst}] = weight;
        vertices.insert(src);
        vertices.insert(dst);
    }

    void print(){
        for (auto edge : adj){
            cout << "[" << edge.first.first << ", " << edge.first.second << "]";
            cout << edge.second;
            cout << endl;
        }
    }

    void dfs(string src){
        map<string, bool> visited;
        stack<string> s;

        s.push(src);
        visited[src] = true;

        while (!s.empty()){
            string curr = s.top();
            cout << curr << " ";
            s.pop();

            for (auto edge : adj){
                if (edge.first.first == curr && !visited[edge.first.second]){
                    s.push(edge.first.second);
                    visited[edge.first.second] = true;
                }
            }
        }
        cout << endl;
    }

    void bfs(string src){
        map<string, bool> visited;
        queue<string> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty()){
            string curr = q.front();
            cout << curr << " ";
            q.pop();

            for (auto edge : adj){
                if (edge.first.first == curr && !visited[edge.first.second]){
                    q.push(edge.first.second);
                    visited[edge.first.second] = true;
                }
            }
        }
        cout << endl;
    }
    void dijkstra(string src){
        
    }
};

int main(){
    srand(time(nullptr));
    system("clear");
    auto rand_str = [](int size){
        string str;
        for (int i = 0; i < size; ++i){
            char rand_char = (char)((rand() % 26) + 65);
            str.push_back(rand_char);
        }
        return str;
    };
    Graph g;
    for (int i = 0; i < (26 * 26); ++i){
        g.add_edge(rand_str(1), rand_str(1), (rand() % 4) + 1);
    }
    g.print();
    g.dfs("A");
    g.bfs("A");
    cout << endl;
    return 0;
}
