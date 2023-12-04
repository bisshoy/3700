#ifndef _BST_DICTIONARY_H
#define _BST_DICTIONARY_H

#include <cstdint>
#include <stdexcept>
#include <algorithm>

static const uint32_t
	NULL_INDEX = 0xffffffff,
	DEFAULT_INITIAL_CAPACITY = 16;

template<typename KeyType, typename ValueType>
class BSTDictionary {
public:
	explicit BSTDictionary(uint32_t _cap = DEFAULT_INITIAL_CAPACITY) {
		// if nTrees = 0 
		if (nTrees == 0) {
			// Allocate space for the six arrays 
			counts  = new uint32_t[_cap];
			heights = new uint32_t[_cap];
			left    = new uint32_t[_cap];
			right   = new uint32_t[_cap];
			keys    = new KeyType[_cap];
			values  = new ValueType[_cap];
			
			// capacity = cap
			capacity = _cap;

			// Generate the free list 
			// for i <- start to end - 1
			for (int i = 0; i < capacity - 1; i++) {
				// left[i] <- i + 1
				left[i] = i + 1;
			} // end for 

			// left[end] <- NULL_INDEX 
			left[capacity - 1] = NULL_INDEX;

			// freeListHead <- start
			freeListHead = start;
		} // end if 

		// nTrees <- nTrees + 1
		nTrees = nTrees + 1;

		// root <- NULL_INDEX 
		root = NULL_INDEX;
	}

	~BSTDictionary() {
		// nTrees <- nTrees - 1
		nTrees = nTrees - 1;

		// if nTrees = 0
		if (nTrees == 0) {
			// Delete all shared arrays 
			delete[] counts;
			delete[] heights;
			delete[] left;
			delete[] right;
			delete[] keys;
			delete[] values;
		}

		// else 
		else {
			// prvClear(root)
			prvClear(root);
		}
	} // end procedure 

	void clear() {
		prvClear(root);
		root = NULL_INDEX;

		//
		nTrees = 0;
		freeListHead = 0;
	}

	uint32_t size() {
		// for empty tree
		if (root == NULL_INDEX) {
			return 0;
		}

		return counts[root];
	}

	uint32_t height() {
		// for empty tree
		if (root == NULL_INDEX) {
			return NULL_INDEX;
		}

		return heights[root];
	}

	bool isEmpty() {
		return (root == NULL_INDEX);
	}

	ValueType &search(const KeyType &k) {
		// n <- root
		uint32_t n = root;

		// while n != NULL_INDEX 
		while (n != NULL_INDEX) {
			// if k = keys[n]
			if (k == keys[n]) {
				// return values[n]
				return values[n];
			}

			// else if k < keys[n]
			else if (k < keys[n]) {
				// n <- left[n]
				n = left[n];
			}

			// else 
			else {
				// n <- right[n]
				n = right[n];
			} // end if
		} // end while 

		// throw domain_error("Search: Key not found")
		throw std::domain_error("Search: Key not found");
	} // end procedure 

	ValueType &operator[](const KeyType &k) {
		uint32_t tmp, n;
		// tmp <- prvAllocate()
		tmp = prvAllocate();

		// n <- tmp
		n = tmp;

		// root <- prvInsert(root, n, k)
		root = prvInsert(root, n, k);

		// if n != tmp
		if (n != tmp) {
			// prvFree 
			prvFree(tmp);
		} // endif 

		// return values[n] 
		return values[n];
	} // end procedure 

	void remove(const KeyType &k) {
		uint32_t ntbd = NULL_INDEX;

		root = prvRemove(root, ntbd, k);

		if (ntbd != NULL_INDEX) {
			ntbd = NULL_INDEX;
		}
	}

	uint32_t getHeight(uint32_t r) {
		if (r == NULL_INDEX) {
			return NULL_INDEX;
		}

		return heights[r];
	}

	uint32_t getCount(uint32_t r) {
		if (r == NULL_INDEX) {
			return 0;
		}

		return counts[r];
	}

private:
	uint32_t
		root;
	
	static uint32_t
		*counts,
		*heights,
		*left,
		*right,
		nTrees,
		capacity,
		freeListHead;
	
	static KeyType
		*keys;
	
