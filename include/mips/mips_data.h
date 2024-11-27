#ifndef MIPS_DATA_H
#define MIPS_DATA_H

struct MipsData {
    std::string name;
    virtual void print(std::ostream &os) const = 0;
};

struct WordData : public MipsData {
    int value;
    WordData(int value) : value(value) {}
    void print(std::ostream &os) const override;
};

struct ByteData : public MipsData {
    int value;
    ByteData(int value) : value(value) {}
    void print(std::ostream &os) const override;
};

struct AsciizData : public MipsData {
    std::string value;
    AsciizData(std::string value) : value(value) {}
    void print(std::ostream &os) const override;
};

#endif // MIPS_DATA_H