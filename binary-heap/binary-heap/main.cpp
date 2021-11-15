// LG P3378
#include <iostream>

using namespace std;

template<typename T, int SIZE = 100, typename Comp=less<T>>
class binary_heap
{
public:
	binary_heap() = default;

	~binary_heap() = default;

	binary_heap(const binary_heap&) = delete;

	binary_heap(binary_heap&&) = delete;

	binary_heap& operator=(const binary_heap&) = delete;

public:
	void push(T x)
	{
		data_[size_++] = x;
		up(size_ - 1);
	}

	T top()
	{
		return data_[0];
	}

	void pop()
	{
		swap(data_[0], data_[size_ - 1]);
		size_--;
		down(0);
	}

	int size()
	{
		return size_;
	}

private:
	static inline constexpr int PARENT(int c)
	{
		return (c - 1) / 2;
	}

	static inline constexpr int LEFT(int c)
	{
		return c * 2 + 1;
	}

	static inline constexpr int RIGHT(int c)
	{
		return c * 2 + 2;
	}

	void down(int p)
	{
		int l = LEFT(p), r = RIGHT(p), root = p;
		if (l < size_ && cmp_(data_[l], data_[root]))
		{
			root = l;
		}

		if (r < size_ && cmp_(data_[r], data_[root]))
		{
			root = r;
		}

		if (root != p)
		{
			swap(data_[root], data_[p]);
			down(root);
		}
	}

	void up(int p)
	{
		for (int cur = p; cur >= 0 && cmp_(data_[cur], data_[PARENT(cur)]); cur = PARENT(cur))
		{
			swap(data_[cur], data_[PARENT(cur)]);
		}
	}

	T data_[SIZE]{};
	int size_{};
	Comp cmp_{};
};

binary_heap<int, 1000100> bh;


int main()
{
	int n = 0;
	cin >> n;
	while (n-- > 0)
	{
		int op = 0;
		cin >> op;
		if (op == 1)
		{
			int x = 0;
			cin >> x;
			bh.push(x);
		}
		else if (op == 2)
		{
			cout << bh.top() << endl;
		}
		else if (op == 3)
		{
			bh.pop();
		}
	}
	return 0;
}
