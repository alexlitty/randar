#ifndef RANDAR_SCENE_SCENE_MODEL_HPP
#define RANDAR_SCENE_SCENE_MODEL_HPP

namespace randar
{
    /**
     * A structure to organize model actions and states within a scene.
     */
    class SceneModel
    {
        /**
         * The unique identifier for this model within the scene.
         *
         * Multiple instances of the same model may be used within a scene.
         * Having this ID helps track the activity of each model instance.
         */
        uint32_t id;

    public:
        /**
         * The model instance.
         */
        Model* model;

        /**
         * All actions that influence the model in this scene.
         */
        std::vector<Action*> actions;

        /**
         * The states of this model in every possible frame.
         *
         * Dynamically built from actions.
         */
        std::vector<ModelState> states;

        /**
         * Constructor.
         */
        SceneModel(uint32_t initId, Model* initModel);

        /**
         * Destructor.
         */
        ~SceneModel();
    };
}

#endif
