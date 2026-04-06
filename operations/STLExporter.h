#ifndef STLEXPORTER_H
#define STLEXPORTER_H

#include <string>
#include "DataClass.h"

class STLExporter {
public:
    static bool exportToAsciiSTL(const DataClass& meshData, const std::string& filename);
};

#endif // STLEXPORTER_H
