#pragma once

#include "../json/json.h"
#include "Expression.h"

namespace Test {
	using std::string;
	using std::istringstream;
	using std::ostream;
	using namespace Expression;
	using namespace Json;

	string single_test(string);

	void run_tests(ostream& out, JsonObject*);
};