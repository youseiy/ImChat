#pragma once
#include <string>
#include "Serializer.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"


namespace  ImChat {

    class JsonSerializer : public ISerializer{
    public:
        virtual ~JsonSerializer() = default;

        nlohmann::json j;
        void write(const std::string& key, const std::string& value) override {
            j[key] = value;
        }

        void write(const std::string& key, int value) override {
            j[key] = value;
        }

        void write(const std::string& key, double value) override {
            j[key] = value;
        }

        void writeArrayValue(const std::string& arraykey,const JsonField &value) override {

            nlohmann::json jtemp;
            jtemp[value.key]={value.value};
            j[arraykey].push_back(jtemp);
        };

        std::string str() const {
            return j.dump();
        }

        std::string prettyStr(int indent = 2) const {
            return j.dump(indent);
        }

    };

}


