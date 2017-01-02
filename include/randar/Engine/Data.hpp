#ifndef RANDAR_ENGINE_DATA_HPP
#define RANDAR_ENGINE_DATA_HPP

namespace randar
{
    /**
     * A representation of data.
     *
     * The data is only brought into memory when needed.
     */
    template <typename T>
    class Data
    {
        T *data;

    public:
        Data() : data(nullptr) { }

        /**
         * Initializes the real data.
         *
         * Nothing happens if the data is already initialized.
         */
        void initialize()
        {
            if (!this->isInitialized()) {
                this->retrieve();
            }
        }

        /**
         * Retrieves the real data.
         */
        virtual void retrieve() = 0;

        /**
         * Frees the real data from memory.
         */
        void destroy()
        {
            delete this->data;
            this->data = nullptr;
        }

        /**
         * Checks whether the real data is initialized.
         */
        bool isInitialized() { return this->data != nullptr; }

        /**
         * Retrieves a reference to the real data.
         */
        T& data() {
            this->initialize();
            return *this->data;
        }

        operator T&() { return this->data(); }
    };
}

#endif
