
#pragma once
#ifndef GUARD_Intl_h
#define GUARD_Intl_h

#include <iostream>
#include "core.h"

using namespace std;

class International : public Core {
public:
    International() : toeic(0) { };
    International(istream& is) { read(is); }

    double grade() const;
    istream& read(istream&);

private:
    double toeic;
    International* clone() const { return new International(*this); }
};

#endif
