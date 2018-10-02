#ifndef KALKMEMORY_H
#define KALKMEMORY_H

#include "baseclass.h"
#include <QVector>

class KalkMemory
{
private:
  QVector<BaseClass*> memory;
public:
  KalkMemory();
  ~KalkMemory();
  BaseClass* getLast() const;
  void insert(BaseClass *);
  BaseClass* search(QString) const;
};

#endif // KALKMEMORY_H
