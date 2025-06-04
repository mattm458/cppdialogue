#pragma once

#include <PipelineCore/Consumer.h>
#include <PipelineCore/Producer.h>

#include <fstream>

class TextFileProducer : public Producer<std::string> {
   public:
    TextFileProducer(const std::string& filename);

    std::string produce() override;

   private:
    std::ifstream infile;
};