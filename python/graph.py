class Vertex:
    def __init__(self, value):
        self.value = value

    def element(self):
        return self.value

class Edge:
    def __init__(self, u: Vertex, v: Vertex):
        self.edge = (u, v)
        
    def element(self):
        return self.edge
    
    def endpoints(self):
        return self.edge

    def opposite(self, v):
        if self.edge[0] is v:
            return self.edge[1]
        else:
            return self.edge[0]
 
class Graph:
    def __init__(self, vertices, edges):
        self.vertices = vertices
        self.edges = edges

    def vertex_count():
        return len(self.vertices)

    def vertices():
        return self.vertices

    def edge_count():
        return len(self.edges)

    def edges():
        return self.edges

class UndirectedGraph(Graph):
    def __init__(self, vertices, edges):
        super().__init__(vertices, edges)

    def get_edge(self, u, v):
        if (u,v) in self.edges or (v,u) in self.edges:
            return (u,v)
        return None

    def degree(self, v):
        degree = 0
        for vertex in self.vertices:
            if self.get_edge(v, vertex): 
                degree += 1
        return degree
            
    
G = UndirectedGraph((1,2,3,4,5), [(1,2), (2,3), (3,4), (4,5)])
assert G.get_edge((2,3)) == (2,3)
assert G.degree(2) == 2