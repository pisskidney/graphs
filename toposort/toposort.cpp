#include "../graph.cpp"
#include<deque>


class Activity {
    public:
        int label;
        vector<int> pre;
        int duration;
        Activity(int l, vector<int> p, int d): label(l), pre(p), duration(d) {} 
};


class ActivityManager {
    public:
        vector<Activity> activities;
        ActivityManager(string file) {
            ifstream ifs;
            ifs.open(file, ifstream::in);
            int nr_activities;
            ifs >> nr_activities;
            for (int i = 0; i < nr_activities; ++i) {
                int l;
                int nr_p;
                vector<int> p;
                int d;
                ifs >> l;
                ifs >> d;
                ifs >> nr_p;
                for (int j = 0; j < nr_p; ++j) {
                    int p_l;
                    ifs >> p_l;
                    p.push_back(p_l);
                }
                Activity a = Activity(l, p, d);
                activities.push_back(a);
            }
        }

        void print () {
            cout << "--------------------";
            cout << endl;
            for (int i = 0; i < activities.size(); ++i) {
                cout << activities[i].label << "; pre: ";
                for (int j = 0; j < activities[i].pre.size(); ++j) {
                    cout << activities[i].pre[j] << " ";
                }
                cout << "; duration=" << activities[i].duration;
                cout << endl;
            }
            cout << "--------------------";
            cout << endl;
        }

        DirectedGraph to_dg() {
            DirectedGraph dg;
            for (int i = 0; i < activities.size(); ++i) {
                for (int j = 0; j < activities[i].pre.size(); ++j) {
                    Edge e;
                    e.from = activities[i].pre[j];
                    e.to = activities[i].label;
                    dg.add_vertex(e.to);
                    dg.add_vertex(e.from);
                    dg.add_edge(e);
                }
            }
            return dg;
        }

        int get_duration(int a) {
            for (int i = 0; i < activities.size(); ++i) {
                if (activities[i].label == a) {
                    return activities[i].duration;
                }
            }
            cout << "INVALID ACTIVITY!";
            return -1;
        }

        void topological_sort(DirectedGraph dg) {
            deque<int> dq;
            vector<int> dist;
            vector<int> indegree;
            vector<int> sorted;
            vector<int> durations;
            vector<int> finish;
            vector<int> latest;
            vector<int> critical;

            for (int i = 0; i < dg.nr_vertices(); ++i) {
                dist.push_back(0);
            }
            for (int i = 0; i < dg.nr_vertices(); ++i) {
                finish.push_back(0);
            }
            for (int i = 0; i < dg.nr_vertices(); ++i) {
                indegree.push_back(0);
            }
            for (int i = 0; i < dg.nr_vertices(); ++i) {
                indegree[i] = dg.indegree(i);
            }
            for (int i = 0; i < dg.nr_vertices(); ++i) {
                if (indegree[i] == 0) {
                    dq.push_back(i);
                    sorted.push_back(i);
                    finish[i] = get_duration(i);
                }
            }

            while (!dq.empty()) {
                int v = dq.front();
                dq.pop_front();
                for (int i = 0; i < dg.out[v].size(); ++i) {
                    Edge e = dg.edges[dg.out[v][i]];
                    int u = e.to;
                    if (dist[u] < dist[v] + get_duration(v)) {
                        dist[u] = dist[v] + get_duration(v);
                    }
                    if (finish[u] < finish[v] + get_duration(u)) {
                        finish[u] = finish[v] + get_duration(u);
                    }
                    indegree[u] -= 1;
                    if (indegree[u] == 0) {
                        dq.push_back(u);
                        sorted.push_back(u);
                    }
                }
            }

            cout << endl;
            cout << "Shortest starting times: ";
            for (int i = 0; i < dist.size(); ++i){
                cout << i << ":"<< dist[i] << ", ";
            }

            for (int i = 0; i < dg.nr_vertices(); ++i) {
                latest.push_back(0);
            }
            cout << endl;
            int last = 0;
            int maxx = 0;
            for (int i = 0; i < finish.size(); ++i){
                if (finish[i] > maxx) {
                    maxx = finish[i];
                    last = i;
                }
            }
            deque<int> back;
            back.push_back(last);
            latest[last] = dist[last];
            while (!back.empty()) {
                int v = back.front();
                back.pop_front();
                for (int i = 0; i < dg.in[v].size(); ++i) {
                    Edge e = dg.edges[dg.in[v][i]];
                    int u = e.from;
                    if (finish[u] < latest[v]) {
                        latest[u] = dist[u] + latest[v] - finish[u];
                       
                    } else {
                        latest[u] = dist[u];
                        critical.push_back(u);
                    }
                    back.push_back(u);
                }
            }

            cout << "Latest starting times: ";
            for (int i = 0; i < latest.size(); ++i){
                cout << i << ":"<< latest[i] << ", ";
            }
            cout << endl;

            cout << "Finish time: " << maxx;
            cout << endl;
            cout << "Topological sort: ";
            for (int i = 0;i<sorted.size();i++) cout<<sorted[i]<<" ";
            cout << endl;

            cout << "Critical points: ";
            cout << last << ", ";
            for (int i = 0; i < critical.size(); ++i){
                cout << critical[i] << ", ";
            }
            cout << endl;
        }
};


int main() {
    ActivityManager am = ActivityManager("activities.txt");
    DirectedGraph dg = am.to_dg();
    am.topological_sort(dg);

    return 0;

}
