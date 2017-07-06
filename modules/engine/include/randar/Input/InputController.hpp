#ifndef RANDAR_SYSTEM_INPUT_CONTROLLER_HPP
#define RANDAR_SYSTEM_INPUT_CONTROLLER_HPP

#include <set>
#include <randar/Math/Vector2.hpp>

namespace randar
{
    class InputController
    {
    protected:
        /**
         * List of currently pressed keys.
         */
        std::set<unsigned int> pressedKeys;

        /**
         * List of currently pressed mouse buttons.
         */
        std::set<unsigned int> pressedMouseButtons;

        /**
         * Most recently known position of the mouse.
         */
        randar::Vector2<float> mousePosition;

    public:
        /**
         * Destructor.
         */
        virtual ~InputController();

        /**
         * Handles a raw key press.
         */
        void handleRawKeyPress(unsigned int key);

        /**
         * Handles a raw key release.
         */
        void handleRawKeyRelease(unsigned int key);

        /**
         * Handles a raw mouse button press.
         */
        void handleRawMouseButtonPress(unsigned int button);

        /**
         * Handles a raw mouse button release.
         */
        void handleRawMouseButtonRelease(unsigned int button);

        /**
         * Handles a raw mouse position update.
         */
        void handleRawMousePosition(float x, float y);

        /**
         * Whether a key is being pressed.
         */
        bool isKeyPressed(unsigned int key) const;

        /**
         * Handles an interpreted key press.
         */
        virtual void onKeyPress(unsigned int key);

        /**
         * Handles an interpreted key release.
         */
        virtual void onKeyRelease(unsigned int key);

        /**
         * Performs custom input handling.
         */
        virtual void handleInput();
    };
}

#endif
