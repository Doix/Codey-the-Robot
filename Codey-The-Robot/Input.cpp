#include "Input.h"

//empty constructors/destructors
Input::Input()
{
}
Input::~Input()
{
}

//begin a new frame and reset maps of keys pressed / released
void Input::beginNewFrame(){
	pressedKeys.clear();
	releasedKeys.clear();
	mouseClicked = false; //TODO: more generic
}

//if keydown, add this to the pressedKeys and heldKeys maps with value of true (false by default)
void Input::KeyDownEvent(const SDL_Event& event){
	pressedKeys[event.key.keysym.sym] = true;
	heldKeys[event.key.keysym.sym] = true;
}

//if key released, add this to the releasedKeys map with value of true 
//and set heldKeys map entry to false
void Input::KeyUpEvent(const SDL_Event& event){
	releasedKeys[event.key.keysym.sym] = true;
	heldKeys[event.key.keysym.sym] = false;
}

void Input::MouseClickEvent(const SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT){
		mouseClicked = true; //TODO: make more generic
		leftClick = std::make_tuple(event.button.x, event.button.y);
	}
}

//check if a key was pressed
bool Input::wasKeyPressed(SDL_Keycode key){
	return pressedKeys[key];
}

//check if a key was released
bool Input::wasKeyReleased(SDL_Keycode key){
	return releasedKeys[key];
}

//check if key is held
bool Input::isKeyHeld(SDL_Keycode key){
	return heldKeys[key];
}

bool Input::wasMouseClicked(){
	return mouseClicked;
}

std::tuple<int, int> Input::getMouseClick(){
	return leftClick;
}