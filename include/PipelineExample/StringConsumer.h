#pragma once

#include <PipelineCore/Consumer.h>

class StringConsumer : public Consumer<std::string> {
   public:
    StringConsumer();

    void consume(std::string& x) override;
};