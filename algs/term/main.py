from tools import tools
from structures.graph import Graph
from structures.hashmap import Hashmap

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

path, path_len = graph.Kruskal()
print(path)
print(path_len)