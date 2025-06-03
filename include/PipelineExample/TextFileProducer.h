#pragma once

#include <PipelineCore/Consumer.h>
#include <PipelineCore/Producer.h>

#include <fstream>

class TextFileProducer : public Producer<std::string> {
   public:
    TextFileProducer(const std::string& filename);

    void step() override;

   private:
    std::ifstream infile;
};