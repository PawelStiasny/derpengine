#include "Settings.h"

#include <string.h>
#include <stdlib.h>

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

	if (!argv)
		return;

	while(*++argv) {
		if (!strcmp(*argv, "--enable-msaa"))
			enable_msaa = true;
		else if (!strcmp(*argv, "--disable-msaa"))
			enable_msaa = false;
		if (!strcmp(*argv, "--disable-shadows"))
			enable_shadows = false;
		else if (!strcmp(*argv, "-g")) {
			opengl_version_major = atoi(*++argv);
			opengl_version_minor = atoi(*++argv);
		}
	}
}

