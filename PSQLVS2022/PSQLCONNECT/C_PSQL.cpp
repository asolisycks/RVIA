
#include "C_PSQL.hpp"

#define CU_VERSION_B2022 "CU-20230107_B22"

C_PSQL::C_PSQL()
{
}

C_PSQL::~C_PSQL()
{
}

std::string C_PSQL::getVersion()
{
	return CU_VERSION_B2022;
}
