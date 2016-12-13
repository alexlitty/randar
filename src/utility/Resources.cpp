#include <randar/utility/Resources.hpp>

randar::Resources::~Resources()
{
    for (auto it : this->materials) {
        delete it.second;
    }

    for (auto it : this->models) {
        delete it.second;
    }
}

void randar::Resources::import(std::string filename)
{
    std::string extension = filename.substr(filename.size() - 3);

    if (extension == "mtl") {
        std::ifstream file(filename);
        this->importMtl(file);
    }

    else if (extension == "obj") {
        std::ifstream file(filename);
        this->importObj(filename.substr(0, filename.size() - 4), file);
    }

    else if (extension == "iqm") {
        std::ifstream file(filename, std::ios::binary);
        this->importIqm(file);
    }
}

void randar::Resources::importMtl(std::ifstream& file)
{
    std::string line, key, name;
    float r, g, b;
    Material *material = nullptr;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (!(iss >> key)) {
            continue;
        }

        if (key == "newmtl") {
            if (!(iss >> name)) {
                continue;
            }

            material = new Material;
            this->materials[name] = material;
            continue;
        }

        else if (material && (key == "Ka" || key == "Kd")) {
            if (!(iss >> r >> g >> b)) {
                continue;
            }

            randar::Color color(
                r * 255,
                g * 255,
                b * 255
            );

            if (key == "Ka") {
                material->ambientColor = color;
            } else {
                material->diffuseColor = color;
            }
        }
    }
}

void randar::Resources::importObj(std::string name, std::ifstream& file)
{
    std::string line, key, filename;
    float x, y, z;

    Model *model = new Model;
    model->vertices.setPrimitive(GL_TRIANGLES);
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (!(iss >> key)) {
            continue;
        }

        if (key == "mtllib") {
            if (!(iss >> filename)) {
                continue;
            }

            this->import(filename);
        }

        else if (key == "v") {
            if (!(iss >> x >> y >> z)) {
                continue;
            }

            Vertex vertex;
            vertex.position.set(x, y, z); 
            vertex.color = randar::randomColor();
            model->vertices.append(vertex);
        }   
    }   
    model->vertices.send();

    if (this->models.find(name) != this->models.end()) {
        delete this->models[name];
    }
    this->models[name] = model;
}
