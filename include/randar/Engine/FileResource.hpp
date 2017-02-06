#ifndef RANDAR_ENGINE_FILE_RESOURCE_HPP
#define RANDAR_ENGINE_FILE_RESOURCE_HPP

#include <string>
#include <randar/Engine/Resource.hpp>
#include <randar/Project/Exporter.hpp>
#include <randar/Filesystem/BinaryFileStream.hpp>

namespace randar
{
    /**
     * A resource which may be partially or completely stored in a file.
     */
    class FileResource : virtual public Resource
    {
    protected:
        /**
         * Path to the file, relative to the root project directory.
         */
        std::string file;

        /**
         * Writes this resource to a file.
         */
        virtual bool save() = 0;

    public:
        /**
         * Constructor.
         */
        FileResource(const std::string& initFile = "");

        /**
         * Sets the file for this resource.
         */
        void setFile(const std::string& newFile);

        /**
         * Gets the file for this resource.
         */
        const std::string& getFile() const;
    };
}

#endif
