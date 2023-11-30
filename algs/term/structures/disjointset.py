class DisjointSet:

    def __init__(self):
        self.parent = {}
        self.rank = {}

    def create(self, node):
        self.parent[node] = node
        self.rank = 0

    def find(self, node):
        if node != self.parent[node]:
            self.parent[node] = self.find(self.parent[node])

    def union(self, node_1, node_2):
        parent_1 = self.find(node_1)
        parent_2 = self.find(node_2)

        if parent_1 != parent_2:
            if self.rank[parent_1] > self.rank[parent_2]:
                parent_1, parent_2 = parent_2, parent_1
            self.parent[parent_2] = parent_1
            if self.rank[parent_2] == self.rank[parent_1]:
                self.rank[parent_1] += 1
