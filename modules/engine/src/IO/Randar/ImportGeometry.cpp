#include <randar/Filesystem/BinaryFileReader.hpp>
#include <randar/IO/Randar.hpp>

void randar::importGeometry(const randar::Path& path, randar::Geometry& geo)
{
    geo.clear();

    uint8_t version;
    uint32_t vertexCount;
    uint32_t indexCount;

    BinaryFileReader stream(path.toString());

    // Check geometry file version.
    stream.read(version);
    if (version != 0) {
        throw std::runtime_error(
            "Incompatible geometry version " + std::to_string(version)
        );
    }

    // Basic geometry information.
    stream.read(vertexCount);
    stream.read(indexCount);

    // Read vertices.
    for (uint32_t i = 0; i < vertexCount; i++) {
        Vertex vertex;

        stream.read(vertex.position.x);
        stream.read(vertex.position.y);
        stream.read(vertex.position.z);
        
        float r, g, b, a;
        stream.read(r);
        stream.read(g);
        stream.read(b);
        stream.read(a);
        vertex.color.set(r, g, b, a);

        stream.read(vertex.normal.x);
        stream.read(vertex.normal.y);
        stream.read(vertex.normal.z);

        stream.read(vertex.textureId);

        float u, v;
        stream.read(u);
        stream.read(v);
        vertex.textureCoordinate.u(u);
        vertex.textureCoordinate.v(v);

        uint32_t jointCount;
        stream.read(jointCount);

        for (uint32_t j = 0; j < jointCount; j++) {
            uint16_t jointIndex;
            uint8_t jointWeight;

            stream.read(jointIndex);
            stream.read(jointWeight);
            vertex.jointWeights[jointIndex] = jointWeight;
        }

        geo.vertices.append(vertex);
    }

    // Read indices;
    for (uint32_t i = 0; i < indexCount; i++) {
        uint32_t index;
        stream.read(index);

        geo.indices.append(index);
    }
}
