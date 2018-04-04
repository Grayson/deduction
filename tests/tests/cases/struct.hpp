//
//  struct.h
//  tests
//
//  Created by Grayson Hansard on 3/10/18.
//  Copyright © 2018 From Concentrate Software. All rights reserved.
//

#include <vector>

struct foo {
	foo() = default;
	foo(int grault) = default;

	int bar;
	double baz(bool quux, void * quuz);
	int const corge;
	std::vector<bool> asdf;

private:
	int grault;

public:
	bool garply();
};
