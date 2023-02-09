
# STATES
# 0: (000)
# 1: (100)
# 2: (010)
# 3: (110)
# 4: (001)
# 5: (101)
# 6: (011)
# 7: (111)

def tritiling(n):
    dp = [[0 for j in range(8)] for i in range(n+1)]
    dp[0][7] = 1
    i = 1
    while i <= n:
        dp[i][0] = dp[i-1][7]
        dp[i][1] = dp[i-1][6]
        #dp[i][2] = dp[i-1][5]
        dp[i][3] = dp[i-1][4] + dp[i-1][7]
        dp[i][4] = dp[i-1][3]
        #dp[i][5] = dp[i-1][2]
        dp[i][6] = dp[i-1][1] + dp[i-1][7]
        dp[i][7] = dp[i-1][0] + dp[i-1][3] + dp[i-1][6]
        i += 1
    return dp


# STATES
# 0: (00)
# 1: (10)
# 2: (01)
# 3: (11)


def duotiling(n):
    dp = [[0 for j in range(4)] for i in range(n+1)]
    dp[0][3] = 1
    i = 1
    while i <= n:
        dp[i][0] = dp[i-1][3]
        #dp[i][1] = dp[i-1][2]
        #dp[i][2] = dp[i-1][1]
        dp[i][3] = dp[i-1][0] + dp[i-1][3]
        i += 1
    return dp
