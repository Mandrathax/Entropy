#ifndef GEN_H
#define GEN_H

#include "Storing/store.h"
#include <iostream>
#include <algorithm>

void add_next_char(string& text, Store& s, int order);

string generate_text(Store& s, int target_length, int order);

#endif
