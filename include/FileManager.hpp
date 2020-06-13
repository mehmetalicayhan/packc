#ifndef FileManager_HPP
#define FileManager_HPP

#include <string>

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
        SOURCE,
        MAIN,
        MAC
    };

    void createCMakeFile();

    void createConfFile();

    void createMainFile();

    static void createSourceFile(const string &name, bool isClass);

    static void createHeaderFile(const string &name);

    void createInitFiles();

    static bool isFileExist(const string &path);

    static void createFile(FileType type, const string &name);

    static void addToCMakeFile(const string &name, const string &extension);

    FileManager(string &projectName, string &projectVersion, string &projectAuthor, string &projectRepository);

    ~FileManager();
};

#endif