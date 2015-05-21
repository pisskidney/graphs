#include <climits>
#include "../graph.cpp"

#define MAX 9;


void fill_adj_matrix(int** adj, DirectedGraph g) {
    int n = g.nr_vertices();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i == j) {
                adj[i][j] = 0;
            } else {
                long int e = g.get_edge(i, j);
                if (e == -1) {
                    adj[i][j] = MAX;
                } else {
                    adj[i][j] = g.get_edge(e).cost;
                }
            }
}


void mult(int** adj, int** d, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int neww = d[i][k] + adj[k][j];
                d[i][j] = (d[i][j] < neww) ? d[i][j] : neww;
            }
        }
    }
}


int shortest_path(DirectedGraph dg, int v1, int v2) {
    int n = dg.nr_vertices();

    // Init adjiacency matrix
    int ** adj;
    adj = new int* [n];
    for (int i = 0; i < n; ++i) {
        adj[i] = new int [n];
    }

    fill_adj_matrix(adj, dg);

    // Init distance matrix
    int ** d;
    d = new int* [n];
    for (int i = 0; i < n; ++i) {
        d[i] = new int [n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = (i == j) ? 0 : MAX;
        }
    }

    // Matrix Multiplication ASPS Algorithm
    for (int i = 0; i < n - 2; ++i) {
        mult(adj, d, n);
    }

    // Check for negative cost cycles
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int neww = d[i][k] + adj[k][j];
                if (neww < d[i][j]) {
                    cout << "NEGATIVE COST CYCLE DETECTED!" << endl;
                    return -1;
                }
            }
        }
    }

    return d[v1][v2];
}


int main() {
    DirectedGraph dg = DirectedGraph("graph_apsp.txt");
    cout << "Shortest path between 1 and 5: " << shortest_path(dg, 1, 5) << endl;
    cout << "Shortest path between 0 and 5: " << shortest_path(dg, 0, 5) << endl;
    cout << "---------------------------------" << endl;

    DirectedGraph dg2 = DirectedGraph("graph_apsp2.txt");
    cout << "Shortest path between 1 and 5: " << shortest_path(dg2, 1, 5) << endl;
    cout << "Shortest path between 0 and 5: " << shortest_path(dg2, 0, 5) << endl;
    return 0;
}
