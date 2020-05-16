#include "ProjectGenerator.hpp"

using json = nlohmann::json;

ProjectGenerator::ProjectGenerator() {

}

ProjectGenerator::~ProjectGenerator() {

}

void ProjectGenerator::proccessFile() {
    std::ifstream packcFile("./packc.json");
    json j;
    packcFile >> j;

    for (auto data : j["classes"].items()) {
        FileManager::createSourceFile(data.value());
        FileManager::createHeaderFile(data.value());
    }
    for (auto data : j["sources"].items()) {
        FileManager::createSourceFile(data.value());
    }
    for (auto data : j["headers"].items()) {
        FileManager::createHeaderFile(data.value());
    }

}
