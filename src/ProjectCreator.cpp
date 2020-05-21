#include "ProjectCreator.hpp"
#include <fstream>

ProjectCreator::ProjectCreator()
{
    init();
    fileManager = new FileManager(p_name, p_version, p_author, p_repository);
    createProject();
}

void ProjectCreator::init()
{
    std::string projectName;
    std::string version;
    std::string author;
    std::string repository;

    std::cout << "Project Name : ";
    getline(std::cin, projectName);

    std::cout << "Version (1.0.0) : ";
    getline(std::cin, version);
    if (version == "")
    {
        version = "1.0.0";
    }

    std::cout << "Author : ";
    getline(std::cin, author);

    std::cout << "Git Repository : ";
    getline(std::cin, repository);

    p_name = projectName;
    p_version = version;
    p_author = author;
    p_repository = repository;
    p_path = "./" + p_name;
}

void ProjectCreator::createDirectory(const std::string &directoryName)
{
    std::string path;
#ifdef _WIN32
    path = p_path + "/" + directoryName;
    mkdir(path.c_str());
#elif __linux__
    path = p_path + "/" + directoryName;
    filesystem::create_directory(path.c_str());
#elif __APPLE__
    path = p_path + "/" + directoryName;
    mkdir(path.c_str(), 0777);
#endif
}

void ProjectCreator::createDirectories()
{
    for (size_t i = 0; i < 3; i++)
    {
        createDirectory(directories[i].c_str());
    }
}

void ProjectCreator::createProject()
{
    createDirectories();
    fileManager->createInitFiles();
}

void ProjectCreator::writeHelpPage()
{
    std::cout << "DESCRIPTION\n\n"
              << "packc is a project manager for C++ written by @mehmetalicayhan.\nYou can create project or add classes,source files, or header files to your existing packc project. \nIn same time this files add to your cmake file automatically.\nYou can build and run your projects and define your own commands.\n\n"
              << "USAGE\n\n"
              << "Create Project:\tpackc create\n\n"
              << "Create Source File:\tpackc add -s <filename>\n\n"
              << "Create C++ Class:\tpackc add -c <filename>\n\n"
              << "Create Header File:\tpackc add -h <filename>\n\n"
              << "Build Project:\t packc build\n\n"
              << "Run Project:\t packc run\n\n"
              << "Clean Project:\t packc clean\n\n";
}

ProjectCreator::~ProjectCreator()
{
    delete fileManager;
    delete this;
}