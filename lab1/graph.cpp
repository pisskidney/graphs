#include<stdlib.h>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>


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
    unordered_set<long int> vertices;
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

            for(int i = 0; i < nr_edges; ++i) {
                Edge e;
                ifs >> e.from >> e.to >> e.cost;
                vertices.insert(e.to);
                vertices.insert(e.from);
                add_edge(e);
            }
        }

        long int indegree(long int v) {
            return in[v].size();
        }

        long int outdegree(long int v) {
            return out[v].size();
        }

        void back_bfs(int from, int to) {
            vector<int> visited;
            queue<int> to_visit;
            int path[vertices.size()];

            int current;

            to_visit.push(to);

            while (!to_visit.empty()) {
                current = to_visit.front();
                to_visit.pop();
                visited.push_back(current);
                for (auto e_id : in[current]) {
                    if (find(visited.begin(), visited.end(), edges[e_id].from) == visited.end()) {
                        to_visit.push(edges[e_id].from);
                        path[edges[e_id].from] = edges[e_id].to;
                    }

                    if (edges[e_id].from == from) {
                        cout << "Found a shortest path: " << endl;
                        cout << "Path: ";
                        unsigned int fromm = from;
                        while (fromm != to) {
                            cout << fromm << " ";
                            fromm = path[fromm];
                        }
                        cout << to << endl;
                    }
                }
            }
        }
};
