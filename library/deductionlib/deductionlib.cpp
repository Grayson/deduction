//
//  deductionlib.cpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <iostream>
#include "deductionlib.hpp"
#include "deductionlibPriv.hpp"

void deductionlib::HelloWorld(const char * s)
{
    deductionlibPriv *theObj = new deductionlibPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void deductionlibPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

