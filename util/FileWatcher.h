#ifndef FILEWACTHER_H
#define FILEWACTHER_H

#include <map>
#include <list>
#include <string>

/// Observer interface for FileWatcher clients.
class FileChangeHandler
{
public:
	virtual void onFileChanged() {};
protected:
	FileChangeHandler() {};
};

/// Notifies observers when a file is changed.
class FileWatcher
{
public:
	FileWatcher(const char *path);
	~FileWatcher();
	void registerObserver(FileChangeHandler *observer);
	void notifyObservers();

	static void pollChanges();

private:
	static std::map< int, FileWatcher* > active_watchers;
	static int inotify_fd;

	int watch_id;
	std::string path;

	std::list<FileChangeHandler*> observers;
};

#endif
