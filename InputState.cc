#include "InputState.h"

InputState::InputState()
{
	readInputState();
	key_function_to_keycode[KF_EXIT] = SDL_SCANCODE_ESCAPE;
	key_function_to_keycode[KF_FORWARDS] = SDL_SCANCODE_W;
	key_function_to_keycode[KF_BACKWARDS] = SDL_SCANCODE_S;
	key_function_to_keycode[KF_ROTATE_SUN] = SDL_SCANCODE_L;
	mouse_x = mouse_y = 0;
}

void InputState::readInputState()
{
	keys = SDL_GetKeyboardState(NULL);
}

bool InputState::getKeyState(KeyFunction f)
{
	return keys[key_function_to_keycode[f]];
}

