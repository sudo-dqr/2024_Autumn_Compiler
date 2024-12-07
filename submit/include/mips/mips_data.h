#ifndef MIPS_DATA_H
#define MIPS_DATA_H
#include <vector>
#include <string>

struct MipsData {
    std::string name;
    MipsData(std::string name) : name(name) {}
    virtual void print(std::ostream &os) const = 0;
};

struct WordData : public MipsData {
    int value;
    bool is_array = false;
    std::vector<int> array_values;
    WordData(std::string name, int value, bool is_array) 
    : MipsData("g_" + name), value(value), is_array(is_array) {}
    WordData(std::string name, std::vector<int> array_values) 
    : MipsData("g_" + name), array_values(array_values), is_array(true) {}
    void print(std::ostream &os) const override;
};

struct ByteData : public MipsData {
    int value;
    bool is_array = false;
    std::vector<int> array_values;
    ByteData(std::string name, int value, bool is_array) 
    : MipsData("g_" + name), value(value), is_array(is_array) {}
    ByteData(std::string name, std::vector<int> array_values)
    : MipsData("g_" + name), array_values(array_values), is_array(true) {}
    void print(std::ostream &os) const override;
};

struct AsciizData : public MipsData {
    std::string value;
    AsciizData(std::string name, std::string value) :
    MipsData("g_" + name), value(value) {}
    void print(std::ostream &os) const override;
};

#endif // MIPS_DATA_H