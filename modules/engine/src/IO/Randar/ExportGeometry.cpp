#include <randar/Filesystem/BinaryFileWriter.hpp>
#include <randar/IO/Randar.hpp>

void randar::exportGeometry(const randar::Path& path, randar::Geometry& geo)
{
    uint8_t version = 0;
    uint32_t vertexCount = geo.vertices.count();
    uint32_t indexCount = geo.indices.count();

    BinaryFileWriter stream(path.toString());

    // Basic geometry information.
    stream.write(version);
    stream.write(vertexCount);
    stream.write(indexCount);

    // Write vertices.
    for (uint32_t i = 0; i < geo.vertices.count(); i++) {
        Vertex vertex = geo.vertices.get(i);

        stream.write(vertex.position.x);
        stream.write(vertex.position.y);
        stream.write(vertex.position.z);

        stream.write(vertex.color.r());
        stream.write(vertex.color.g());
        stream.write(vertex.color.b());
        stream.write(vertex.color.a());

        stream.write(vertex.normal.x);
        stream.write(vertex.normal.y);
        stream.write(vertex.normal.z);

        stream.write(vertex.textureId);
        stream.write(vertex.textureCoordinate.u());
        stream.write(vertex.textureCoordinate.v());

        stream.write(static_cast<uint32_t>(vertex.jointWeights.size()));
        for (auto item : vertex.jointWeights) {
            stream.write(item.first);
            stream.write(item.second);
        }
    }

    // Write indices.
    for (uint32_t i = 0; i < geo.indices.count(); i++) {
        stream.write(geo.indices.get(i));
    }
}
