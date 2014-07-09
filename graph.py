#!/usr/bin/python


class Vertex():
    def __init__(self, identifier):
        self.identifier = identifier
        self.out = list()
        self.inn = list()

    def __str__(self):
        return self.identifier

    def out_as_str(self):
        return ', '.join([str(e.dest.identifier) for e in self.out])

    def in_as_str(self):
        return ', '.join([str(e.source.identifier) for e in self.inn])


class Edge():
    def __init__(self, source, dest, cost=0):
        self.source = source
        self.dest = dest
        self.cost = cost


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


def main():
    g = Graph.from_file('graph.txt', directed=False)
    print g.as_str()


if __name__ == "__main__":
    main()
