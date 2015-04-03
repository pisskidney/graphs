#include<stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<unordered_map>


using namespace std;


class Edge {
    public:
        unsigned long int id, from, to;
        int cost;
        Edge(): id(-1), from(-1), to(-1), cost(-1) {}
        Edge(int from, int to, int cost): from(from), to(to), cost(cost) {}
        void set_id(unsigned long int new_id) {
            id = new_id;
        }
};


class DirectedGraph {
    vector<long int> vertices;
    vector<Edge> edges;
    unordered_map<int, vector<long int>> in;
    unordered_map<int, vector<long int>> out;
    
    public:
        long int nr_vertices() {
            return vertices.size();
        }

        long int nr_edges() {
            return edges.size();
        }

        void print_edges() {
            for (auto e : edges) {
                cout << "id: " << e.id;
                cout << " | from: " << e.from;
                cout << " | to: " << e.to;
                cout << " | cost: " << e.cost;
                cout << "\n";
            }
        }

        long int get_edge(long int v1, long int v2) {
            for (auto edge_id : in[v1]) {
                if (edges[edge_id].from == v2) return edge_id;
            }
            for (auto edge_id : in[v2]) {
                if (edges[edge_id].from == v1) return edge_id;
            }
            return -1;
        }

        Edge get_edge(long int id) {
            return edges[id];

        }

        void add_edge(Edge e) {
            e.id = edges.size();
            edges.push_back(e);
            in[e.to].push_back(e.id);
            out[e.from].push_back(e.id);
        }

        DirectedGraph(string file) {
            long int nr_vertices, nr_edges;
            ifstream ifs;
            ifs.open(file, ifstream::in);
            ifs >> nr_vertices;
            ifs >> nr_edges;

            for(int i = 0; i < nr_vertices; ++i) vertices.push_back(i);

            for(int i = 0; i < nr_edges; ++i) {
                Edge e;
                ifs >> e.from >> e.to >> e.cost;
                add_edge(e);
            }
        }

        long int indegree(long int v) {
            return in[v].size();
        }

        long int outdegree(long int v) {
            return out[v].size();
        }
};


int main() {
    DirectedGraph dg("graph.txt");
    cout << "vertices: " << dg.nr_vertices() << endl;
    dg.print_edges();
    cout << dg.get_edge(1, 2) << endl;
    cout << dg.get_edge(2, 1) << endl;
    cout << dg.get_edge(5, 1) << endl;
    cout << "in degree of 2: " << dg.indegree(2) << endl;
    cout << "out degree of 2: " << dg.outdegree(2) << endl;

    return 1;
}
