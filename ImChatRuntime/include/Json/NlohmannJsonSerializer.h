#pragma once
#include "IJsonSerializer.h"


class NlohmannJsonSerializer : public ImChat::IJsonSerializer{


    std::string serialize(const ImChat::Message &msg) const override;

};

