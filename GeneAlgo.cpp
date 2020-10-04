﻿#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include "My_Algorithms.h"

int main()
{
    srand(time(0));
    field f( 32,5,2,[](auto& vec) {
        int x = rand()%32;
        return x;
    }
    );
    field exampl(15, 2);
    for (int i = 0; i < 32; i++) {
        int x = rand() % 32;
        exampl.add_without_rule(f[x].first, f[x].second);
    }
    exampl.print_field();
    auto result = CTH_algo(f, 2,true);
}
