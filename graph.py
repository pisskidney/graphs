#!/usr/bin/python


class Vertex():
    def __init__(self, identifier):
        self.identifier = identifier
        self.out = list()
        self.inn = list()

    @property
    def in_deg(self):
        return len(self.inn)

    @property
    def out_deg(self):
        return len(self.out)

    def __str__(self):
        return self.identifier

    def out_as_str(self):
        return ', '.join([str(e.dest.identifier) for e in self.out])

    def in_as_str(self):
        return ', '.join([str(e.source.identifier) for e in self.inn])

    def __eq__(self, v):
        return self.identifier == v.identifier

    def __hash__(self):
        return hash(self.identifier)


class Edge():
    def __init__(self, source, dest, weight=0):
        self.source = source
        self.dest = dest
        self.weight = weight

    def __eq__(self, edge):
        return (
            self.source == edge.source and
            self.dest == edge.dest
            and self.weight == edge.weight
        )


class Graph():
    def __init__(self, directed=False):
        self.directed = directed
        self.vertices = dict()

    @classmethod
    def from_file(cls, filename, directed=False):
        ''' If the graph is undirected, it will create a source->dest and
        a dest->source edge for the same edge defining pair.
        '''
        new = cls(directed=directed)
        f = open(filename, 'r')
        nr_vertices = int(f.readline())
        for i in range(1, nr_vertices+1):
            new.vertices[i] = Vertex(i)
        for line in f:
            source, dest = line.split(' ')
            source, dest = int(source), int(dest)
            e = Edge(new.vertices[source], new.vertices[dest])
            new.vertices[source].out.append(e)
            new.vertices[dest].inn.append(e)
            if not directed:
                e2 = Edge(new.vertices[dest], new.vertices[source])
                new.vertices[dest].out.append(e2)
                new.vertices[source].inn.append(e2)
        return new

    def as_str(self, redundancy=True):
        ''' The redundancy param dictates if we need to print both the in and
        out going edges in an undirected graph.
        '''
        output = ''
        for k, v in self.vertices.iteritems():
            output += '\n(%s)\n' % str(k)
            output += 'out: %s\n' % v.out_as_str()
            if redundancy or self.directed:
                output += 'in: %s\n' % v.in_as_str()
        return output

    def get_edge(self, v1, v2):
        e = Edge(v1, v2)
        for edge in self.vertices[v1.identifier].out:
            if edge == e:
                return edge
        return None


def main():
    g = Graph.from_file('graph.txt', directed=False)
    print g.as_str()
    print bool(g.get_edge(Vertex(2), Vertex(1)))
    print g.vertices[2].in_deg


if __name__ == "__main__":
    main()