	static ValueType
		*values;

	uint32_t prvAllocate() {
		uint32_t tmp;
		
		// if freeListHead = NULL_INDEX
		if (freeListHead == NULL_INDEX) {
			// Allocate temporary arrays with 2*capacity elements 
			uint32_t  *TEMP_counts   = new uint32_t[2*capacity];
			uint32_t  *TEMP_heights  = new uint32_t[2*capacity];
			uint32_t  *TEMP_left     = new uint32_t[2*capacity];
			uint32_t  *TEMP_right    = new uint32_t[2*capacity];
			KeyType   *TEMP_keys     = new KeyType[2*capacity];
			ValueType *TEMP_values   = new ValueType[2*capacity];

			// Copy data from old arrays to temporary arrays 
			for (int i = 0; i < capacity; i++) {
				TEMP_counts[i]  = counts[i];
				TEMP_heights[i] = heights[i];
				TEMP_left[i]    = left[i];
				TEMP_right[i]   = right[i];
				TEMP_keys[i]    = keys[i];
				TEMP_values[i]  = values[i];
			}

			// Delete old arrays 
			delete[] counts;
			delete[] heights;
			delete[] left;
			delete[] right;
			delete[] keys;
			delete[] values;

			// Point shared pointers to temporary arrays 
			counts  = TEMP_counts;
			heights = TEMP_heights;
			left    = TEMP_left;
			right   = TEMP_right;
			keys    = TEMP_keys;
			values  = TEMP_values; 

			// Regenerate the free list 
			// for i <- start to end - 1
			for (int i = capacity; i < 2 * capacity - 1; i++) {
				// left[i] <- i + 1
				left[i] = i + 1;
			} // end for 

			// left[end] <- NULL_INDEX 
			left[2 * capacity - 1] = NULL_INDEX;

			// freeListHead <- start
			freeListHead = capacity;


			// capacity = 2*capacity 
			capacity = 2 * capacity; 
		} // end if 

		// tmp <- freeListHead 
		tmp = freeListHead;

		// freeListHead <- left[freeListHead]
		freeListHead = left[freeListHead];


		// left[tmp] <- NULL_INDEX 
		left[tmp] = NULL_INDEX;

		// right[tmp] <- NULL_INDEX 
		right[tmp] = NULL_INDEX;

		// counts[tmp] <- 1
		counts[tmp] = 1;

		// heights[tmp] <- 1
		heights[tmp] = 1;

		return tmp;
	} // end procedure 

	void prvFree(uint32_t n) {
		// left[n] <- freeListHead;
		left[n] = freeListHead;

		// freeListHead <- n
		freeListHead = n;
	} // end procedure 

	void prvClear(uint32_t r) {
		if (r != NULL_INDEX) {
			prvClear(left[r]);
			prvClear(right[r]);
			// r = NULL_INDEX;
			prvAdjust(r);
		}
	}

	void prvAdjust(uint32_t r) {
		// counts[r] <- getCount(left[r]) + getCount(right[r]) + 1
		counts[r] = getCount(left[r]) + getCount(right[r]) + 1; //count(left[r])???

		// heights[r] <- max(getHeight(left[r]), getHeight(right[r])) + 1
		heights[r] = std::max(getHeight(left[r]), getHeight(right[r])) + 1;
	}

	uint32_t prvInsert(uint32_t r, uint32_t &n, const KeyType &k) {
		// if r = NULL_INDEX 
		if (r == NULL_INDEX) {
			// keys[n] = k
			keys[n] = k;

			// return n 
			return n;
		} // end if 

		// if k = keys[r] 
		if (k == keys[r]) {
			// n = r
			n = r;
		}

		// else if k < keys[r]
		else if (k < keys[r]) {
			// left[r] <- prvInsert(left[r], n, k)
			left[r] = prvInsert(left[r], n, k);
		}

		// else
		else {
			// right[r] <- prvInsert(right[r], n, k)
			right[r] = prvInsert(right[r], n, k);
		} // end if 

		prvAdjust(r);

		return r;
	} // end procedure 

