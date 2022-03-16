#include <iomanip>
#include <sstream>

double pi = 3.14159265359;
std::stringstream s;
s << std::fixed << std::setprecision(2) << pi;
std::string s = s.str();
