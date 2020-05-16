#include "ProjectCreator.hpp"
#include <fstream>

ProjectCreator::ProjectCreator() {
    init();
    createProject();
}

void ProjectCreator::init() {
    std::string projectName;
    std::string version;
    std::string makeSystem;
    std::string author;

    std::cout << "Project Name : ";
    std::cin >> projectName;

    std::cout << "Version : ";
    getline(std::cin, version);

    std::cout << "Make System (CMake/Makefile) : ";
    getline(std::cin, makeSystem);

    std::cout << "Author : ";
    getline(std::cin, author);

    p_name = projectName;
    p_version = version;
    p_makeSystem = makeSystem;
    p_author = author;
    p_path = "./" + p_name;

    fileManager = new FileManager(p_name, p_version, p_makeSystem, p_author);
}

void ProjectCreator::createDirectory(std::string directoryName) {
    std::string path = p_path + "/" + directoryName;
    filesystem::create_directory(path.c_str());
}

void ProjectCreator::createDirectories() {
    for (size_t i = 0; i < 3; i++) {
        createDirectory(directories[i].c_str());
    }
}

void ProjectCreator::createProject() {
    createDirectories();
    fileManager->createInitFiles();
}

ProjectCreator::~ProjectCreator() {
    delete fileManager;
    delete this;
}