	uint32_t prvRemove(uint32_t r, uint32_t &ntbd, const KeyType &k) {
		uint32_t tmp;
		KeyType keySwapTemp;
		ValueType valSwapTemp;

		// if r = NULL_INDEX 
		if (r == NULL_INDEX) {
			// throw domain_error("Remove: Key not found")
			throw std::domain_error("Remove: Key not found");
		} // end if 

		// if k < keys[r] 
		if (k < keys[r]) {
			// left[r] <- prvRemove(left[r], ntbd, k)
			left[r] = prvRemove(left[r], ntbd, k);
		}

		// else if k > keys[r]
		else if (k > keys[r]) {
			// right[r] <- prvRemove(right[r], ntbd, k)
			right[r] = prvRemove(right[r], ntbd, k);
		}

		// else 
		else {
			// ntbd <- r
			ntbd = r;

			// if left[r] = NULL_INDEX 
			if (left[r] == NULL_INDEX) {
				// if right[r] = NULL_INDEX
				if (right[r] == NULL_INDEX) {
					// r <- NULL_INDEX
					r = NULL_INDEX;
				}

				// else
				else {
					// r <- right[r]
					r = right[r];
				} // end if 
			}

			// else 
			else {
				// if right[r] = NULL_INDEX 
				if (right[r] == NULL_INDEX) {
					// r <- left[r]
					r = left[r];
				} 

				// else 
				else {
					// Reduce two-child case to one-child case 
					// if getHeight(right[r]) > getHeight(left[r])
					if (getHeight(right[r]) > getHeight(left[r])) {
						// tmp <- right[r]
						tmp = right[r];

						// left[tmp] != NULL_INDEX
						while (left[tmp] != NULL_INDEX) {
							// tmp <- left[tmp]
							tmp = left[tmp];
						} // end while 

						// SWAP keys[r] and keys[tmp]
						keySwapTemp = keys[tmp];
						keys[tmp] = keys[r];
						keys[r] = keySwapTemp;

						// SWAP values[r] and values[tmp]
						valSwapTemp = values[tmp];
						values[tmp] = values[r];
						values[r] = valSwapTemp;

						// right <- prvRemove(right[r], ntbd, k)
						right[r] = prvRemove(right[r], ntbd, k);
					}

					// else 
					else {
						// tmp <- left[r]
						tmp = left[r];

						// while right[tmp] != NULL_INDEX
						while (right[tmp] != NULL_INDEX) {
							// tmp <- right[tmp]
							tmp = right[tmp];
						} // end while 

						// SWAP keys[r] and keys[tmp]
						keySwapTemp = keys[tmp];
						keys[tmp] = keys[r];
						keys[r] = keySwapTemp;

						// SWAP values[r] and values[tmp]
						valSwapTemp = values[tmp];
						values[tmp] = values[r];
						values[r] = valSwapTemp;

						// left[r] <- prvRemove(left[r], ntbd, k)
						left[r] = prvRemove(left[r], ntbd, k);
					} // end if 
				} // end if 
			} // end if 
		} // end if 

		// if r != NULL_INDEX 
		if (r != NULL_INDEX) {
			prvAdjust(r);
		} // end if 

		return r;
	} // end procedure 
};

template<typename KeyType, typename ValueType>
uint32_t *BSTDictionary<KeyType, ValueType>::counts = nullptr;

template<typename KeyType, typename ValueType>
uint32_t *BSTDictionary<KeyType, ValueType>::heights = nullptr;

template<typename KeyType, typename ValueType>
uint32_t *BSTDictionary<KeyType, ValueType>::left = nullptr;

template<typename KeyType, typename ValueType>
uint32_t *BSTDictionary<KeyType, ValueType>::right = nullptr;

template<typename KeyType, typename ValueType>
uint32_t BSTDictionary<KeyType, ValueType>::nTrees = 0;

template<typename KeyType, typename ValueType>
uint32_t BSTDictionary<KeyType, ValueType>::capacity = 0;

template<typename KeyType, typename ValueType>
uint32_t BSTDictionary<KeyType, ValueType>::freeListHead = 0;

template<typename KeyType, typename ValueType>
KeyType *BSTDictionary<KeyType, ValueType>::keys = nullptr;

template<typename KeyType, typename ValueType>
ValueType *BSTDictionary<KeyType, ValueType>::values = nullptr;

#endif

