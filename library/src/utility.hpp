//
//  utility.hpp
//  deductionlib
//
//  Created by Grayson Hansard on 3/6/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#pragma once

#define EXPORT __attribute__((visibility("default")))

#ifdef __APPLE__
#include <experimental/optional>
#ifdef _LIBCPP_EXPERIMENTAL_OPTIONAL
#define stdoptional std::experimental::optional
#endif
#else
#define stdoptional std::optional
#endif
