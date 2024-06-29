#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int key;
    int value;
};

using matrix = vector<vector<int>>;

class Graph{
    private:
        matrix table;
        vector<string> keys;
    public:
        int vertices;
    Graph(int numVertices){
        vertices = numVertices;
        table.resize(vertices, vector<int>(vertices, 0));
        keys.resize(vertices);
        for (int i = 0; i < vertices; ++i){
            keys[i] = i + 65;
        }
    }
    void addEdge(int u, int v){
        if (u >= 0 && u < vertices && v >= 0 && u < vertices && v != u){
            table[u][v] = 1;
        }
    }
    void display(){
        for (int i = 0; i < vertices; ++i){
            for (int j = 0; j < vertices; ++j){
                if (table[i][j]){
                    cout << keys[i] << " --> " << keys[j] << endl;
                }
            }
        }
    }
    void printTable(){
        cout << "  ";
        for (int q = 0; q < vertices; ++q){
            cout << keys[q] << " ";
        }
        cout << endl;
        for (int i = 0; i < vertices; ++ i){
            cout << keys[i] << " ";
            for (int j = 0; j < vertices; ++j){
                if (table[i][j]) cout << "x ";
                else cout << "· ";
            }
            cout << endl;
        }
    }
};

int main(void){
    srand(time(nullptr));
    system("cls||clear");

    Graph graph(20);
    for (int i = 0; i < 100; ++i){
        graph.addEdge(rand() % graph.vertices, rand() % graph.vertices);
    }
    graph.printTable();
    cout << endl;
    return 0;
}