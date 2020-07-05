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
    cmakeFile << "cmake_minimum_required(VERSION 2.8)\n\n"
              << "project(" + projectName + ")\n\n"
              << "set(SHARED_FLAGS\n)\n"
              << "set(CMAKE_C_FLAGS \"-std=c17 ${SHARED_FLAGS}\")\n"
              << "set(CMAKE_CXX_FLAGS \"-std=c++17 ${SHARED_FLAGS}\")\n\n"
              << "set(PROJECT_DIR ${CMAKE_SOURCE_DIR})\n\n"
              << "set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)\n\n"
              << "set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)\n\n"
              << "set(PROJECT_SOURCES\n${PROJECT_SOURCE_DIR}/main.cpp)\n\n"
              << "set(PROJECT_HEADERS\n)\n\n"
              << "include_directories(${PROJECT_INCLUDE_DIR})\n\n"
              << "add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})\n\n";
    cmakeFile.close();
}

void FileManager::createConfFile() {

    json j2 = {
            {"Project Name", projectName},
            {"Version",      projectVersion},
            {"Author",       projectAuthor},
            {"Repository",   projectRepository},
            {"commands",     {{"run", "cd build && ./" + projectName}, {"build", "cd build && cmake .. && " +
                                                                                 OS_MAKE}, {"clean", OS_REMOVE +
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

void FileManager::createSourceFile(const std::string &name) {
    std::string srcFilePath = "./src/" + name + ".cpp";
    std::string fileContent = readFile(name,FileType::SOURCE);
    std::string::size_type pos = 0;
    while ((pos = fileContent.find("<ProjectName>", pos)) != std::string::npos) {
        fileContent.replace(pos, fileContent.size(), name);
        pos += name.size();
    }
    std::ofstream sourceFile(srcFilePath);
    sourceFile << fileContent;
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
    std::string fileExtension = getExtension(type);
    std::string filePath = getPath(type) + name + fileExtension;

    std::string fileContent = readFile(name,FileType::SOURCE);
    std::cout<<filePath;
    std::ofstream file(filePath);
    fileContent = FileManager::replace(fileContent,"<ProjectName>",name);
    if (isFileExist("./packc.json")) {
        file<<fileContent;
        if (type == FileType::SOURCE) {
            addToCMakeFile(name, ".cpp");
        } else if (type == FileType::HEADER) {
            addToCMakeFile(name, ".hpp");
        } else {
            file.close();
            return;
        }
    }

    file.close();
}


std::string FileManager::readFile(const std::string& name,FileType type) {
    char cfgdir[256];
    get_user_config_folder(cfgdir, sizeof(cfgdir), "packc");
    if (cfgdir[0] == 0) {
        std::cout << "Unable to find home directory.\n";
    }
    std::cout << cfgdir << std::endl;
    std::string filePath = "../../templates/";
    switch (type) {
        case FileType::SOURCE:
            filePath += "source.tempp";
            break;
        case FileType::HEADER:
            filePath += "header.tempp";
            break;
        default:
            break;
    }

    ifstream readFile(filePath);
    std::string fileContent;
    std::string line;

    while (getline(readFile, line)) {
        fileContent += line;
        fileContent += "\n";
    }

    readFile.close();

    return fileContent;
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

void FileManager::addDynamicLibrary(const string &libName) {
    if (isFileExist("./CMakeLists.txt")) {
        std::fstream file("./CMakeLists.txt", std::ios::in);
        std::string replace;
        std::string replaceWith;
        replace = "set(SHARED_FLAGS";
        replaceWith = "set(SHARED_FLAGS\n -l" + libName;
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {

            line = FileManager::replace(line, replace, replaceWith);

            lines.push_back(line);
        }
        file.close();
        file.open("./CMakeLists.txt", std::ios::out | std::ios::trunc);

        for (const auto &i : lines) {
            file << i << std::endl;
        }
    }
}

std::string FileManager::replace(std::string data, const std::string &replace, const std::string &replaceWith) {
    std::string::size_type pos = 0;

    while ((pos = data.find(replace, pos)) != std::string::npos) {
        data.replace(pos, data.size(), replaceWith);
        pos += replaceWith.size();
    }

    return data;
}

FileManager::~FileManager() {
    delete this;
}

string FileManager::getPath(FileManager::FileType type) {
    switch (type) {
        case FileType::SOURCE:
        case FileType::MAIN:
            return "./src/";
        case FileType::HEADER:
            return "./include/";
        default:
            return "./";
    }
}

string FileManager::getExtension(FileManager::FileType type){
    if(type == FileType::SOURCE || type == FileType::MAIN){
        return ".cpp";
    } else if(type == FileType::HEADER){
        return ".hpp";
    } else {
        return "";
    }
}

