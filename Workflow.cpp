#include "Workflow.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

Workflow::Workflow(FileManagement& fileMgmt,
                   Map& mapper,
                   Sorter& sorter,
                   Reducer& reducer)
    : fileMgmt_(fileMgmt),
      mapper_(mapper),
      sorter_(sorter),
      reducer_(reducer) {}

bool Workflow::Run() {
    try {
        fileMgmt_.initialize();

        auto inputFiles = fileMgmt_.inputFiles();
        for (const auto& file : inputFiles) {
            std::ifstream inFile = fileMgmt_.openFile(file);
            std::string line;
            while (std::getline(inFile, line)) {
                mapper_.map(file.filename().string(), line);
            }
        }
        mapper_.finalize();

        std::string intermediatePath = "temp/intermediate.txt";
        auto aggregatedData = sorter_.Aggregate(intermediatePath);
        sorter_.ExportAggregated(aggregatedData, "temp/aggregated.txt");

        reducer_.SetOutputDir(fileMgmt_.getOutputDir());
        for (auto& [key, values] : aggregatedData) {
            reducer_.Reduce(key, values);
        }
        reducer_.Flush();

        fileMgmt_.writeFile();
        std::cout << "Workflow completed successfully.\n";
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Workflow failed: " << e.what() << "\n";
        return false;
    }
}
