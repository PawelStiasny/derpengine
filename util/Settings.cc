#include "Settings.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Settings::Settings(const char *argv[])
{
	opengl_version_major = 3;
	opengl_version_minor = 0;

#ifdef WIN32
	enable_msaa = true;
#else
	enable_msaa = false;
#endif
	enable_shadows = true;
	enable_debugging = true;
	enable_synchronous_debugging = false;
	fullscreen = false;

	if (!argv)
		return;

	while(*++argv) {
		if (!strcmp(*argv, "--enable-msaa"))
			enable_msaa = true;
		else if (!strcmp(*argv, "--disable-msaa"))
			enable_msaa = false;
		else if (!strcmp(*argv, "--disable-shadows"))
			enable_shadows = false;
		else if (!strcmp(*argv, "-g")) {
			opengl_version_major = atoi(*++argv);
			opengl_version_minor = atoi(*++argv);
		}
		else if (!strcmp(*argv, "--sync-debug"))
			enable_synchronous_debugging = true;
		else if (!strcmp(*argv, "--no-debug"))
			enable_debugging = false;
		else if (!strcmp(*argv, "-r")) {
			fullscreen = true;
			resolution_x = atoi(*++argv);
			resolution_y = atoi(*++argv);
		} else
			printf("Unrecognized argument: %s\n", *argv);
	}
}

