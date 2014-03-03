#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include "SDL.h"

class Input
{
public:
	Input();
	~Input();

	void beginNewFrame();
	void KeyUpEvent(const SDL_Event& event);
	void KeyDownEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Keycode key);
	bool wasKeyReleased(SDL_Keycode key);
	bool isKeyHeld(SDL_Keycode key);

private:
	std::map<SDL_Keycode, bool> heldKeys;
	std::map<SDL_Keycode, bool> pressedKeys;
	std::map<SDL_Keycode, bool> releasedKeys;
};

#endif //  INPUT_H_