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
    std::ifstream file(filename);

    if (extension == "mtl") {
        this->importMtl(file);
    }

    else if (extension == "obj") {
        this->importObj(filename.substr(0, filename.size() - 4), file);
    }
}

void randar::Resources::importMtl(std::ifstream& file)
{

}

void randar::Resources::importObj(std::string name, std::ifstream& file)
{
    Model *model = new Model;
    model->mesh.setPrimitive(GL_TRIANGLES);
    
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
            model->mesh.append(vertex);
        }   
    }   
    model->mesh.send();

    if (this->models.find(name) != this->models.end()) {
        delete this->models[name];
    }
    this->models[name] = model;
}
