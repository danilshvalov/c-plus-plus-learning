#include "test_runner.h"
#include "../date.h"

#include <iostream>

void testOperators() {
    {
        Date lhs{ 2015, 05, 05 };
        Date rhs{ 2016, 05, 05 };
        ASSERT((lhs < rhs));
    }

    {
        Date lhs{ 2015, 05, 05 };
        Date rhs{ 2015, 06, 05 };
        ASSERT((lhs < rhs));
    }

    {
        Date lhs{ 2015, 05, 05 };
        Date rhs{ 2015, 05, 06 };
        ASSERT((lhs < rhs));
    }

    {
        Date lhs{ 2016, 05, 05 };
        Date rhs{ 2015, 05, 05 };
        ASSERT((lhs > rhs));
    }

    {
        Date lhs{ 2015, 06, 05 };
        Date rhs{ 2015, 05, 05 };
        ASSERT((lhs > rhs));
    }

    {
        Date lhs{ 2015, 05, 06 };
        Date rhs{ 2015, 05, 05 };
        ASSERT((lhs > rhs));
    }

    {
        Date lhs{ 2015, 05, 05 };
        Date rhs{ 2015, 05, 05 };
        ASSERT((lhs == rhs));
    }
}