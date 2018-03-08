//
//  utility.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#define EXPORT __attribute__((visibility("default")))

// Damn you, c++17 according to Xcode stdlib!
#include <experimental/optional>
#ifdef _LIBCPP_EXPERIMENTAL_OPTIONAL
#define stdoptional std::experimental::optional
#else
#define stdoptional std::optional
#endif
