#pragma once
#include <string>

struct JsonField {
    std::string key;
    std::string value;
};


struct ISerializer {
    virtual ~ISerializer() = default;

    virtual void write(const std::string& key, const std::string& value) = 0;
    virtual void write(const std::string& key, int value) = 0;
    virtual void write(const std::string& key, double value) = 0;

    virtual void writeArrayValue(const std::string& keyarray,const JsonField& value={}) = 0;

};