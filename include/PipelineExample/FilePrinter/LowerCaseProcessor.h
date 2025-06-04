#pragma once

#include <PipelineCore/Processor.h>

class LowerCaseProcessor : public Processor<std::string, std::string> {
   public:
    LowerCaseProcessor();

   protected:
    std::string process(std::string &in) override;
};