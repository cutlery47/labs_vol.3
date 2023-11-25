from tools import tools

class Graph:
    def __init__(self, matrix=None, vertices=None):
        # матрица смежности и матрица с вершинами
        self.matrix = matrix
        self.vertices = vertices

        self.list = self.fromAdjToList()
        self.incident = self.fromAdjToIncident()

    # преобразование матрицы смежности в список смежности
    def fromAdjToList(self):
        adj_list = {}
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                if self.matrix[i][j] != 0:
                    adj_list[self.vertices[i]] = adj_list.get(self.vertices[i], "") + str(self.vertices[j]) + ":" + str(self.matrix[i][j]) + " "

        return adj_list

    # преобразование матрицы смежности в матрицу инцидентности
    def fromAdjToIncident(self):
        incid = [[0 for i in range(len(self.vertices))]]
        edge = 0

        for i in range(len(self.matrix)):
            for j in range(i, len(self.matrix[i])):
                if self.matrix[i][j] != 0:
                    incid.append([0 for i in range(len(self.vertices))])
                    incid[edge][j] = self.matrix[i][j]
                    edge += 1

        return incid[:-1]


    def Kruskal(self):
        # число вершин, котрые нужно пройти (все вершины)
        # копия матрицы, чтобы не засирать оригинал
        target = len(self.vertices)
        tmp_matrix = self.matrix.copy()

        # счетчик посещенных верщин
        # множество посещенных вершин, чтобы проверять, что ребро образует зацикленность
        num_visited = 1
        visited = set()

        # матрица для хранения маршрута
        # переменная для хранения длины маршрута
        path = []
        path_len = 0

        # пока не пройдем все вершины
        while num_visited < target:
            edge_found = False
            # длина минимального ребра
            min_len = 0
            # координаты минимального ребра в матрице смежности
            min_j = -1
            min_i = -1

            # пока не найдем минимальное хорошее ребро (не образующее зацикленность)
            while not edge_found:
                # находим претендента на минимальное ребро
                (min_len, min_j, min_i) = tools.findMinEdge(tmp_matrix)

                i_visited = self.vertices[min_i] in visited
                j_visited = self.vertices[min_j] in visited

                # если образуется цикл (смежные вершины посещены) - ищем заново
                if i_visited and j_visited:
                    tmp_matrix[min_i][min_j] = -1
                else:
                    # иначе все круто
                    edge_found = True

                    tmp_matrix[min_i][min_j] = -1

                    # добавляем смежные вершины в множество вершин
                    if not i_visited:
                        visited.add(self.vertices[min_i])

                    if not j_visited:
                        visited.add(self.vertices[min_j])

            # прибавляем длину пути и добавляем ребро
            num_visited += 1
            path_len += min_len
            path.append(self.vertices[min_i] + self.vertices[min_j])

        print(*path)
        print(path_len)

    # обход в глубину по матрице смежности (рекурсивно)
    # входные данные: текущая вершина, массив посещенных вершин
    def dfs(self, curr, visited=None):
        # массив для проверки посещенности вершин
        if not visited:
            visited = [False] * len(self.vertices)

        # помечаем текущую вершину
        visited[curr] = True

        print(self.vertices[curr])

        # проходимся по всем смежным вершинам для текущей вершины
        for i in range(len(self.vertices)):
            if self.matrix[curr][i] != 0 and not visited[i]:
                self.dfs(i, visited)

    # обход в щирину по матрице смежности
    def bfs(self, curr):
        # массив для проверки посещенности вершин
        visited = [False] * len(self.vertices)

        # очередь для хранения вершин
        q = [curr]

        # помечаем посещенную вершину
        visited[curr] = True

        # пока есть элементы в очереди
        while q:
            vis = q[0]
            q.pop(0)

            print(self.vertices[vis])

            for i in range(len(self.vertices)):
                if self.matrix[vis][i] != 0 and not visited[i]:
                    # добавляем в очередь всех соседей текущей вершины
                    q.append(i)
                    visited[i] = True



