#ifndef BASECLASS_H
#define BASECLASS_H

#include <QString>
#include "exception.h"

class BaseClass
{
private:
  QString name;
public:
  BaseClass(QString name="null");
  BaseClass(const BaseClass&);
  virtual QString print() const;
  virtual ~BaseClass() =default;
  void setName(QString name) ;
  QString getName() const;
  virtual BaseClass* operator+(const BaseClass& b) const;
  virtual BaseClass* operator-(const BaseClass& b) const;
  virtual BaseClass* operator*(const BaseClass& b) const;
  virtual BaseClass* operator/(const BaseClass& b);
  virtual BaseClass* operator=(const BaseClass& b);
};

#endif // BASECLASS_H
