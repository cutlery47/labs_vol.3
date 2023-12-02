from sorting.modtimsort import modtimsort
from structures.disjointset import DisjointSet
from structures.arraylist import ArrayList
from tools import tools

class Graph:
    def __init__(self, matrix=None, vertices=None):
        # матрица смежности и матрица с вершинами
        self.matrix = matrix
        self.vertices = vertices

        self.list = self.fromAdjToList()
        self.incident = self.fromAdjToIncident()

    # преобразование матрицы смежности в список смежности
    def fromAdjToList(self) -> ArrayList:
        edges = ArrayList()
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                if self.matrix[i][j] != 0:
                    edge = ArrayList()
                    edge.push(self.vertices[i])
                    edge.push(self.vertices[j])
                    edge.push(self.matrix[i][j])
                    edges.push(edge)

        return edges

    # преобразование матрицы смежности в матрицу инцидентности
    def fromAdjToIncident(self) -> ArrayList():
        incid = ArrayList(tools.fill(0, len(self.vertices)))

        edge = 0

        for i in range(len(self.matrix)):
            for j in range(i, len(self.matrix[i])):
                if self.matrix[i][j] != 0:
                    incid.push(tools.fill(0, len(self.vertices)))
                    incid[edge][j] = self.matrix[i][j]
                    edge += 1

        return incid[:-1]

    def Kruskal(self):
        # матрица для хранения маршрута
        # переменная для хранения длины маршрута
        path = ArrayList()
        path_len = 0

        # создаем матрицу с отсортированными по весу кортежами ребер (начало, конец, вес)
        edges = modtimsort(self.list, 2)

        set = DisjointSet()

        for edge in edges:
            set.create(edge[0])
            set.create(edge[1])

        for edge in edges:
            if set.rank[edge[0]] == len(self.vertices) - 1 or set.rank[edge[1]] == len(self.vertices) - 1:
                break

            if set.find(edge[0]) != set.find(edge[1]):
                node = ArrayList()
                node.push(edge[0])
                node.push(edge[1])

                path.push(node)

                set.union(edge[0], edge[1])
                path_len += edge[2]

        return (path, path_len)

    # обход в глубину по матрице смежности (рекурсивно)
    # входные данные: текущая вершина, массив посещенных вершин
    def dfs(self, curr, visited=None):
        # массив для проверки посещенности вершин
        if not visited:
            visited = tools.fill(False, len(self.vertices))

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
        visited = tools.fill(False, len(self.vertices))

        # очередь для хранения вершин
        q = ArrayList(curr)

        # помечаем посещенную вершину
        visited[curr] = True

        # пока есть элементы в очереди
        while q:
            vis = q[0]
            q.pop_front()

            print(self.vertices[vis])

            for i in range(len(self.vertices)):
                if self.matrix[vis][i] != 0 and not visited[i]:
                    # добавляем в очередь всех соседей текущей вершины
                    q.push(i)
                    visited[i] = True