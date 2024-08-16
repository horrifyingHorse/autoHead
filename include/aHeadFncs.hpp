#ifndef AHEADFNCS_HPP
#define AHEADFNCS_HPP

#include "aHeadClass.hpp"

int autoHead();

int ahProcess_exit(const UsrCmd &);

void populateCliCmdMap();

int execute(UsrCmd &);

#endif // !AHEADFNCS_HPP
