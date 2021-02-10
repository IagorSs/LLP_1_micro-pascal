#ifndef REAL_VALUE_H
#define REAL_VALUE_H

#include "Value.h"

class RealValue : public Value<double> {
    public:
        RealValue(double value);
        virtual ~RealValue();

        double value();

    private:
        double m_value;

};

#endif
