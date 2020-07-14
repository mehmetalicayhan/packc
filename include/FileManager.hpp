#ifndef FileManager_HPP
#define FileManager_HPP

#include <string>
#include <map>
#include <cfgpath.h>

using namespace std;

class FileManager
{

private:
    string projectDir;
    string projectName;
    string projectVersion;
    string projectAuthor;
    string projectRepository;
    string OS_MAKE;
    string OS_REMOVE;

public:
    enum class FileType
    {
        CMAKE,
        MAKEFILE,
        HEADER,
        SOURCE,
        MAIN,
        CONF
    };

    void createCMakeFile();

    void createConfFile();

    void createMainFile();

    void createInitFiles();

    static std::string readFile(const std::string &name, FileType type);

    static bool isFileExist(const string &path);

    static void createFile(FileType type, const string &name);

    static string getPath(FileType type);

    static string getExtension(FileType type);

    static string replaceString(string orgString, const string search, const string replace);

    static void addToCMakeFile(const string &name, const string &extension);

    static void addDynamicLibrary(const string &libName);

    FileManager(string &projectName, string &projectVersion, string &projectAuthor, string &projectRepository);

    static string getConfigPath(bool isTest = false);

    ~FileManager();
};

#endif