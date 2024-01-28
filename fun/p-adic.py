from pyadic import PAdic
from fractions import Fraction
import sys

sys.set_int_max_str_digits(10000000)
sys.setrecursionlimit(300000) 

# Parameters

## Desired form:
## polynomial(x) = p^k * n
## where k can be arbitrarily large.

polynomial = [7, 0, 1]  # 7*x^0+0*x^1+1*x^2 = x^2 + 7
p = 2                   

## `x0` represents the initial guess for Newton's method.
## `n` is the number of iterations.
## `digits` is the number of p-adic digits to calculate.

x0 = Fraction(1)
n = 15
digits = 1000

# Newton's Method

def f(x):
    return sum(c * x ** i for i, c in enumerate(polynomial))

def f_prime(x):
    result = 0
    for i, c in enumerate(polynomial):
        if (i == 0):
            continue
        result += c * i * x ** (i - 1)
    return result


def newton_root_finding(f, f_prime, x0, n):
    x = Fraction(x0)
    for i in range(n):
        x -= f(x) / f_prime(x)
        # print(f"Round {i+1:02}", PAdic(x, p, digits).as_tuple)
    return x


root = newton_root_finding(f, f_prime, x0, n)

padic = PAdic(root, p, digits)
# print(f"Original p-adic number: {padic}")
padic_num = padic.num
# print(f"10-based p-adic number: {padic_num}")
result = f(padic_num)

with open("output.txt", "w") as f:
    f.write(str(result))