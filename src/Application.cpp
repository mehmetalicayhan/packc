#include "Application.hpp"
#include <iostream>
#include <FileManager.hpp>
#include "ProjectBuilder.hpp"
#include <string>

Application::Application(int argc, char const *argv[]) {
    std::string programArg;
    // A dictionary using function pointers
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

            if (argument == "-c") {
                std::cout << "create class";

                for(int i=3; i < argc; i++)
                {
                    std::string filename = argv[i];
                    FileManager::createFile(FileManager::FileType::SOURCE, filename);
                    FileManager::createFile(FileManager::FileType::HEADER, filename);
                }
            } else if (argument == "-s") {
                std::cout << "create source :";

                for(int i=3; i < argc; i++)
                {
                    std::cout << "Creating class: " << argv[i] << std::endl;
                    std::string filename = argv[i];
                    FileManager::createFile(FileManager::FileType::SOURCE, filename);
                }
                
            } else if (argument == "-h") {
                std::cout << "create header :";

                // TODO .h file include in class
                for(int i=3; i < argc; i++)
                {
                    std::string filename = argv[i];
                    FileManager::createFile(FileManager::FileType::HEADER, filename);
                }
            }
            else if(argument=="-l") {
                
                for(int i=3; i < argc; i++)
                {
                    std::string libraryName = argv[i];
                    FileManager::addDynamicLibrary(libraryName);
                }
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
