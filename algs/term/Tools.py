def parseHeader(header):
    header = header.split("  ")
    header[-1] = header[-1][0]
    return header

def parseData(data):
    shitty_matrix = data.split("\n")
    pretty_matrix = []

    for i, el in enumerate(shitty_matrix):
        pretty_matrix.append(shitty_matrix[i].split("  "))

    for i in range(len(pretty_matrix)):
        for j in range(len(pretty_matrix[0])):
            pretty_matrix[i][j] = int(pretty_matrix[i][j])

    return pretty_matrix

def findMinEdge(matrix):
    mn = float('inf')
    vertex_1 = -1
    vertex_2 = -1

    for i in range(0, len(matrix)):
        for j in range(i, len(matrix)):
            if matrix[i][j] < mn and (matrix[i][j] != 0 and matrix[i][j] != -1):
                mn = matrix[i][j]
                vertex_1 = j
                vertex_2 = i

    return mn, vertex_1, vertex_2
