#include "../graph.cpp"
#include<deque>

vector<vector<int>> all;

void perm(vector<int> a, int k) {
    if (k >= a.size()) {
        all.push_back(a);
        return;
    }
    for (int i = k; i < a.size(); ++i) {
        int aux = a[i];
        a[i] = a[0];
        a[0] = aux;
        perm(a, k + 1);
    }
}


void tsp(DirectedGraph dg) {
    int best = 0;
    int besti = 0;
    for (int i = 0; i < all.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < all[i].size() - 1; ++j) {
            sum += (dg.edges[dg.get_edge(all[i][j], all[i][j+1])]).cost;
        }
        if (best < sum) {
            best = sum;
            besti = i;
        }
    }
    cout << "Best path: ";
    for (int i = 0; i < all[besti].size(); ++i) cout << all[besti][i] << " ";

    cout << endl <<"Cost: " << best << endl;
}


int main() {
    DirectedGraph dg = DirectedGraph("tsp.txt");

    vector<int> a;
    for (int i = 0; i < dg.nr_vertices(); ++i) {
        a.push_back(i);
    }
    perm(a, 0);
    tsp(dg);

    return 0;
}
