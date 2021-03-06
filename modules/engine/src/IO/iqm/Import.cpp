#include <stdio.h>
#include <randar/IO/Iqm.hpp>

void randar::importIqm(const randar::Path& path, randar::Geometry& geo)
{
    geo.clear();

    FILE *f = ::fopen(path.toString().c_str(), "rb");
    if (!f) { throw std::runtime_error("Cannot open file"); }

    // Read header.
    iqm::header header;
    if (::fread(&header, 1, sizeof(header), f) != sizeof(header)) {
        throw std::runtime_error("Corrupted header: Too short");
    }

    // Invalid magic string.
    if (std::string(header.magic) != std::string(IQM_MAGIC)) {
        throw std::runtime_error("Corrupted header: Magic string");
    }

    // Incompatible file version.
    iqm::lilswap(&header.version, (sizeof(header) - sizeof(header.magic))/sizeof(unsigned int));
    if (header.version != IQM_VERSION) {
        throw std::runtime_error(
              "Detected IQM version " + std::to_string(header.version)
            + ", but only version " + std::to_string(IQM_VERSION)
            + " is supported"
        );
    }

    // File too big.
    if (header.filesize > (16 << 20)) {
        throw std::runtime_error("File size must not exceed 16MB");
    }
    
    // Load data into buffer.
    unsigned char *buffer = new unsigned char[header.filesize];
    if (::fread(buffer + sizeof(header), 1, header.filesize - sizeof(header), f) != header.filesize - sizeof(header)) {
        throw std::runtime_error("Corrupted header: Filesize");
    }
    ::fclose(f);

    // Nothing worth importing.
    if (header.num_meshes <= 0) {
        return;
    }

    iqm::lilswap((unsigned int*)&buffer[header.ofs_vertexarrays], header.num_vertexarrays*sizeof(iqm::vertexarray)/sizeof(unsigned int));
    iqm::lilswap((unsigned int*)&buffer[header.ofs_triangles], header.num_triangles*sizeof(iqm::triangle)/sizeof(unsigned int));
    iqm::lilswap((unsigned int*)&buffer[header.ofs_meshes], header.num_meshes*sizeof(iqm::mesh)/sizeof(unsigned int));
    iqm::lilswap((unsigned int*)&buffer[header.ofs_joints], header.num_joints*sizeof(iqm::joint)/sizeof(unsigned int));

    // @todo - textures

    // Read vertex arrays.
    float *inposition = NULL, *innormal = NULL, *intangent = NULL, *intexcoord = NULL;
    //const char *str = header.ofs_text ? (char *)&buffer[header.ofs_text] : "";

    iqm::vertexarray *vas = reinterpret_cast<iqm::vertexarray*>(&buffer[header.ofs_vertexarrays]);
    for(int i = 0; i < (int)header.num_vertexarrays; i++)
    {
        iqm::vertexarray &va = vas[i];
        switch(va.type)
        {
            case IQM_POSITION: if(va.format != IQM_FLOAT || va.size != 3) throw std::runtime_error("Bad vertex array a"); inposition = (float *)&buffer[va.offset]; iqm::lilswap(inposition, 3*header.num_vertexes); break;
            case IQM_NORMAL: if(va.format != IQM_FLOAT || va.size != 3) throw std::runtime_error("Bad vertex array b"); innormal = (float *)&buffer[va.offset]; iqm::lilswap(innormal, 3*header.num_vertexes); break;
            case IQM_TANGENT: if(va.format != IQM_FLOAT || va.size != 4) throw std::runtime_error("Bad vertex array c"); intangent = (float *)&buffer[va.offset]; iqm::lilswap(intangent, 4*header.num_vertexes); break;
            case IQM_TEXCOORD: if(va.format != IQM_FLOAT || va.size != 2) throw std::runtime_error("Bad vertex array d"); intexcoord = (float *)&buffer[va.offset]; iqm::lilswap(intexcoord, 2*header.num_vertexes); break;
        }
    }

    // Read meshes.
    //iqm::mesh *meshes = reinterpret_cast<iqm::mesh*>(&buffer[header.ofs_meshes]);
    for (unsigned int i = 0; i < header.num_meshes; i++) {
        //iqm::mesh &mesh = meshes[i];
    }

    // Read vertices.
    for (unsigned int i = 0; i < header.num_vertexes; i++) {
        iqm::vertex data;
        if (inposition) ::memcpy(data.position, &inposition[i * 3], sizeof(data.position));
        if (intexcoord) ::memcpy(data.texcoord, &intexcoord[i * 2], sizeof(data.texcoord));

        Vertex vertex;
        vertex.position = Vector3(data.position[0], data.position[1], data.position[2]);
        vertex.textureCoordinate.u(data.texcoord[0]);
        vertex.textureCoordinate.v(data.texcoord[1]);
        geo.vertices.append(vertex);
    }

    // Read triangles.
    iqm::triangle *triangles = reinterpret_cast<iqm::triangle*>(&buffer[header.ofs_triangles]);
    for (unsigned int i = 0; i < header.num_triangles; i++) {
        iqm::triangle &triangle = triangles[i];

        for (unsigned int i = 0; i < 3; i++) {
            geo.indices.append(triangle.vertex[i]);
        }
    }

    // IQMs have no explicit texture data. For now, assume each mesh has a single texture.
    //model->meshTextures.push_back(nullptr);
}
