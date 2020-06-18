#include "Application.hpp"
#include <iostream>
#include <FileManager.hpp>
#include "ProjectBuilder.hpp"
#include <string>

Application::Application(int argc, char const *argv[]) {
    std::string programArg;

    if (argc < 2) {
        ProjectCreator::printHelp();
        return;
    } else {
        programArg = argv[1];
        if (programArg == "create") {
            if( argc == 2)
                projectCreator = new ProjectCreator();
            else{
                std::cout<<"\nCheck the 'packc help' command to run it correctly\n";
                return;
            } 

        } else if (programArg == "add") {

            std::string argument = argv[2];
            std::string fileName = argv[3];

            if (argument == "-c") {
                std::cout << "create class";

                FileManager::createFile(FileManager::FileType::SOURCE, fileName);
                FileManager::createFile(FileManager::FileType::HEADER, fileName);
            } else if (argument == "-s") {
                std::cout << "create source :";

                FileManager::createFile(FileManager::FileType::SOURCE, fileName);
            } else if (argument == "-h") {
                std::cout << "create header :";

                // TODO .h file include in class
                FileManager::createFile(FileManager::FileType::HEADER, fileName);
            }
            else if(argument=="-dl") {
                FileManager::addDynamicLibrary(fileName);
            }
        } else if (programArg == "help") {
            ProjectCreator::printHelp();
        } else {
            projectBuilder = new ProjectBuilder();
            projectBuilder->runCommands(programArg);
        }
    }
}

Application::~Application() {
    delete projectCreator;
    delete projectBuilder;
    delete this;
}
