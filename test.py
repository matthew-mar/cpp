arr = [12, 130926, 3941054950, 2013898548, 197852696, 2753287507]

arr.sort()

print(arr)

s = 0
for i in range(0, len(arr)):
    s = s + arr[i] * (i + 1)
    print(arr[i], s)
print(s)
