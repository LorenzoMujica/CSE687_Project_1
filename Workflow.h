#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "FileManagement.h"
#include "Map.h"
#include "sorter.h"
#include "reducer.h"

class Workflow {
public:
    Workflow(FileManagement& fileMgmt,
             Map& mapper,
             Sorter& sorter,
             Reducer& reducer);

    bool Run();  // runs the entire map-reduce workflow

private:
    FileManagement& fileMgmt_;
    Map& mapper_;
    Sorter& sorter_;
    Reducer& reducer_;
};

#endif
