import sys
input = sys.stdin.readline
n, s = map(int, input().split())
arr = list(map(int, input().split()))

pref = [0] * (n + 1)
for i in range(1, n + 1):
    pref[i] = pref[i - 1] + arr[i - 1]

from collections import defaultdict

prefix_count = defaultdict(int)
prefix_count[0] = 1
# ends[i] = number of good subarrays ending at index i
ends = [0] * n 
for i in range(n):
    ends[i] = prefix_count[pref[i + 1] - s]
    prefix_count[pref[i + 1]] += 1

suffix_count = defaultdict(int)
suffix_count[pref[n]] = 1
# after[i] = number of good subarrays after index i
after = [0] * (n + 1)
for i in range(n - 1, -1, -1):
    after[i] = after[i + 1] + suffix_count[pref[i] + s]
    suffix_count[pref[i]] += 1

ans = 0
for i in range(n - 1):
    ans += ends[i] * after[i + 1]

print(ans)