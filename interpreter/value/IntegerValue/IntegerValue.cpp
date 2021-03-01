#include "IntegerValue.h"

IntegerValue::IntegerValue(int value)
  : Value(Type::IntegerType), m_value(value) {
}

IntegerValue::~IntegerValue() {
}

void IntegerValue::setValue(int value) {
  m_value = value;
}

int IntegerValue::value() {
    return m_value;
}
