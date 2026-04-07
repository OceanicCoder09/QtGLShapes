#ifndef STLIMPORTER_H
#define STLIMPORTER_H

#include <string>
#include "DataClass.h"

class STLImporter {
public:
    static bool importFromAsciiSTL(const std::string& filename, DataClass& meshData);
};

#endif // STLIMPORTER_H
