from structures.arraylist import ArrayList

def fill(val, len):
    res = ArrayList()
    for i in range(len):
        res.push(val)
    return res

def split(string, seq):
    res = ArrayList()
    seq_len = len(seq)

    marker = 0
    l = 0
    r = seq_len - 1

    while r < len(string):
        if seq == string[l:r + 1]:
            res.push(string[marker:l])
            l += seq_len
            r += seq_len
            marker = r
        else:
            l += 1
            r += 1

    res.push(string[marker:r])

    return res


def parseHeader(header):
    header = split(header, " ")
    header[-1] = header[-1][0]
    return header

def parseData(data):
    pretty_matrix = ArrayList()

    shitty_matrix = split(data, "\n")

    for i in range(len(shitty_matrix)):
        pretty_matrix.push(split(shitty_matrix[i], " "))

    # конвертируем значения матрицы в целые числа
    for i in range(len(pretty_matrix)):
        for j in range(len(pretty_matrix[i])):
            pretty_matrix[i][j] = int(pretty_matrix[i][j])

    return pretty_matrix
