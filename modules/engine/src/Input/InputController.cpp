#include <randar/Input/InputController.hpp>

// Destructor.
randar::InputController::~InputController()
{

}

// Handles a raw key press.
void randar::InputController::handleRawKeyPress(unsigned int key)
{
    this->pressedKeys.insert(key);
    this->onKeyPress(key);
}

// Handles a raw key release.
void randar::InputController::handleRawKeyRelease(unsigned int key)
{
    this->pressedKeys.erase(key);
    this->onKeyRelease(key);
}

// Handles a raw mouse button press.
void randar::InputController::handleRawMouseButtonPress(unsigned int button)
{
    this->pressedMouseButtons.insert(button);
}

// Handles a raw mouse button release.
void randar::InputController::handleRawMouseButtonRelease(unsigned int button)
{
    this->pressedMouseButtons.erase(button);
}

// Handles a raw mouse position update.
void randar::InputController::handleRawMousePosition(float x, float y)
{
    randar::Vector2<float> newMousePosition(x, y);
    randar::Vector2<float> delta(
        x - this->mousePosition.x,
        y - this->mousePosition.y
    );

    //this->onMouseMove(newMousePosition);
    this->mousePosition = newMousePosition;
}

// Whether a key is being pressed.
bool randar::InputController::isKeyPressed(unsigned int key) const
{
    return this->pressedKeys.count(key);
}

// Handles an interpreted key press.
void randar::InputController::onKeyPress(unsigned int key)
{

}

// Handles an interpreted key release.
void randar::InputController::onKeyRelease(unsigned int key)
{

}

// Performs custom input handling.
void randar::InputController::handleInput()
{

}
