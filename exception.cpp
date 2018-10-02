#include "exception.h"

QString NameUsed::toQString() const {
    return QString("Nome già in uso; sceglierne un altro.");
}

QString InvalidPolynom::toQString() const {
    return QString("Polinomio inserito nella forma sbagliata.");
}

QString NotFound::toQString() const {
    return QString("Nome non trovato. Oggetto non prensente in momoria.");
}

QString FullMemory::toQString() const {
  return QString("Memoria piena.");
}

QString InvalidName::toQString() const {
    return QString("Nome non ammesso. Usa nomi composti da un carattere alfabetico");
}

QString DataErr::toQString() const {
  return QString("Errore nei dati inseriti. Riprova.");
}

QString InvalidOperation::toQString() const {
  return QString("Attenzione: non puoi eseguire operazioni tra vettori e polinomi");
}
