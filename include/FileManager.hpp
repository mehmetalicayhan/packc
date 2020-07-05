#ifndef FileManager_HPP
#define FileManager_HPP

#include <string>
#include <map>
#include <cfgpath.h>

using namespace std;

class FileManager {

private:
    string projectDir;
    string projectName;
    string projectVersion;
    string projectAuthor;
    string projectRepository;
    string OS_MAKE;
    string OS_REMOVE;

public:
    enum class FileType {
        CMAKE,
        MAKEFILE,
        HEADER,
        SOURCE ,
        MAIN,
        MAC
    };

    void createCMakeFile();

    void createConfFile();

    void createMainFile();

    static void createSourceFile(const string &name);

    static void createHeaderFile(const string &name);

    void createInitFiles();

    static std::string readFile(const std::string &name, FileType type);

    static bool isFileExist(const string &path);

    static void createFile(FileType type, const string &name);

    static string getPath(FileType type);

    static std::string replace(std::string data, const std::string &replace, const std::string &replaceWith);

    static void addToCMakeFile(const string &name, const string &extension);

    static void addDynamicLibrary(const string &libName);

    FileManager(string &projectName, string &projectVersion, string &projectAuthor, string &projectRepository);

    ~FileManager();

    static string getExtension(FileType type);
};

#endif