import functools as ft
import itertools as it
import math as m


def lcm(a, b):
    return abs(a*b) // m.gcd(a, b)


def min_coins(cents, coins):
    coins.add(1)

    cutoff = ft.reduce(lcm, coins)
    n_t = (cents // cutoff) * (cutoff // max(coins))
    cents %= cutoff

    dp = [0]
    for i in range(1, cents+1):
        dp.append(min([dp[i-c]+1 for c in coins if i >= c]))
    #print(dp)
    return dp[cents]+n_t


def min_coins_hash(cents, coins):
    coins.add(1)

    cutoff = ft.reduce(lcm, coins)
    n_t = (cents // cutoff) * (cutoff // max(coins))
    cents %= cutoff

    dp = {0: []}
    for i in range(1, cents+1):
        dp[i] = min([[*dp[i-c], c] for c in coins if i-c in dp], key=len)

    # for k, v in dp.items():
    #     print(f'{k}: {v}')
    return dp[cents] + [max(coins)]*n_t


if __name__ == '__main__':
    coins = {1, 15, 25}
    print(min_coins(74, coins))
    print(min_coins_hash(74, coins))
