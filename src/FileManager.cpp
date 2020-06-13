#include "FileManager.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

FileManager::FileManager(std::string &projectName, std::string &projectVersion,
                         std::string &projectAuthor, std::string &projectRepository) {
    this->projectName = projectName;
    this->projectVersion = projectVersion;
    this->projectAuthor = projectAuthor;
    this->projectDir = "./" + projectName;
    this->projectRepository = projectRepository;
#ifdef _WIN32
    OS_MAKE = "mingw32-make";
    OS_REMOVE = "rmdir";
#elif __unix__
    OS_MAKE = "make";
    OS_REMOVE = "rm -rf";
#endif
}

void FileManager::createCMakeFile() {
    std::ofstream cmakeFile(projectDir + "/CMakeLists.txt");
    cmakeFile << "cmake_minimum_required(VERSION 2.8)"
              << "\n"
              << "project(" + projectName + ")\n"
              << "set(PROJECT_DIR ${CMAKE_SOURCE_DIR})\n"
              << "set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)\n"
              << "set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)\n"
              << "set(PROJECT_SOURCES\n${PROJECT_SOURCE_DIR}/main.cpp)\n"
              << "set(PROJECT_HEADERS\n)\n"
              << "include_directories(${PROJECT_INCLUDE_DIR})\n"
              << "add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})\n";
    cmakeFile.close();
}

void FileManager::createConfFile() {
    /*
    "commands" : {}
      "run" : "cd build"
      "build" : "naber"
      "create" : "what"
    }

  */
    json j2 = {
            {"Project Name", projectName},
            {"Version",      projectVersion},
            {"Author",       projectAuthor},
            {"Repository",   projectRepository},
            {"commands",     {{"run", "cd build && ./" +
                                      projectName}, {"build", "cd build && cmake .. && " + OS_MAKE}, {"clean",
                                                                                                             OS_REMOVE +
                                                                                                             " build"}}}};
    std::ofstream macFile(projectDir + "/packc.json");

    macFile << j2.dump(4);

    macFile.close();
}

void FileManager::createMainFile() {
    std::string mainPath = projectDir + "/src/main.cpp";
    std::ofstream mainFile(mainPath);
    mainFile
            << "#include<iostream>\n\nint main(int argc,char** argv){\n\n\tstd::cout<<\"Hello World\"<<std::endl;\n\n\treturn 0;\n\n}";
    mainFile.close();
}

void FileManager::createSourceFile(const std::string &name, bool isClass) {
    std::string srcFilePath = "./src/" + name + ".cpp";
    std::ofstream sourceFile(srcFilePath);
    std::string fileData;
    fileData = isClass ?
               sourceFile << "//#include \" " + name + ".hpp\" \n"

                          // << "class " + name + "\n"
                          //<< "{\n"
                          //<< "private: \n\n"
                          //<< "public: \n\n"
                          //<< "   " + name + "(/* args */); \n"
                          //<< "   ~" + name + "(); \n"
                          //<< "};\n"
                          //<< "\n"
                          << name + "::" + name + "(/*args*/)\n"
                          << "{\n"
                          << "}\n"
                          << name + "::" + "~" + name + "()\n"
                          << "{\n"
                          << "}\n";
    sourceFile.close();
}

void FileManager::createHeaderFile(const std::string &name) {
    std::string headerFilePath = "./include/" + name + ".hpp";
    std::ofstream headerFile(headerFilePath);

    headerFile << "#ifndef " + name + "_HPP\n"
               << "#define " + name + "_HPP\n"
               << "class " + name + "\n"
               << "{\n"
               << "private: \n\n"
               << "public: \n\n"
               << "   " + name + "(/* args */); \n"
               << "   ~" + name + "(); \n"
               << "};\n"
               << "\n\n"
               << "#endif";

    headerFile.close();
}

void FileManager::createInitFiles() {
    createCMakeFile();
    createConfFile();
    createMainFile();
}

bool FileManager::isFileExist(const std::string &path) {
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void FileManager::createFile(FileType type, const std::string &name) {
    std::ofstream file;
    if (isFileExist("./packc.json")) {
        if (type == FileType::SOURCE) {
            createSourceFile(name);
            addToCMakeFile(name, ".cpp");
        } else if (type == FileType::HEADER) {
            createHeaderFile(name);
            addToCMakeFile(name, ".hpp");
        } else {
            return;
        }
    }
}

void FileManager::addToCMakeFile(const std::string &name, const std::string &extension) {
    if (isFileExist("./CMakeLists.txt")) {
        std::fstream file("./CMakeLists.txt", std::ios::in);
        std::string replace;
        std::string replace_with;

        if (extension == ".cpp") {
            replace = "set(PROJECT_SOURCES";
            replace_with = "set(PROJECT_SOURCES\n${PROJECT_SOURCE_DIR}/" + name + ".cpp";
        } else {
            replace = "set(PROJECT_HEADERS";
            replace_with = "set(PROJECT_HEADERS\n${PROJECT_INCLUDE_DIR}/" + name + ".hpp";
        }
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {

            std::string::size_type pos = 0;

            while ((pos = line.find(replace, pos)) != std::string::npos) {
                line.replace(pos, line.size(), replace_with);
                pos += replace_with.size();
            }

            lines.push_back(line);
        }
        file.close();
        file.open("./CMakeLists.txt", std::ios::out | std::ios::trunc);

        for (const auto &i : lines) {
            file << i << std::endl;
        }
    }
}

FileManager::~FileManager() {
    delete this;
}


