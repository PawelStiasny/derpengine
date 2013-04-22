#include "FileWatcher.h"

#ifdef LINUX
extern "C" {
#include <unistd.h>
#include <sys/inotify.h>
}
#include <stdio.h>
#include <algorithm>

int FileWatcher::inotify_fd = -1;
std::map< int, FileWatcher* > FileWatcher::active_watchers;

FileWatcher::FileWatcher(const char *path)
{
	if (inotify_fd == -1) {
		inotify_fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
		if (inotify_fd == -1) {
			perror("Inotify initialization error");
			return;
		}
	}

	this->path = path;

	watch_id = inotify_add_watch(inotify_fd, path, IN_CLOSE_WRITE);
	if (watch_id != -1)
		active_watchers[watch_id] = this;
}

FileWatcher::~FileWatcher()
{
	inotify_rm_watch(inotify_fd, watch_id);
	active_watchers.erase(watch_id);
	if (active_watchers.empty()) {
		close(inotify_fd);
		inotify_fd = -1;
	}
}

void FileWatcher::registerObserver(FileChangeHandler *observer)
{
	observers.push_back(observer);
}

void FileWatcher::notifyObservers()
{
	std::for_each(
			observers.begin(), observers.end(), 
			std::mem_fun(&FileChangeHandler::onFileChanged));
	/*inotify_rm_watch(inotify_fd, watch_id);
	active_watchers.erase(watch_id);
	watch_id = inotify_add_watch(inotify_fd, path.c_str(), IN_MODIFY | IN_CLOSE_WRITE);
	active_watchers[watch_id] = this;*/
}

void FileWatcher::pollChanges()
{
	if (inotify_fd == -1)
		return;

	struct inotify_event ie;
	while ( read(inotify_fd, &ie, sizeof(ie)) > 0 ) {
		puts("inotify event read");
		active_watchers[ie.wd]->notifyObservers();
	}
}

#else


FileWatcher::FileWatcher(const char *path) {}
FileWatcher::~FileWatcher() {}
void FileWatcher::registerObserver(FileChangeHandler *observer) {}
void FileWatcher::notifyObservers() {}
void FileWatcher::pollChanges() {}

#endif
