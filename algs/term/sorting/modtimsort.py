from structures.arraylist import ArrayList

def getMinrun(arr: ArrayList):
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

def binarySearch(arr:ArrayList, l, r, val, key):
    """ Meh """

    if l == r:
        if arr[l][key] > val:
            return l
        else:
            return l + 1
    elif l > r:
        return l
    else:
        m = (l + r) // 2
        if arr[m][key] > val:
            return binarySearch(arr, l, m - 1, val, key)
        elif arr[m][key] < val:
            return binarySearch(arr, m + 1, r, val, key)
        else:
            return m

def binaryInsertionSort(arr: ArrayList, key):
    """ Sorting sub-arrays (used when adjusting runs) """

    if len(arr) <= 1:
        return arr

    for i in range(1, len(arr)):
        index = binarySearch(arr, 0, i - 1, arr[i][key], key)
        if index != i:
            arr.insert(index, arr[i])
            arr.remove(i + 1)

    return arr

def reverse(arr: ArrayList):
    """ Busta Nutt"""

    for i in range(0, len(arr) // 2):
        arr[i], arr[len(arr) - i -1] = arr[len(arr) - i - 1], arr[i]

def merge(left: ArrayList, right: ArrayList, key) -> ArrayList:
    """ Merging two given sub-arrays """

    l = 0
    r = 0
    res = ArrayList()

    while l < len(left) and r < len(right):
            if l < len(left) and left[l][key] < right[r][key]:
                res.push(left[l])
                l += 1
            else:
                res.push(right[r])
                r += 1

    if r == len(right):
        while l < len(left):
            res.push(left[l])
            l += 1
    else:
        while r < len(right):
            res.push(right[r])
            r += 1

    return res

def mergeSort(arr: ArrayList, key) -> ArrayList:
    """ Sorting by dividing current array on sub-arrays (then merging) """

    if len(arr) == 1:
        return arr

    left = mergeSort(arr[:len(arr) // 2], key)
    right = mergeSort(arr[len(arr) // 2:], key)
    return merge(left, right, key)

def modtimsort(arr: ArrayList, key) -> ArrayList:
    """ The man himself """

    minrun = getMinrun(arr)

    res = ArrayList()

    runs = ArrayList()

    run = ArrayList()

    i = 0
    while i <= len(arr):
        if len(run) < 2:
            run.push(arr[i])
            i += 1
            continue

        order = run[-1][key] - run[-2][key]

        if i >= len(arr) or (arr[i][key] >= run[-1][key] and order < 0) or (arr[i][key] < run[-1][key] and order >= 0):
            if len(run) < minrun:
                # if current run len is less than minrun -- fill current run till len == minrun
                if i + minrun < len(arr):
                    for j in range(i, i + minrun):
                        run.push(arr[j])
                else:
                    for j in range(i, len(arr)):
                        run.push(arr[j])
                # hence gotta sort the shie
                run = binaryInsertionSort(run, key)
                i += minrun
            elif len(run) >= minrun and order < 0:
                # if all good but the ordering was reversed -- reverse current run
                reverse(run)

            runs.push(ArrayList(run)[0])
            run = ArrayList()

            if i != len(arr):
                i -= 1
        else:
            run.push(arr[i])

        i += 1

        while len(runs) > 0:
            if len(runs) == 1:
                res = runs.pop()
            elif len(runs) == 2:
                res = merge(runs.pop(), runs.pop(), key)
            else:
                x = runs.pop()
                y = runs.pop()
                z = runs.pop()

                if not (len(x) > len(y) + len(z)) or not (len(y) > len(z)):
                    if len(x) >= len(z):
                        z = merge(z, y, key)
                    else:
                        x = merge(x, y, key)

                    runs.push(z)
                    runs.push(x)
                else:
                    runs.push(z)
                    runs.push(y)
                    runs.push(x)

    return res

