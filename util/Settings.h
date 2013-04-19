#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings
{
	Settings(const char *argv[]);

	bool
		enable_msaa,
		enable_shadows;

	int
		opengl_version_major,
		opengl_version_minor;
};

#endif

