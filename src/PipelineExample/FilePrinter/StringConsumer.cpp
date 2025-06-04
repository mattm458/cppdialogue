#include <PipelineExample/StringConsumer.h>

#include <PipelineCore/Consumer.h>

#include <iostream>
#include <string>

StringConsumer::StringConsumer() : Consumer<std::string>() {}

void StringConsumer::consume(std::string& x) { std::cout << x << std::endl; }