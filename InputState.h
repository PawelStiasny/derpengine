#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <SDL2/SDL.h>
#undef main
#include <map>

class InputState
{
public:
	enum KeyFunction { KF_EXIT, KF_FORWARDS, KF_BACKWARDS };

	InputState();
	void readInputState();
	bool getKeyState(KeyFunction f);
	int getAbsoluteMouseX() { return mouse_x; };
	int getAbsoluteMouseY() { return mouse_y; };
	float getMouseX() { return (float)mouse_x / (float)w; };
	float getMouseY() { return (float)mouse_y / (float)h; };

	int w, h;
	int mouse_x, mouse_y;

private:
	Uint8 *keys;
	Uint8 key_function_to_keycode[3];
};

#endif