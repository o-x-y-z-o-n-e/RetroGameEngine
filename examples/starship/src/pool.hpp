#ifndef _POOL_HPP_
#define _POOL_HPP_

template<typename T>
class pool {
public:
	typedef std::pair<T*, bool> entry;
	typedef std::vector<entry> table;
public:
	T* create() {
		table::iterator it;
		for(it = registry.begin(); it != registry.end(); it++) {
			if(!it->second) {
				it->second = true;
				return it->first;
			}
		}

		T* ins = new T();
		registry.push_back(entry(ins, true));
		return ins;
	}

	void destroy(T* ins) {
		table::iterator it;
		for(it = registry.begin(); it != registry.end(); it++) {
			if(it->first == ins) {
				it->second = false;
				return;
			}
		}
	}

	void destroy_all() {
		table::iterator it;
		for(it = registry.begin(); it != registry.end(); it++) {
			it->second = false;
		}
	}
private:
	table registry;
};

#endif /* _POOL_HPP_ */