#include <fstream>
#include <sstream>
#include <randar/render/Model.hpp>

void randar::Model::import(std::string filename)
{
    this->mesh.clear();
    this->mesh.setPrimitive(GL_TRIANGLES);
    
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string key;
        float x, y, z;

        if (!(iss >> key)) { continue; }
        if (key == "v") {
            if (!(iss >> x >> y >> z)) { continue; }

            Vertex vertex;
            vertex.position.set(x, y, z);
            vertex.color = randar::randomColor();
            this->mesh.append(vertex);
        }
    }
    this->mesh.send();
}
