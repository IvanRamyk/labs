//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_BASE2_H
#define TASK3_BASE2_H

#include <memory>

class Base1;

class Base2 {
protected:
    int& count () const;
    int N;
    Base2(std::shared_ptr<Base1> _base1 = nullptr, std::shared_ptr<Base2> _base2 = nullptr);
    ~Base2();

private:
    std::shared_ptr<Base2>  base2;
    std::shared_ptr<Base1>  base1;
public:
    void setBase1(std::shared_ptr<Base1> base);
    void setBase2(std::shared_ptr<Base2> base);
    int getN();
};




#endif //TASK3_BASE2_H
