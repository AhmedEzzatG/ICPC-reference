#include<bits/stdc++.h>
using namespace std;

long long cnt = 0;
vector<int> v, temp;

// e the first index not have in range array
// like end()
template<class T = less<int>>
void merge_sort(int s, int e, T cmp = less<int>()) {
	if (s + 1 >= e)
		return;
	int m = s + (e - s >> 1);
	merge_sort(s, m, cmp);
	merge_sort(m, e, cmp);
	for (int i = s; i < e; i++)
		temp[i] = v[i];
	int i = s, j = m, k = s;
	while (i < m && j < e)
		if (cmp(temp[i], temp[j]))
			v[k++] = temp[i++];
		else
			v[k++] = temp[j++], cnt += j - k;
	while (i < m)
		v[k++] = temp[i++];
	while (j < e)
		v[k++] = temp[j++];
}

ll count_inversions(vector<int> &a) {
    v = a;
    temp = vector<int>(a.size());
    cnt = 0;
    merge_sort(0, a.size());
    return cnt;
}

// O(n*log(n)/log(base))
// O(n + base) memory
void radix_sort(vector<int> &v, int base) {
	vector<int> tmp(v.size());
	for (int it = 0, p = 1; it < 10; it++, p *= base) {
		vector<int> frq(base);
		for (auto &it : v)
			frq[(it / p) % base]++;
		for (int i = 1; i < base; i++)
			frq[i] += frq[i - 1];
		for (int i = v.size() - 1; i >= 0; i--)
			tmp[--frq[(v[i] / p) % base]] = v[i];
		v = tmp;
	}
}

void quick_sort(int s, int e) {
	if (s >= e)
		return;
	int j = rand() % (e - s + 1) + s;
	swap(v[s], v[j]);
	j = s;
	int pivot = v[s];
	for (int i = s + 1; i <= e; i++)
		if (v[i] <= pivot)
			swap(v[i], v[++j]);
	swap(v[s], v[j]);
	quick_sort(s, j - 1);
	quick_sort(j + 1, e);
}
