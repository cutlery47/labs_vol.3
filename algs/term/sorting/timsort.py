import random

def getMinrun(arr):
    """ Calculating size of the smallest sub-array """

    n = len(arr)
    r = 0
    while n >= 64:
        # as we are doing bit shift to the right -- we calculate the amount of
        # 1's on the 0-th bit of a binary n representation on each iteration
        # no clue why we do that but anyways...
        r = r | (n & 1)
        n //= 2
    return n + r

def binaryInsertionSort(arr: list):
    """ Sorting sub-arrays (used when adjusting runs) """

    if len(arr) <= 1:
        return arr

    # using binary search to find insertion index
    for i in range(1, len(arr)):
        index = binarySearch(arr, 0, i - 1, arr[i])
        arr = arr[:index] + [arr[i]] + arr[index:i] + arr[i + 1:]

    return arr


def binarySearch(arr, l, r, key):
    """ Meh """

    if l == r:
        if arr[l] > key:
            return l
        else:
            return l + 1
    elif l > r:
        return l
    else:
        m = (l + r) // 2
        if arr[m] > key:
            return binarySearch(arr, l, m - 1, key)
        elif arr[m] < key:
            return binarySearch(arr, m + 1, r, key)
        else:
            return m


def reverse(arr: list):
    """ Busta Nutt"""

    for i in range(0, len(arr) // 2):
        arr[i], arr[len(arr) - i - 1] = arr[len(arr) - i - 1], arr[i]


def merge(left: list, right: list) -> list:
    """ Merging two given sub-arrays """

    l = 0
    r = 0
    res = []

    while l < len(left) and r < len(right):
            if l < len(left) and left[l] < right[r]:
                res.append(left[l])
                l += 1
            else:
                res.append(right[r])
                r += 1

    if r == len(right):
        res += left[l:]
    else:
        res += right[r:]

    return res

def mergeSort(arr: list) -> list:
    """ Sorting by dividing current array on sub-arrays (then merging) """

    if len(arr) == 1:
        return arr

    left = mergeSort(arr[:len(arr) // 2])
    right = mergeSort(arr[len(arr) // 2:])
    return merge(left, right)

def timsort(arr: list) -> list:
    """ The man himself """

    minrun = getMinrun(arr)

    # array for returning the result
    res = []

    # "stack" for merging arrays
    stack = []

    # storage for runs
    runs = []

    # array for storing current run
    run = []

    # dividing input array on runs
    i = 0
    while i <= len(arr):
        # by default, the first pair of elements is pushed
        # simply because two random elements are always arranged in some orde
        if len(run) < 2:
            run.append(arr[i])
            i += 1
            continue

        # current run ordering storage
        order = run[-1] - run[-2]

        # if current element ruins ordering - end current run
        if i >= len(arr) or (arr[i] >= run[-1] and order < 0) or (arr[i] < run[-1] and order >= 0):
            if len(run) < minrun:
                # if current run len is less than minrun -- fill current run till len == minrun
                if i + minrun < len(arr):
                    run += arr[i:i + minrun]
                else:
                    run += arr[i:len(arr)]
                # hence gotta sort the shie
                run = binaryInsertionSort(run)
                i += minrun
            elif len(run) >= minrun and order < 0:
                # if all good but the ordering was reversed -- reverse current run
                reverse(run)

            runs.append(run.copy())
            run = []

            if i != len(arr):
                i -= 1
        else:
            run.append(arr[i])

        i += 1

    while len(runs) > 0:
        if len(runs) == 1:
            res = runs.pop()
        elif len(runs) == 2:
            res = merge(runs.pop(), runs.pop())
        else:
            x = runs.pop()
            y = runs.pop()
            z = runs.pop()

            if not (len(x) > len(y) + len(z)) or not (len(y) > len(z)):
                if len(x) >= len(z):
                    z = merge(z, y)
                else:
                    x = merge(x, y)

                runs.append(z)
                runs.append(x)
            else:
                runs.append(z)
                runs.append(y)
                runs.append(x)

    return res

a = []
for i in range(1000):
    a.append(random.randint(0, 13210))
print(timsort(a))
