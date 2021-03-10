class Vertex:
    __slots__ = '_element'

    def __init__(self, x):
        self._element = x

    def element(self):
        return self._element

    def __hash__(self):
        return hash(id(self))


class Edge:
    slots = '_origin', '_destination', '_element'

    def __init__(self, u, v, x):
        self._origin = u
        self._destination = v
        self._element = x
        self.visited = False

    def endpoints(self):
        return (self._origin, self._destination)

    def opposite(self, v):
        return self._destination if v is self._origin else self._origin

    def element(self):
        return self._element

    def __hash__(self):
        return hash((self._origin, self._destination))

    def is_visisted(self):
        self.visited

    def visit(self):
        self.visited = True

    def __str__(self):
        return f'{self._origin}-{self._destination}'


class Graph:
    def __init__(self, directed=False):
        self._outgoing = {}
        self._incoming = {} if directed else self._outgoing

    def is_directed(self):
        return self._incoming is not self._outgoing

    def vertex_count(self):
        return len(self._outgoing)

    def vertices(self):
        return self._outgoing.keys()

    def edge_count(self):
        total = sum(len(self._outgoing[v]) for v in self._outgoing)

        return total if self.is_directed() else total // 2

    def edges(self):
        result = set()
        for m in self._outgoing.values():
            result.update(m.values())
        return result

    def get_edge(self, u, v):
        return self._outgoing[u].get(v)

    def degree(self, v, outgoing=True):
        adj = self._outgoing if outgoing else self._incoming
        return len(adj[v])

    def incident_edges(self, v, outgoing=True):
        adj = self._outgoing if outgoing else self._incoming
        print('adjacent', adj)
        for edge in adj[v].values():
            yield edge

    def insert_vertex(self, x=None):
        v = Vertex(x)
        self._outgoing[v] = {}
        if self.is_directed():
            self._incoming[v] = {}
        return v

    def insert_edge(self, u, v, x=None):
        e = Edge(u, v, x)
        print('')
        print('Outgoing', self._outgoing)
        self._outgoing[u][v] = e
        self._incoming[v][u] = e


G = Graph(False)
v1 = G.insert_vertex(1)
v2 = G.insert_vertex(2)
G.insert_edge(v1, v2)


def depth_first_search(G, u):
    print(G.incident_edges(u))
    for e in G.incident_edges(u):
        print(e.endpoints())


depth_first_search(G, 4)


# class UndirectedGraph(Graph):
#     def __init__(self, vertices, edges):
#         super().__init__(vertices, edges)

#     def get_edge(self, u, v):
#         if (u, v) in self.edges or (v, u) in self.edges:
#             return (u, v)
#         return None

#     def degree(self, v):
#         degree = 0
#         for vertex in self.vertices:
#             if self.get_edge(v, vertex):
#                 degree += 1
#         return degree


# G = UndirectedGraph((1, 2, 3, 4, 5), [(1, 2), (2, 3), (3, 4), (4, 5)])
# assert G.get_edge((2, 3)) == (2, 3)
# assert G.degree(2) == 2


# def breadth_first_search(g, s, discovered):
#     level = [s]
#     while len(level) > 0:
#         next_level = []
#         for u in level:
#             # For every outgoing edge from u
#             for e in g.incident_edges(u):

#                 v = e.opposite(u)
#                 if v not in discovered:
#                     discovered[v] = e
#                     next_level.append(v)
#         level = next_level
