#include "Input.hpp"

int Input::keyLength = 0;
const Uint8* Input::keyboardState = SDL_GetKeyboardState(&Input::keyLength);
Uint8* Input::previousKeyboardState = new Uint8[Input::keyLength];

void Input::Update()
{
    memcpy(previousKeyboardState, keyboardState, keyLength);
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return keyboardState[key];
}

bool Input::GetKeyPressed(SDL_Scancode key)
{
    return !previousKeyboardState[key] && keyboardState[key];
}