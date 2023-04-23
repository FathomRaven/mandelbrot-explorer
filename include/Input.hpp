#include <SDL2/SDL.h>

// Static class for managing input functions

class Input
{
public:
    // Update previous keyboard
    static void Update();

    /// @brief Check if a key is being held down
    /// @param key the key to check
    static bool GetKeyDown(SDL_Scancode key);

    /// @brief Check if a key has been pressed
    /// @param key the key to check
    static bool GetKeyPressed(SDL_Scancode key);

private:
    static Uint8* previousKeyboardState;
    const static Uint8* keyboardState;
    static int keyLength;
};