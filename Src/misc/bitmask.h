bool getBit(ll num, int ind) {
	return ((num >> ind) & 1);
}
ll setBit(ll num, int ind, bool val) {
	return val ? (num | (1LL << ind)) : (num & ~(1LL << ind));
}
ll flipBit(ll num, int ind) {
	return (num ^ (1LL << ind));
}
ll leastBit(ll num) {
	return (num & -num);
}
template<class Int>
Int turnOnLastZero(Int num) {
	return num | num + 1;
}
template<class Int>
Int turnOnLastConsecutiveZeroes(Int num) {
	return num | num - 1;
}
template<class Int>
Int turnOffLastBit(Int num) {
	return num & num - 1;
}
template<class Int>
Int turnOffLastConsecutiveBits(Int num) {
	return num & num + 1;
}
//num%mod, mod is a power of 2
ll Mod(ll num, ll mod) {
	return (num & mod - 1);
}
bool isPowerOfTwo(ll num) {
	return (num & num - 1) == 0;
}
void genAllSubmask(int mask) {
	for (int subMask = mask;; subMask = (subMask - 1) & mask) {
		//code
		if (subMask == 0)
			break;
	}
}
/*
 * __builtin functions:
 *  __builtin_popcount -> used to count the number of one’s
 *  __builtin_clz -> used to count the leading zeros of the integer
 *  __builtin_ctz -> used to count the trailing zeros of the integer
 *
 */
// for run __builtin_popcount in visual
#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
#ifdef _WIN64
#define __builtin_popcountll __popcnt64
#else
inline int __builtin_popcountll(__int64 a) {
	return __builtin_popcount((unsigned int)a) + __builtin_popcount(a >> 32);
}
#endif
#endif
int LOG2(int x) { //floor(log2(x))
	return 31 - __builtin_clz(x);
}

int LOG2(long long x) { //floor(log2(x))
	return 63 - __builtin_clzll(x);
}
