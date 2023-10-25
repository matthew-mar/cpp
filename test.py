n, m = map(int, input().split())

nums = list(map(int, input().split()))

for _ in range(m):
    query = input().split()
    if query[0] == "del":
        del nums[int(query[1]) - 1]
    elif query[0] == "add":
        nums.insert(int(query[1]), int(query[2]))
        print(nums)

print(len(nums))
print(*nums)
