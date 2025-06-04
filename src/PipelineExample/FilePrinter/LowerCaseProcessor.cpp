#include <PipelineExample/FilePrinter/LowerCaseProcessor.h>

#include <algorithm>
#include <string>

LowerCaseProcessor::LowerCaseProcessor()
    : Processor<std::string, std::string>() {};

std::string LowerCaseProcessor::process(std::string &in) {
    std::string out = in;

    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return out;
}
