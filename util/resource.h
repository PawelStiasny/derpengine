#ifndef RESOURCE_H
#define RESOURCE_H

#include <assert.h>
#include <stdio.h>

/// Generic interface for refernce-counted shared resources.
class SharedResource
{
public:
	SharedResource() {
		handle_count = 0;
	};

	void handleCreated() {
		handle_count++;
		printf("handle created (%lx)\n", (unsigned long)this);
	};

	void handleRemoved() {
		printf("handle removed (%lx)\n", (unsigned long)this);
		assert(handle_count > 0);
		handle_count--;
		if (!handle_count)
			onLastHandleRemoved();
	};

	bool hasHandles() {
		return (handle_count > 0);
	};

protected:
	virtual void onLastHandleRemoved() {};

private:
	unsigned int handle_count;
};

/// Reference-counting handle for a SharedResource.
//  T should be a subclass of SharedResource.
template <class T>
class ResourceHandle
{
public:
	ResourceHandle(T *res = 0)
	{
		shared_resource = res;
		if (res) shared_resource->handleCreated();
	}

	ResourceHandle(const ResourceHandle<T> &r)
	{
		shared_resource = r.shared_resource;
		if (shared_resource) shared_resource->handleCreated();
	}

	~ResourceHandle()
	{
		if (shared_resource) shared_resource->handleRemoved();
	}

	ResourceHandle<T> & operator=(const ResourceHandle<T> &rhs)
	{
		if (rhs.shared_resource == shared_resource)
			return *this;

		if (shared_resource) shared_resource->handleRemoved();
		shared_resource = rhs.shared_resource;
		if (shared_resource) shared_resource->handleCreated();
		return *this;
	}

	T & operator*()
	{
		return *shared_resource;
	}

	T * operator->()
	{
		return shared_resource;
	}

	T * getRawPointer()
	{
		return shared_resource;
	}

	bool operator==(const ResourceHandle<T> &rhs)
	{
		return (shared_resource == rhs.shared_resource);
	}

private:
	T *shared_resource;
};

#endif

