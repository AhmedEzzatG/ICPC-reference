#include<bits/stdc++.h>
using namespace std;

//zero based SQRT_Decomposition with lazy propagation
template<typename update_type, typename query_type>
class SQRT_Decomposition {
	struct Bucket {
		int l, r;
		update_type lazy;
		Bucket(int l, int r) :
				l(l), r(r) {
			//set default value to lazy
			//build bucket for the first time
		}
		void build() {
			//update all bucket with lazy if have
			//rebuild the bucket
			//clear lazy
		}
		//update all bucket
		void update(const update_type &val) {
			//just update lazy
		}
		//update range in bucket
		void update(int start, int end, const update_type &val) {
			if (start == l && end == r) {
				update(val);
				return;
			}
			//update bucket
			//rebuild the bucket if need
		}
		//query about all bucket
		query_type query() {
			//calc with lazy
		}
		//query about range in bucket
		query_type query(int start, int end) {
			if (start == l && end == r)
				return query();
			//push lazy if have
			//calc
		}
	};

	int n, sqrtN;
	vector<Bucket> bucket;
	int begin(int idx) {
		return idx * sqrtN;
	}
	int end(int idx) {
		return min(sqrtN * (idx + 1), n) - 1;
	}
	int which_block(int idx) {
		return idx / sqrtN;
	}
public:
	SQRT_Decomposition(int n) {
		this->n = n;
		sqrtN = sqrt(n);
		for (int i = 0; i < n; i += sqrtN)
			bucket.push_back(Bucket(i, min(i + sqrtN, n) - 1));
	}

	void update(int left, int right, update_type val) {
		int st = which_block(left), ed = which_block(right);
		bucket[st].update(left, min(bucket[st].r, right), val);
		for (int i = st + 1; i < ed; i++)
			bucket[i].update(val);
		if (st != ed)
			bucket[ed].update(bucket[ed].l, right, val);
	}

	query_type query(int left, int right) {
		int st = which_block(left), ed = which_block(right);
		query_type rt = bucket[st].query(left, min(bucket[st].r, right));
		for (int i = st + 1; i < ed; i++)
			rt += bucket[i].query();
		if (st != ed)
			rt += bucket[ed].query(bucket[ed].l, right);
		return rt;
	}
};
