template<typename T, int SIZE>

class Set {
private:
	T set[SIZE];
	int push_val = 0;
	int pop_val = SIZE;
	bool exists = false;
public:

	Set() { // initalize entire set to 0
		for (unsigned int i = 0; i <= SIZE; i++) {
			set[i] = NULL;
		}
	}

	bool find(T val) { // check if element exists
		for (unsigned int i = 0; i <= SIZE; i++) {
			if (set[i] == val) {
				exists = true;
				break;
			}
		}
		return exists;
	}

	int size() { //get size of set
		return SIZE;
	}
	void push(T val) { // add new element to set
		if (push_val <= SIZE) {
			set[push_val] = val;
			push_val++;
		}
	}
	void pop() { // remove last element from set 
		if (pop_val >= 0) {
			set[pop_val] = NULL;
			pop_val--;
		}
	}
	T at(int index) { // return element at user defined index
		T val = set[index];
		return val;
	}

};
