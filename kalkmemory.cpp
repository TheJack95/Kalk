#include "kalkmemory.h"
#include "polynom.h"

KalkMemory::KalkMemory() : memory() {}

KalkMemory::~KalkMemory()
{
  while(memory.size() > 0)
    delete memory[0];
}

BaseClass* KalkMemory::getLast() const { return memory.last(); }

void KalkMemory::insert(BaseClass *b)
{
  if(memory.size()==26)
      throw FullMemory();

  if(b->getName().size() != 1)
    throw InvalidName();

  for(int i=0; i<memory.size(); ++i)
    if(memory[i]->getName() == b->getName())
      throw NameUsed();

    memory.push_back(b);
}

BaseClass* KalkMemory::search(QString b) const
{
  for(int i=0; i<memory.size(); ++i)
    if(memory[i]->getName() == b)
      return memory[i];

  throw NotFound();
}




