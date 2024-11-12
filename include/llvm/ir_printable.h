#ifndef IR_PRINTABLE_H
#define IR_PRINTABLE_H

#include <iostream>

class IRPrintable {
    public:
        virtual void print(std::ostream &os) const = 0;
        virtual ~IRPrintable() = default;
};

#endif // IR_PRINTABLE_H