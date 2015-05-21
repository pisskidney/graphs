#include "../graph.cpp"


class Activity {
    public:
        char label;
        vector<char> pre;
        int duration;
        Activity(char l, vector<char> p, int d): label(l), pre(p), duration(d) {} 
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
                char l;
                int nr_p;
                vector<char> p;
                int d;
                ifs >> l;
                ifs >> d;
                ifs >> nr_p;
                for (int j = 0; j < nr_p; ++j) {
                    char p_l;
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
                cout << endl;
            }
            cout << "--------------------";
            cout << endl;
        }

        void topological_sort() {
            vector<Activity> sorted;
            vector<Activity> same;
            int timee = 0;

            cout << "LOL";
            

            for (int i = 0; i < activities.size(); ++i) {
                Activity a = Activity(activities[i].label, activities[i].pre, activities[i].duration);
                same.push_back(a);
            }

            //while (sorted.size() < activities.size()) {
                vector<Activity> topush;
                for (int i = 0; i < same.size(); ++i) {
                    if (same[i].pre.size() == 0) {
                        topush.push_back(same[i]);
                    }
                }

                for(int i = 0; i < topush.size(); ++i)
                    cout << topush[i].label;
                cout << topush.size();

                for (int i = 0; i < topush.size(); ++i) {
                    int latest = timee;
                    for (int j = 0; j < topush.size(); ++j)
                        if (i != j)
                            latest += topush[j].duration;
                    cout << topush[i].label << ": Earliest:"<<timee<<", Latest:"<<latest<<endl;
                }
                /*
                for (int i = 0; i < topush.size(); ++i) {
                    sorted.push_back(topush[i]);
                    timee += topush[i].duration;
                    vector<Activity>::iterator it1 = same.begin();
                    while (it1 != same.end()) {
                        if ((*it1).pre.size() == 0) {
                            it1 = same.erase(it1);
                        } else {
                            vector<char>::iterator it2 = (*it1).pre.begin();
                            while (it2 != (*it1).pre.end()) {
                                if (*it2 == topush[i].label)
                                    it2 = (*it1).pre.erase(it2);
                            }
                        }
                    }
                }
                */
            //}
            
        }
};


int main() {
    ActivityManager am = ActivityManager("activities.txt");
    am.print();
    am.topological_sort();


    return 0;

}
