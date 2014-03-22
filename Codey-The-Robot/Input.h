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
	void MouseClickEvent(const SDL_Event& event);
	void MouseReleasedEvent(const SDL_Event& event);
	void MouseMotionEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Keycode key);
	bool wasKeyReleased(SDL_Keycode key);
	bool isKeyHeld(SDL_Keycode key);
	bool wasMouseClicked();
	bool isMouseHeld();
	std::tuple<int, int> getMouseClick();
	std::tuple<int, int> getMouseMotion();

private:
	std::map<SDL_Keycode, bool> heldKeys;
	std::map<SDL_Keycode, bool> pressedKeys;
	std::map<SDL_Keycode, bool> releasedKeys;
	std::tuple<int, int> leftClick;
	std::tuple<int, int> motion;
	bool mouseClicked;
	bool mouseHeld;
};

#endif //  INPUT_H_