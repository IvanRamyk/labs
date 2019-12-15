#include "blogsystem.h"

BlogSystem::BlogSystem()
{

}

void BlogSystem::nextDay(){
    current_date = current_date + Date(0, 0, 1);
}
