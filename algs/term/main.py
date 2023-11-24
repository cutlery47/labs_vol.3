import Tools
from Graph import Graph

f = open("data.txt", "r")
header = f.readline()
data = f.read()

edges = Tools.parseHeader(header)
adjacency_matrix = Tools.parseData(data)

graph = Graph(adjacency_matrix, edges)
graph.Kruskal()
