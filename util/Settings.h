#ifndef SETTINGS_H
#define SETTINGS_H

class SceneManager;

struct Settings
{
	Settings(const char *argv[]);
	SceneManager * makeSceneManager();

	bool
		fullscreen,
		enable_msaa,
		enable_shadows,
		enable_debugging,
		enable_synchronous_debugging;

	int
		opengl_version_major,
		opengl_version_minor,
		resolution_x,
		resolution_y;

	char
		scene_name[32];
};

#endif

