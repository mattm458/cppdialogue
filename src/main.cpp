#include <SDL3/SDL.h>

#include <PipelineCore/PipelineBuilder.h>

#include <PipelineExample/FilePrinter/LowerCaseProcessor.h>
#include <PipelineExample/FilePrinter/StringConsumer.h>
#include <PipelineExample/FilePrinter/TextFileProducer.h>

#include <future>
#include <iostream>
#include <memory>
#include <string>

int main() {
    Pipeline *p = PipelineBuilder::BuildPipeline<TextFileProducer>(
                      "example_data/frankenstein.txt")
                      .then<LowerCaseProcessor>()
                      .close<StringConsumer>();

    std::future<void> f = p->start();

    while (true) std::this_thread::yield();
}