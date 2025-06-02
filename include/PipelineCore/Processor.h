#pragma once

#include <PipelineCore/Consumer.h>
#include <PipelineCore/Producer.h>

template <typename InType, typename OutType>
class Processor : public Consumer<InType>, public Producer<OutType> {};