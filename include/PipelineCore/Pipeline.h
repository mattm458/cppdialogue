#pragma once

#include <PipelineBase/Runnable.h>

#include <future>
#include <vector>

class Pipeline : public Runnable {
   public:
    void add_stage(Runnable *runnable) {
        if (this->complete) {
            throw std::runtime_error(
                "New stages cannot be added to a complete pipeline!");
        }

        this->stages.push_back(runnable);
    }

    void finalize() { this->complete = true; }

   protected:
    void on_startup() override {
        for (int i = this->stages.size() - 1; i >= 0; i--) {
            this->futures.push_back(this->stages[i]->start());
        };
    }

    void step() override { return; }

   private:
    bool complete = false;
    std::vector<Runnable *> stages;
    std::vector<std::future<void>> futures;
};