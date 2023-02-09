a = [1, 1, 0, 0, 1, 0, 1, 0]


def int_to_bin_array(x):
    return [int(d) for d in str(bin(x))[2:]]


def count_bits(n):
    cnt_set, cnt_total = 0, 0
    while n:
        cnt_total += 1
        cnt_set += n & 1
        n >>= 1
    return cnt_total - cnt_set, cnt_set


def count_flips3(n):
    count = 0
    while n:
        c0, c1 = count_bits(n)
        count += c0
        n &= 2**(c0+c1-1) - 1
    return count


def count_flips4(n):
    if n == 0: return 0
    
    if n % 2 == 0:
        return count_flips4(n//2) + count_bits(n//2)[1]
    else:
        return count_flips4((n-1)//2) + 1


def count_flips2(lst):
    _lst = lst.copy()
    c = 0
    while len(_lst) > 1:
        if _lst.pop(0) == 1:
            c += len(_lst) - sum(_lst)
    return c


def count_flips(lst):
    _lst = lst
    n = len(_lst)
    c = 0
    i = 0
    while i < n-1:
        if (_lst[i], _lst[i+1]) == (1, 0):
            _lst[i], _lst[i+1] = 0, 1
            c += 1
            i = i-1 if i > 0 else 0
        else:
            i += 1
    return c


for i in range(1, 1001):
    print(count_flips3(i), count_flips4(i) - count_bits(i)[1])
print()
