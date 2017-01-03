#ifndef RANDAR_DATA_DATA_HPP
#define RANDAR_DATA_DATA_HPP

namespace randar
{
    /**
     * A representation of data with a configurable source.
     *
     * The data is only brought into memory when needed.
     */
    template <typename T>
    class Data
    {
        T *data;
        std::function<T*()> source;

    public:
        Data() : data(nullptr) { }
        Data(Data& other) : data(nullptr), source(other.source) { }
        ~Data() { this->destroy(); }

        /**
         * Sets the data source.
         */
        void setSource(std::function<T*()>& newSource)
        {
            this->source = newSource;
        }

        /**
         * Initializes the real data.
         *
         * Nothing happens if the data is already initialized.
         */
        void initialize()
        {
            if (!this->isInitialized()) {
                this->data = this->source.get();
            }
        }

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
        T& get() {
            this->initialize();
            return *this->data;
        }

        operator T&() { return this->data(); }
    };
}

#endif
