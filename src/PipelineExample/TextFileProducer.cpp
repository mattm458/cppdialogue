#include <PipelineExample/TextFileProducer.h>

#include <PipelineCore/Producer.h>

#include <iostream>
#include <string>

TextFileProducer::TextFileProducer(const std::string& filename) : Producer() {
    this->infile.open(filename);
}

std::string TextFileProducer::produce() {
    std::string line;

    if (std::getline(this->infile, line))
        return line;
    else {
        this->stop();
        return line;
    }
}