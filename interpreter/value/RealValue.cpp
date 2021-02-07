#include "RealValue.h"

RealValue::RealValue(double value)
  : Value(Type::RealType), m_value(value) {
}

RealValue::~RealValue() {
}

double RealValue::value() {
    return m_value;
}
