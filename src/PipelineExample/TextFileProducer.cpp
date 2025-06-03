#include <PipelineExample/TextFileProducer.h>

#include <PipelineCore/Producer.h>

#include <iostream>
#include <string>

TextFileProducer::TextFileProducer(const std::string& filename) : Producer() {
    this->infile.open(filename);
}

void TextFileProducer::step() {
    std::string line;

    if (std::getline(this->infile, line))
        this->produce(line);
    else
        this->stop();
}