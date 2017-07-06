#ifndef RANDAR_SYSTEM_INPUT_CONTROLLER_HPP
#define RANDAR_SYSTEM_INPUT_CONTROLLER_HPP

#include <set>

namespace randar
{
    class InputController
    {
    protected:
        /**
         * A list of keys currently being pressed.
         */
        std::set<unsigned int> pressedKeys;

    public:
        /**
         * Destructor.
         */
        virtual ~InputController();

        /**
         * Handles a raw key press.
         */
        void handleKeyPress(unsigned int key);

        /**
         * Handles a raw key release.
         */
        void handleKeyRelease(unsigned int key);

        /**
         * Whether a key is being pressed.
         */
        bool isKeyPressed(unsigned int key) const;

        /**
         * Handles an interpreted key press.
         */
        virtual void onKeyPress();

        /**
         * Handles an interpreted key release.
         */
        virtual void onKeyRelease();
    };
}

#endif
