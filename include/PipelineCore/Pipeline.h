#pragma once

#include <PipelineBase/Runnable.h>

#include <vector>

class Pipeline : Runnable {
   public:
    Pipeline(std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages)
        : Runnable(), stages(stages) {}

    void step() override { return; }

   private:
    std::shared_ptr<std::vector<std::shared_ptr<Runnable>>> stages;
};