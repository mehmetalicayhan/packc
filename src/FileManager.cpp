#include "FileManager.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;

FileManager::FileManager(std::string &projectName, std::string &projectVersion,
                         std::string &projectAuthor, std::string &projectRepository)
{
    this->projectName = projectName;
    this->projectVersion = projectVersion;
    this->projectAuthor = projectAuthor;
    this->projectDir = "./" + projectName;
    this->projectRepository = projectRepository;
#ifdef _WIN32
    OS_MAKE = "mingw32-make";
    OS_REMOVE = "rmdir";
#elif __unix__ || __APPLE__
    OS_MAKE = "make";
    OS_REMOVE = "rm -rf";
#endif
}

void FileManager::createCMakeFile()
{

    std::string filePath = getConfigPath(true);
    filePath += "cmake.tempp";
    ifstream templateFile(filePath);
    std::string fileContent;
    if (templateFile)
    {
        ostringstream ss;
        ss << templateFile.rdbuf();
        fileContent = ss.str();
    }
    templateFile.close();

    std::ofstream cmakeFile(projectDir + "/CMakeLists.txt");
    fileContent = FileManager::replaceString(fileContent, "<ProjectName>", projectName);
    cmakeFile << fileContent;
    cmakeFile.close();
}

void FileManager::createConfFile()
{

    json j2 = {
        {"Project Name", projectName},
        {"Version", projectVersion},
        {"Author", projectAuthor},
        {"Repository", projectRepository},
        {"commands", {{"run", "cd build && ./" + projectName}, {"build", "cd build && cmake .. && " + OS_MAKE}, {"clean", OS_REMOVE + " build"}}}};
    std::ofstream macFile(projectDir + "/packc.json");

    macFile << j2.dump(4);

    macFile.close();
}

void FileManager::createMainFile()
{
    std::string filePath;
    filePath = getConfigPath(true);
    filePath += "main.tempp";
    ifstream templateFile(filePath);
    std::string fileContent;
    if (templateFile)
    {
        ostringstream ss;
        ss << templateFile.rdbuf();
        fileContent = ss.str();
    }

    templateFile.close();

    std::string mainPath = projectDir + "/src/main.cpp";
    std::ofstream mainFile(mainPath);
    mainFile
        << fileContent;
    mainFile.close();
}

void FileManager::createInitFiles()
{
    createCMakeFile();
    createConfFile();
    createMainFile();
}

bool FileManager::isFileExist(const std::string &path)
{
    if (FILE *file = fopen(path.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

void FileManager::createFile(FileType type, const std::string &name)
{
    std::string fileExtension = getExtension(type);
    std::string filePath = getPath(type) + name + fileExtension;

    std::string fileContent = readFile(name, type);
    std::cout << filePath;
    std::ofstream file(filePath);

    fileContent = replaceString(fileContent, "<FileName>", name);

    if (isFileExist("./packc.json"))
    {
        file << fileContent;
        if (type == FileType::SOURCE)
        {
            addToCMakeFile(name, ".cpp");
        }
        else if (type == FileType::HEADER)
        {
            addToCMakeFile(name, ".hpp");
        }
        else
        {
            file.close();
            return;
        }
    }

    file.close();
}

std::string FileManager::readFile(const std::string &name, FileType type)
{

    std::string filePath = getConfigPath(true);
    switch (type)
    {
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

    while (getline(readFile, line))
    {
        fileContent += line;
        fileContent += "\n";
    }

    readFile.close();

    return fileContent;
}

void FileManager::addToCMakeFile(const std::string &name, const std::string &extension)
{
    if (isFileExist("./CMakeLists.txt"))
    {
        std::fstream file("./CMakeLists.txt", std::ios::in);
        std::string replace;
        std::string replace_with;

        if (extension == ".cpp")
        {
            replace = "set(PROJECT_SOURCES";
            replace_with = "set(PROJECT_SOURCES\n${PROJECT_SOURCE_DIR}/" + name + ".cpp";
        }
        else
        {
            replace = "set(PROJECT_HEADERS";
            replace_with = "set(PROJECT_HEADERS\n${PROJECT_INCLUDE_DIR}/" + name + ".hpp";
        }
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line))
        {

            std::string::size_type pos = 0;

            while ((pos = line.find(replace, pos)) != std::string::npos)
            {
                line.replace(pos, line.size(), replace_with);
                pos += replace_with.size();
            }

            lines.push_back(line);
        }
        file.close();
        file.open("./CMakeLists.txt", std::ios::out | std::ios::trunc);

        for (const auto &i : lines)
        {
            file << i << std::endl;
        }
    }
}

void FileManager::addDynamicLibrary(const string &libName)
{
    if (isFileExist("./CMakeLists.txt"))
    {
        std::fstream file("./CMakeLists.txt", std::ios::in);
        std::string replace;
        std::string replaceWith;
        replace = "set(SHARED_FLAGS";
        replaceWith = "set(SHARED_FLAGS\n -l" + libName;
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line))
        {
            line = replaceString(line, replace, replaceWith);
            lines.push_back(line);
        }
        file.close();
        file.open("./CMakeLists.txt", std::ios::out | std::ios::trunc);

        for (const auto &i : lines)
        {
            file << i << std::endl;
        }
        file.close();
    }
}

string FileManager::getPath(FileManager::FileType type)
{
    switch (type)
    {
    case FileType::SOURCE:
    case FileType::MAIN:
        return "./src/";
    case FileType::HEADER:
        return "./include/";
    default:
        return "./";
    }
}

std::string FileManager::replaceString(string orgString, const string search, const string replace)
{
    for (size_t pos = 0;; pos += replace.length())
    {
        pos = orgString.find(search, pos);
        if (pos == string::npos)
            break;
        orgString.erase(pos, search.length());
        orgString.insert(pos, replace);
    }
    return orgString;
}

string FileManager::getExtension(FileManager::FileType type)
{
    if (type == FileType::SOURCE || type == FileType::MAIN)
    {
        return ".cpp";
    }
    else if (type == FileType::HEADER)
    {
        return ".hpp";
    }
    else
    {
        return "";
    }
}

FileManager::~FileManager()
{
    delete this;
}

string FileManager::getConfigPath(bool isTest)
{
    if (isTest)
    {
        return "../../templates/";
    }
    char configDir[256];
    get_user_config_folder(configDir, sizeof(configDir), "packc");
    if (configDir[0] == 0)
    {
        std::cout << "Unable to find home directory.\n";
    }
    return configDir;
}
