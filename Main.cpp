#include "fastlist.hpp"

using namespace std;

int main() {
    srand(time(nullptr));
    fast_list<int> fl;
    int num;
    fl.push_front(17);
    fl.print();
    cout << fl.pop_back() << endl;
    for (int i = 0; i < 20; ++i) {
        num = rand() % 50 + 1;
        fl.push_back(num);
        cout << num << ' ';
    }
    fl.print();
    for (int i = 0; i < 21; ++i) {
        try {
            cout << fl.pop_back() << ' ';
        } catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
