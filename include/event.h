//
// Created by stefa on 4/6/2026.
//

#ifndef OOP_EVENT_H
#define OOP_EVENT_H

#include <string>

class event{
    std::string type="default";
protected:
    virtual std::string getType();
public:
    virtual ~event()=default;
};


#endif //OOP_EVENT_H