#include "tab.h"

Tab::Tab()
{
    add_note(Note("llksajdlkasj", "alsdhlaskd"));
}

void Tab::add_note(Note note){
    notes.push_back(note);
}
