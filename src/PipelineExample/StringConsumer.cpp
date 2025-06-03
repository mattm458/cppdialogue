#include <PipelineExample/StringConsumer.h>

#include <PipelineCore/Consumer.h>

#include <iostream>
#include <string>

StringConsumer::StringConsumer() : Consumer() {}

void StringConsumer::step() {
    if (this->consumable()) {
        std::cout << this->consume() << std::endl;
    }
}