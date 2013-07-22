#include <functional>
#include <map>

template <typename K, typename T>
class ResourcePool
{
public:
	/// Returns an object from the pool. construct_object function is used if
	/// the object doesn't exist.
	ResourceHandle<T> getObject(const K &key, std::function<T* ()> construct_object)
	{
		typename std::map< K, T* >::iterator it = pool.find(key);
		if (it == pool.end()) {
			T* obj = construct_object();
			pool.insert(std::make_pair(key, obj));
			return obj;
		} else {
			return it->second;
		}
	}

	bool releaseAllUnused()
	{
		int remaining = 0, deleted = 0;

		for (auto &kv : pool) {
			if ((kv.second)->hasHandles()) {
				remaining++;
			} else {
				delete kv.second;
				deleted++;
			}
		}

		return !remaining;
	}

private:
	std::map< K, T* > pool;
};
