#ifndef RANDAR_INPUT_CAMERA_INPUT_CONTROLLER_HPP
#define RANDAR_INPUT_CAMERA_INPUT_CONTROLLER_HPP

#include <randar/Input/InputController.hpp>
#include <randar/Render/Camera.hpp>

namespace randar
{
    class CameraInputController : virtual public InputController
    {
    protected:
        Camera& camera;
        
    public:
        /**
         * Constructor.
         */
        CameraInputController(Camera& initCamera);

        /**
         * Destructor.
         */
        virtual ~CameraInputController();

        /**
         * Performs camera input handling.
         */
        virtual void handleInput() override;
    };
}

#endif
