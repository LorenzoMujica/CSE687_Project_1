#include "FileManagement.h"
#include "Map.h"
#include "sorter.h"
#include "reducer.h"
#include "rWorkflow.h"

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <input_dir> <output_dir> <temp_dir>\n";
        return 1;
    }

    std::string inputDir = argv[1];
    std::string outputDir = argv[2];
    std::string tempDir = argv[3];

    try {
        FileManagement fileMgmt(inputDir, outputDir, tempDir);
        Map mapper(fileMgmt, tempDir + "/intermediate.txt", 8192);
        Sorter sorter;
        Reducer reducer;

        Workflow workflow(fileMgmt, mapper, sorter, reducer);
        bool success = workflow.Run();

        return success ? 0 : 2;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }
}
