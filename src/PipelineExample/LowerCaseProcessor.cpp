#include <PipelineExample/LowerCaseProcessor.h>

LowerCaseProcessor::LowerCaseProcessor()
    : Processor<std::string, std::string>() {};

std::string LowerCaseProcessor::process(std::string &in) { return in; }
