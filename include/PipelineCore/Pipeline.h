#pragma once

#include <PipelineBase/Runnable.h>

#include <vector>

class Pipeline : Runnable {
   public:
    void step() override { return; }

    void add_stage(Runnable *runnable) {
        if (this->complete) {
            throw std::runtime_error(
                "New stages cannot be added to a complete pipeline!");
        }

        this->stages.push_back(runnable);
    }

    void finalize() { this->complete = true; }

   private:
    bool complete = false;
    std::vector<Runnable *> stages;
};