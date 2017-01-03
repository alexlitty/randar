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
        Datasource& source;

    public:
        Data() : data(nullptr) { }
        Data(Data& other) : data(nullptr), source(other.source) { }
        ~Data() { this->destroy(); }

        /**
         * Sets the data source.
         */
        void setSource(Datasource& newSource)
        {
            this->source = newSource;
        }

        /**
         * Retrieves a reference to the real data.
         */
        T& get() { return this->source.
            this->initialize();
            return *this->data;
        }

        operator T&() { return this->data(); }
    };
}

#endif
