#pragma once

#include <vector>
#include <string>
#include "token.h"

std::vector<Token*> parse(const std::string& expression);
