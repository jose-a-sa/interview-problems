# import itertools as it

# x = [ 1, 4, 9, 16 ]
# s = []
# n = 100
# #Remove elements >9
# x = [ i for i in x if i <= n]

# for i in range(1, n + 1):
#     for j in it.product(x,repeat = i):
#         if sum(j) == n:
#             s.append(list(j))

# #Sort each combo
# s =[sorted(i) for i in s]
# #group by unique combo
# print( list(k for k,_ in it.groupby(s)) )


from abc import abstractproperty


def partition_nr_into_given_set_of_nrs(nr, S):
    def _iterator(n, nrs):
        print((n, nrs))
        if n == 0:
            yield []
        for k, v in enumerate(nrs):
            if v <= n:
                for rest in _iterator(n - v, nrs[k:]):
                    yield [v, *rest]
    return list(_iterator(nr, sorted(S, reverse=True)))


def partition(nr, S):
    nrs = sorted(S, reverse=True)

    def _iterator(n, i=0, memo=dict()):
        if (n, i) in memo.keys():
            return memo[(n, i)]
        if n == 0:
            return []
        lst = []
        for k in range(i, len(nrs)):
            if nrs[k] <= n:
                for rest in _iterator(n - nrs[k], k):
                    lst.append([nrs[k], *rest])
        memo[(n, i)] = lst
        return lst
    return _iterator(nr)


S = [1, 4, 9, 16]
nrs = sorted(S, reverse=True)
print(partition(9, S))
