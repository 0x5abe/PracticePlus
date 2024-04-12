namespace util::math {
	inline int mod(int k, int n) {
		return ((k %= n) < 0) ? k+n : k;
	}
}