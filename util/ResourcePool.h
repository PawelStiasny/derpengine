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

	int releaseAllUnused(
			std::function<void (const K&, const T*)> on_used = NULL)
	{
		int deleted = 0;

		auto it = pool.begin();
		//for (auto &kv : pool) {
		while (it != pool.end()) {
			if ((it->second)->hasHandles()) {
				if (on_used)
					on_used(it->first, it->second);
				it++;
			} else {
				delete it->second;
				it = pool.erase(it);
				deleted++;
			}
		}

		return deleted;
	}

	int size()
	{
		return pool.size();
	}

private:
	std::map< K, T* > pool;
};
