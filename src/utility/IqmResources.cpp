#include <randar/utility/iqm.hpp>
#include <randar/utility/Resources.hpp>

void randar::Resources::importIqm(std::ifstream& file)
{
    iqm::header header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (std::string(header.magic) != std::string(IQM_MAGIC)) {
        throw std::runtime_error("Corrupted header");
    }

    iqm::lilswap(&header.version, (sizeof(header) - sizeof(header.magic))/sizeof(unsigned int));
    if (header.version != IQM_VERSION) {
        throw std::runtime_error(
              "Detected version " + std::to_string(header.version)
            + ", but only version " + std::to_string(IQM_VERSION)
            + " is supported"
        );
    }

    if (header.filesize > (16 << 20)) {
        throw std::runtime_error("File size must not exceed 16MB");
    }

    char *buffer = new char[header.filesize];
    file.read(buffer, header.filesize - sizeof(header));
    if (file.gcount() != static_cast<unsigned int>(header.filesize - sizeof(header))) {
        throw std::runtime_error("Corrupted header - Filesize");
    }
}
