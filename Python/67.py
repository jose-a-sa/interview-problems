from copy import deepcopy


def apply(f):
    return lambda x: f(*x)


class Graph:
    def __init__(self, vert):
        self.V = len(vert)
        self.vertices = vert
        self.vertices_index = dict(zip(vert, range(self.V)))
        self.adj = [[] for i in range(self.V)]

    def DFSUtil(self, temp, v, iv, visited):
        visited[iv] = True
        temp.append(v)
        for i in self.adj[iv]:
            w = self.vertices[i]
            if not visited[i]:
                temp = self.DFSUtil(temp, w, i, visited)
        return temp

    def addEdge(self, v, w):
        iv, iw = map(self.vertices_index.get, (v, w))
        self.adj[iv].append(iw)

    def connectedComponents(self):
        visited = [False for _ in range(self.V)]
        cc = []
        for v, iv in self.vertices_index.items():
            if not visited[iv]:
                temp = []
                cc.append(self.DFSUtil(temp, v, iv, visited))
        return cc


def main():
    m = 100
    vert = []
    trig_og = [[0 for i in range(m+1)] for j in range(m+1)]

    f = open("projecteuler/p067_triangle.txt")
    try:
        for i, line in enumerate(f.readlines()):
            for j, v in enumerate(line.split()):
                trig_og[i][j] = int(v)
                vert.append((i, j))
    finally:
        f.close()

    trig = deepcopy(trig_og)
    g = Graph(vert)

    for i in reversed(range(m)):
        for j in range(i):
            j_sel = j if trig[i][j] > trig[i][j+1] else j+1
            trig[i-1][j] += trig[i][j_sel]
            g.addEdge((i-1, j), (i, j_sel))

    print(list(map(len, g.connectedComponents())))
    max_path = sorted(max(g.connectedComponents(), key=len))
    numbers = list(map(apply(lambda i, j: trig_og[i][j]), max_path))
    print(max_path)
    print(numbers)
    print(trig[0][0], sum(numbers))


if __name__ == "__main__":
    main()
