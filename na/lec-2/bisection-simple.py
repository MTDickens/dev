def it(a,b,n,f):
    mid = a + (b-a)/2
    if n == 0:
            return mid
    else:
            mid_val = f(mid)
            if mid_val == 0: return mid
            elif mid_val > 0: return it(a, mid, n-1,f)
            else: return it(mid,b,n-1,f)

if __name__ == "__main__":
    f = lambda x: x**3 - x - 1
    # f(1,2, 13, f) with print precision of 4
    print(it(1,2, 13, f))