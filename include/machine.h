//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_MACHINE_H
#define OOP_MACHINE_H


class machine {
    //date in funcție de fiecare masina in parte
public:
    virtual ~machine()=default;
    virtual void update()=0;
};


#endif //OOP_MACHINE_Hs