#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}

void Input::beginNewFrame(){
	pressedKeys.clear();
	releasedKeys.clear();
}

void Input::KeyDownEvent(const SDL_Event& event){
	pressedKeys[event.key.keysym.sym] = true;
	heldKeys[event.key.keysym.sym] = true;
}

void Input::KeyUpEvent(const SDL_Event& event){
	releasedKeys[event.key.keysym.sym] = true;
	heldKeys[event.key.keysym.sym] = false;
}


bool Input::wasKeyPressed(SDL_Keycode key){
	return pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Keycode key){
	return releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Keycode key){
	return heldKeys[key];
}
