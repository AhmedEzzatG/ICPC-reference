enum DIR {
	L, R
};

template<typename T>
struct cartesian_tree {
	static cartesian_tree<T> *sentinel;
	T key;
	int priority = 0, frequency = 0, size = 0;
	cartesian_tree *child[2];
	cartesian_tree() {
		key = T();
		priority = 0;
		child[L] = child[R] = this;
	}
	cartesian_tree(const T &x, int y) :
			key(x), priority(y) {
		size = frequency = 1;
		child[L] = child[R] = sentinel;
	}
	void push_down() {

	}
	void push_up() {
		size = child[L]->size + child[R]->size + frequency;
	}
};

template<typename T>
cartesian_tree<T> *cartesian_tree<T>::sentinel = new cartesian_tree<T>();

template<typename T>
void split(cartesian_tree<T> *root, T key, cartesian_tree<T> *&l,
		cartesian_tree<T> *&r) {
	if (root == cartesian_tree<T>::sentinel) {
		l = r = cartesian_tree<T>::sentinel;
		return;
	}
	root->push_down();
	if (root->key <= key) {
		split(root->child[R], key, root->child[R], r);
		l = root;
	} else {
		split(root->child[L], key, l, root->child[L]);
		r = root;
	}
	root->push_up();
}

template<typename T>
cartesian_tree<T>* merge(cartesian_tree<T> *l, cartesian_tree<T> *r) {
	l->push_down();
	r->push_down();
	if (l == cartesian_tree<T>::sentinel || r == cartesian_tree<T>::sentinel)
		return (l == cartesian_tree<T>::sentinel ? r : l);
	if (l->priority > r->priority) {
		l->child[R] = merge(l->child[R], r);
		l->push_up();
		return l;
	}
	r->child[L] = merge(l, r->child[L]);
	r->push_up();
	return r;
}

template<typename T, template<typename > class cartesian_tree>
class treap {
	typedef cartesian_tree<T> node;
	typedef node *nodeptr;
#define emptyNode node::sentinel
	nodeptr root;
	void insert(nodeptr &root, nodeptr it) {
		if (root == emptyNode) {
			root = it;
		} else if (it->priority > root->priority) {
			split(root, it->key, it->child[L], it->child[R]);
			root = it;
		} else
			insert(root->child[root->key < it->key], it);
		root->push_up();
	}
	bool increment(nodeptr root, const T &key) {
		if (root == emptyNode)
			return 0;
		if (root->key == key) {
			root->frequency++;
			root->push_up();
			return root;
		}
		bool rt = increment(root->child[root->key < key], key);
		root->push_up();
		return rt;
	}
	nodeptr find(nodeptr root, const T &key) {
		if (root == emptyNode || root->key == key)
			return root;
		return find(root->child[root->key < key], key);
	}
	void erase(nodeptr &root, const T &key) {
		if (root == emptyNode)
			return;
		if (root->key == key) {
			if (--(root->frequency) == 0)
				root = merge(root->child[L], root->child[R]);
		} else
			erase(root->child[root->key < key], key);
		root->push_up();
	}
	T kth(nodeptr root, int k) {
		if (root->child[L]->size >= k)
			return kth(root->child[L], k);
		k -= root->child[L]->size;
		if (k <= root->frequency)
			return root->key;
		return kth(root->child[R], k - root->frequency);
	}
	int order_of_key(nodeptr root, const T &key) {
		if (root == emptyNode)
			return 0;
		if (key < root->key)
			return order_of_key(root->child[L], key);
		if (key == root->key)
			return root->child[L]->size;
		return root->child[L]->size + root->frequency
				+ order_of_key(root->child[R], key);
	}
public:
	treap() :
			root(emptyNode) {
	}
	void insert(const T &x) {
		if (increment(root, x)) //change it to find(x) to make it as a set
			return;
		insert(root, new node(x, rand()));
	}
	void erase(const T &x) {
		erase(root, x);
	}
	bool find(const T &x) {
		return (find(root, x) != emptyNode);
	}
	int get_kth_number(int k) {
		assert(1 <= k && k <= size());
		return kth(root, k);
	}
	int order_of_key(const T &x) {
		return order_of_key(root, x);
	}
	int size() {
		return root->size;
	}
};

int main() {
	run();
	treap<int, cartesian_tree> tp;
}
