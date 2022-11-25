#include <functional>
#include <iostream>
#include <map>

using namespace std;

void doShowAllBooks() { cout << "查看所有书籍信息" << endl; }
void doBorrow() { cout << "借书" << endl; }
void doBack() { cout << "还书" << endl; }
void doQueryBooks() { cout << "查询书籍" << endl; }
void doLoginOut() { cout << "注销" << endl; }

int main() {
    int choice = 0;
    map<int, function<void()>> actionMap;
    actionMap.insert({1, doShowAllBooks});
    actionMap.insert({2, doBorrow});
    actionMap.insert({3, doBack});
    actionMap.insert({4, doQueryBooks});
    actionMap.insert({5, doLoginOut});

    for (;;) {
        cout << "-----------------" << endl;
        cout << "1.查看所有书籍信息" << endl;
        cout << "2.借书" << endl;
        cout << "3.还书" << endl;
        cout << "4.查询书籍" << endl;
        cout << "5.注销" << endl;
        cout << "-----------------" << endl;
        cout << "请选择:";
        cin >> choice;

        auto it = actionMap.find(choice);
        if (it ==  actionMap.end()) {
            cout << "输入数字无效， 重新选择!" << endl;
        } else {
            it->second();
        }

        // 不好，因为这块代码无法闭合  无法做到“开-闭原则
        // switch (choice) {
        //     case 1:
        //         break;
        //     case 2:
        //         break;
        //     case 3:
        //         break;
        //     case 4:
        //         break;
        //     case 5:
        //         break;
        //     default:
        //         break;
        // }
    }
}