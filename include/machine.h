//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_MACHINE_H
#define OOP_MACHINE_H
#include <iostream>


class machine {
    //date in funcție de fiecare masina in parte
public:
    virtual ~machine()=default;
    virtual void update()=0;
    virtual void check_input(machine*);
    virtual void check_output(machine*);
    friend std::ostream& operator<<(std::ostream&,const machine&);
    friend std::istream& operator>>(std::istream&,machine&);

};


#endif //OOP_MACHINE_Hs