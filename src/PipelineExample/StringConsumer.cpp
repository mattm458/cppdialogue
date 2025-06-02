#include <PipelineExample/StringConsumer.h>

#include <PipelineCore/Consumer.h>
#include <PipelineCore/Producer.h>

#include <iostream>
#include <string>

StringConsumer::StringConsumer() : Consumer() {}

StringConsumer::StringConsumer(Producer<std::string>& producer)
    : Consumer(producer) {}

void StringConsumer::step() {
    if (this->consumable()) {
        std::cout << this->consume() << std::endl;
    }
}