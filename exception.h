#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception {
public:
    virtual ~Exception()=default;
    virtual QString toQString() const =0;
};

class InvalidOperation : public Exception {
public:
  QString toQString() const;
};

class DataErr : public Exception {
public:
  QString toQString() const;
};

class NameUsed : public Exception {
public:
    QString toQString() const;
};

class InvalidName : public Exception {
public:
  QString toQString() const;
};

class NotFound : public Exception {
public:
  QString toQString() const;
};

class FullMemory : public Exception {
public:
  QString toQString() const;
};

class InvalidPolynom : public Exception {
public:
  QString toQString() const;
};





#endif // EXCEPTION_H
