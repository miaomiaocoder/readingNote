#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
关联容器：
1.各个容器底层的数据结构 O(1)  O(log2n)
2.常用增删查方法
增加：insert(val)
遍历：iterator自己搜索， 调用find成员方法
删除：erase(key)  erase(it)
*/
int main() {
    //// 处理海量数据查重复；去重复的时候
    // const int ARR_LEN = 100;
    // int arr[ARR_LEN] = { 0 };
    // for (int i = 0; i < ARR_LEN; ++i)
    //{
    //	arr[i] = rand() % 20 + 1;
    // }

    //// 上面的10万个整数中，把数字进行去重打印  set  map
    // unordered_set<int> set;
    // for (int v : arr) // O(n)
    //{
    //	set.insert(v); // O(1)
    // }

    // for (int v : set)
    //{
    //	cout << v << " ";
    // }
    // cout << endl;

#if 0
	// 上面的10万个整数中，统计哪些数字重复了，并且统计数字重复的次数
	unordered_map<int, int> map1;
	for (int k : arr)
	{
		/*
		auto it = map1.find(k);
		if (it == map1.end())
		{
			map1.insert({k, 1});
		}
		else
		{
			it->second++;
		}
		*/
		map1[k]++; // map1[k]  [k, 1]
	}

	/*
	for (const pair<int, int> &p : map1)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
	*/

	auto it = map1.begin();
	for (; it != map1.end(); ++it)
	{
		if (it->second > 1)
		{
			cout << "key:" << it->first <<
				" count:" << it->second << endl;
		}
	}
#endif

    /*
    [key, value]
    struct pair
    {
     first; => key
     second; => value
    }

    map的operator[]
    1.查询
    2.如果key不存在，它会插入一对数据[key, string()]
    V& operator[](const K &key)
    {
            insert({key, V()});
    }
    */

    /*
    unordered_map<int, string> map1;
    map1.insert(make_pair(1000, "张三"));
    map1.insert({1010, "李四"}); // map表增加元素
    map1.insert({1020, "王五" });
    map1.insert({1030, "王凯" });
    map1.erase(1020); // {1020, "王五" }删除了

    auto it1 = map1.find(1030);
    if (it1 != map1.end())
    {
            // it1 -> pair对象
            cout << "key:" << it1->first << " value:" << it1->second << endl;
    }

    //map1[2000]; // key:2000 value:""
    //map1[2000] = "刘硕"; // map1.insert({2000, "刘硕"});
    //map1[1000] = "张三2"; //
    //cout << map1.size() << endl;
    // map operator[](key) => value  查询
    //cout << map1[1000] << endl;
    */

    unordered_set<int> set1;  // 不会存储key值重复的元素
    for (int i = 0; i < 50; ++i) {
        set1.insert(rand() % 20 + 1);  // vector/deque/list  insert(it, val)
    }

    cout << set1.size() << endl;
    cout << set1.count(15) << endl;

    auto it1 = set1.begin();
    for (; it1 != set1.end(); ++it1) {
        cout << *it1 << " ";
    }
    cout << endl;

    set1.erase(20);  // 按key值删除元素

    for (it1 = set1.begin(); it1 != set1.end();) {
        if (*it1 == 30) {
            it1 = set1.erase(it1);  // 调用erase，it1迭代器就失效了
        } else {
            ++it1;
        }
    }

    it1 = set1.find(20);
    if (it1 != set1.end()) {
        set1.erase(it1);
    }

    for (int v : set1) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}