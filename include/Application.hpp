#ifndef  Application_HPP
#define  Application_HPP

#include "ProjectCreator.hpp"
#include "ProjectBuilder.hpp"

class Application {

private:
    ProjectBuilder *projectBuilder;
    ProjectCreator *projectCreator;


public:
    Application(int argc, char const *argv[]);

    ~Application();
};

#endif