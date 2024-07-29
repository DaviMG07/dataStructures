#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

class Graph {
public:
    std::map<std::pair<std::string, std::string>, int> adj;
    std::set<std::string> vertices;

    void add_edge(const std::string& src, const std::string& dst, int weight) {
        if (src == dst) return;
        adj[{src, dst}] = weight;
        vertices.insert(src);
        vertices.insert(dst);
    }

    void save_to_graphviz(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "digraph G {" << std::endl;

        // Write nodes
        for (const auto& vertex : vertices) {
            file << "    " << vertex << ";" << std::endl;
        }

        // Write edges
        for (const auto& edge : adj) {
            file << "    " << edge.first.first << " -> " << edge.first.second;
            file << " [label=\"" << edge.second << "\"];" << std::endl;
        }

        file << "}" << std::endl;
        file.close();
    }
};

int main() {
    Graph graph;
    graph.add_edge("A", "B", 5);
    graph.add_edge("A", "C", 3);
    graph.add_edge("B", "C", 2);
    graph.add_edge("C", "D", 4);
    graph.add_edge("D", "A", 1);

    graph.save_to_graphviz("graph.dot");

    std::cout << "Graphviz file 'graph.dot' created successfully." << std::endl;

    return 0;
}

