import Tools

class Graph:

    def __init__(self, matrix=None, vertices=None):
        self.matrix = matrix
        self.vertices = vertices

    def Kruskal(self):
        #
        target = len(self.vertices)
        tmp_matrix = self.matrix.copy()

        #
        num_visited = 1
        visited = set()

        #
        path = []
        path_len = 0

        while num_visited < target:
            edge_found = False
            min_len = 0
            min_j = -1
            min_i = -1

            while not edge_found:
                (min_len, min_j, min_i) = Tools.findMinEdge(tmp_matrix)

                i_visited = self.vertices[min_i] in visited
                j_visited = self.vertices[min_j] in visited

                if i_visited and j_visited:
                    tmp_matrix[min_i][min_j] = -1
                else:
                    edge_found = True

                    tmp_matrix[min_i][min_j] = -1

                    if not i_visited:
                        visited.add(self.vertices[min_i])

                    if not j_visited:
                        visited.add(self.vertices[min_j])

            num_visited += 1
            path_len += min_len
            path.append(self.vertices[min_i] + self.vertices[min_j])

        print(*path)
        print(path_len)


