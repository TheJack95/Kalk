#ifndef KALK_H
#define KALK_H

#include "kalkmemory.h"
#include "polynom.h"
#include "euclideanvector.h"

class Kalk
{
private:
  KalkMemory *memoria;
  BaseClass *first;
  BaseClass *second;
public:
  Kalk();
  ~Kalk();

  BaseClass* save(QStringList d, bool);
  BaseClass* getMemory(QString name) const;
  void setF(QStringList);
  void setS(QStringList);
  BaseClass* getFirst() const;
  BaseClass* getSecond() const;
  void del();

  BaseClass* plus() const;
  BaseClass* minus() const;
  BaseClass* per() const;
  BaseClass* div() const;
  BaseClass* operations(QString) const;
};

#endif // KALK_H
