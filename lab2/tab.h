#ifndef TAB_H
#define TAB_H

#include "note.h"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>

class Tab : public QWidget
{
    Q_OBJECT
private:
    std::vector<Note> notes;

public:
    Tab();
    void add_note(Note note);
};

#endif // TAB_H
