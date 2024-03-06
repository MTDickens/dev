#include <iostream>
#include <iomanip>
#include <sstream>

float n_prec_mult(float x1, float x2, int prec)
{
    std::stringstream ss;
    float ret_val;
    ss << std::setprecision(prec) << x1 * x2;
    ss >> ret_val;
    return ret_val;
}

int main() 
{
    constexpr int prec = 8;
    std::cout << std::setprecision(prec + 3) << n_prec_mult(1.114, 1.919, prec) << ' ' << std::setprecision(prec + 3) << 1.114 * 1.919;
    return 0;
}