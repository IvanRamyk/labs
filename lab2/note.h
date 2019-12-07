#ifndef NOTE_H
#define NOTE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Note
{
private:
    QString text;
    QString name;

public:
    Note(QString text = "", QString name = "");
};

#endif // NOTE_H
