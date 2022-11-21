// 使用无序关联容器包含的头文件
#include <iostream>
#include <string>

// 使用有序关联容器包含的头文件  红黑树
#include <map>  // map multimap
#include <set>  // set multiset
using namespace std;

// class Student
//{
// public:
//	Student(int id = 0, string name = "")
//		:_id(id), _name(name) {}
// private:
//	int _id;
//	string _name;
//	friend ostream& operator<<(ostream& out, const Student& stu);
// };
// ostream& operator<<(ostream& out, const Student& stu)
//{
//	out << "id:" << stu._id << " name:" << stu._name << endl;
//	return out;
// }
// int main()
//{
//	map<int, Student> stuMap;
//	stuMap.insert({ 1000, Student(1000, "张雯") });
//	stuMap.insert({ 1020, Student(1020, "李广") });
//	stuMap.insert({ 1030, Student(1030, "高洋") });
//
//	// stuMap.erase(it) stuMap.erase(1020)  stuMap[2000] [2000, V()]
//	// cout << stuMap[1020] << endl;   stuMap.find(key)
//	auto it = stuMap.begin();
//	for (; it != stuMap.end(); ++it)
//	{
//		cout << "key:" << it->first << " value:" << it->second << endl;
//	}
//	cout << endl;
//
//	return 0;
// }

class Student {
   public:
    Student(int id, string name) : _id(id), _name(name) {}
    bool operator<(const Student& stu) const { return _id < stu._id; }

   private:
    int _id;
    string _name;
    friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu) {
    out << "id:" << stu._id << " name:" << stu._name << endl;
    return out;
}
int main() {
    set<Student> set1;

    set1.insert(Student(1020, "李广"));
    set1.insert(Student(1000, "张雯"));

    for (auto it = set1.begin(); it != set1.end(); ++it) {
        cout << *it << endl;
    }

    /*set<int> set1;
    for (int i = 0; i < 20; ++i)
    {
            set1.insert(rand()%20+1);
    }

    for (int v : set1)
    {
            cout << v << " ";
    }
    cout << endl;*/

    return 0;
}