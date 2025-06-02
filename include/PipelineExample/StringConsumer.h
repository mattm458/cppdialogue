#pragma once

#include <PipelineCore/Consumer.h>
#include <PipelineCore/Producer.h>

class StringConsumer : public Consumer<std::string> {
   public:
    StringConsumer();
    StringConsumer(Producer<std::string>& producer);

    void step() override;
};