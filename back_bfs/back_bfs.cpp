#include "../graph.cpp"

int main() {
    DirectedGraph g = DirectedGraph("graph2.txt");
    g.back_bfs(1, 6);
}
