#ifndef OPENSEESMODELGENERATOR_H
#define OPENSEESMODELGENERATOR_H

#include <string>
using namespace std;

class OpenseesModelGenerator
{
public:

    OpenseesModelGenerator();
    void randPara();
    void writeModel();




private:
    int _seed;
    string _randPath;
    string _framePath;
    string _nodePath;
    string _elementPath;

};

#endif // OPENSEESMODELGENERATOR_H
