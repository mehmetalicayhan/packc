
#ifndef PROJECTGENERATOR_HPP
#define PROJECTGENERATOR_HPP
#include <fstream>
#include "json.hpp"
#include "FileManager.hpp"
class ProjectGenerator{
private:

public:
    ProjectGenerator();
    ~ProjectGenerator();

    static void proccessFile();
};
#endif //PROJECTGENERATOR_HPP
