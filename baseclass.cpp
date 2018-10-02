#include "baseclass.h"

BaseClass::BaseClass(QString name): name(name) {}

BaseClass::BaseClass(const BaseClass& a) : name(a.name) {}

void BaseClass::setName(QString name) { name=name; }

QString BaseClass::getName() const { return name; }

QString BaseClass::print() const { return name; }

BaseClass* BaseClass::operator+(const BaseClass& b) const { return new BaseClass(name+"+"+b.name); }

BaseClass* BaseClass::operator-(const BaseClass& b) const { return new BaseClass(name+"-"+b.name); }

BaseClass* BaseClass::operator*(const BaseClass& b) const { return new BaseClass(name+"*"+b.name); }

BaseClass* BaseClass::operator/(const BaseClass& b)  { name=name+"/"+b.name; return this; }

BaseClass* BaseClass::operator=(const BaseClass& b)
{
  if(this!=&b)
    {
      name=b.name;
    }
  return this;
}
