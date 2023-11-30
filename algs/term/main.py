from tools import tools
from structures.graph import Graph

# текстовый файл состоит из двух частей
# первая - перечисление вершин
# вторая - матрица смежности
f = open("tests/data.txt", "r")
header = f.readline()
data = f.read()

# парсинг с файла
edges = tools.parseHeader(header)
adjacency_matrix = tools.parseData(data)

graph = Graph(adjacency_matrix, edges)

print(graph.list)
print(graph.incident)

print("bfs")
graph.dfs(0)

print("bfs")
graph.dfs(1)

print("dfs")
graph.bfs(0)