//
// Created by Ivan Ramyk on 10/29/19.
//

#ifndef TASK3_BASE1_H
#define TASK3_BASE1_H

#include <memory>

class Base2;

class Base1 {
protected:
    int& count () const;
    int N;
    Base1(std::shared_ptr<Base1> _base1 = nullptr, std::shared_ptr<Base2> _base2 = nullptr);
    ~Base1();

private:
    std::shared_ptr<Base2>  base2;
    std::shared_ptr<Base1>  base1;
public:
    void setBase1(std::shared_ptr<Base1> base);
    void setBase2(std::shared_ptr<Base2> base);
    std::shared_ptr<Base1> getBase1();
    std::shared_ptr<Base2> getBase2();
    int getN();
};


#endif //TASK3_BASE1_H
