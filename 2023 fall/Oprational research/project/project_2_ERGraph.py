""" a collection of doubly stochastic matrix for connected graph
please firstly install networkx 3.1.0 by
pip install networkx==3.1.0
"""
import matplotlib.pyplot as plt
import networkx as nx
import numpy as np
# import torch


class Graph:
    """
    Parameters: graph_type = 'ER', default = 'ER'
                weighted_type = 'max_degree' or 'metropolis_hastings'
                N: number of nodes
                plot_g: whether plot the graph
                p: connection probability for ER graph
                max_len: the maximum length of each edge

    Return: a connected ER graph with a weight matrix W for each edge

    """

    def __init__(self, graph_type='ER', weighted_type=None, N=2, plot_g=False, p=0, max_len=1.):
        self.graph_type = graph_type
        self.weighted_type = weighted_type
        self.N = N
        self.max_len = max_len # maximum length of each edge
        self.plot_g = plot_g
        self.G = None
        self.L = None  # Laplacian  matrix
        self.degree = 0  # degree of each node
        self.peer = None  # neighborhood of each node
        self.p = p  # connection probability for ER graph
        if graph_type:
            if self.N == 1:
                self.peer = np.array([0])
            else:
                self.peer = self.build_graph()
            self.W = self.generate_edge_weight()

    def er_graph(self):
        """ Erdos Renyi graph with N nodes, connective probability p"""
        while True:
            self.G = nx.erdos_renyi_graph(self.N, self.p)
            self.L = nx.laplacian_matrix(self.G).toarray()
            _, s, _ = np.linalg.svd(self.L)
            s.sort()
            if s[1] > 0.01:
                print(f'The connected Erdos-Renyi graph is generated. Algebraic Connectivity: {s[1]:.3f}, size of {self.N}')
                break

    def complete(self):
        """ complete graph with N nodes """
        self.G = nx.complete_graph(self.N)
        self.L = nx.laplacian_matrix(self.G).toarray()

    def generate_edge_weight(self):
        A = nx.adjacency_matrix(self.G).todense()
        A = np.array(A)
        weight_matrix = np.where(A == 1, self.max_len*np.random.rand(*A.shape), 0)
        return weight_matrix

    def build_graph(self):
        switcher = {
            'ER': self.er_graph,
            'complete': self.complete
        }
        method = switcher.get(self.graph_type, "Invalid graph")()
        # method()
        if self.plot_g:
            nx.draw(self.G)
            txt = "The" + ' ' + self.graph_type + ' ' + 'graph' + ',' + ' ' + 'n = ' + str(self.N)
            txt += ', p=' + str(self.p) if self.graph_type == 'ER' else ''
            plt.figtext(0.5, 0.01, txt, wrap=True, horizontalalignment='center', fontsize=10)
            import os
            if not os.path.isdir("Graph"):
                os.makedirs("Graph")
            save_path = 'Graph'
            plt.savefig(os.path.join(save_path, self.graph_type + str(self.N) + str(self.p) + '.pdf'), format='pdf',
                        dpi=3000)
            plt.show()

        return self.peer


if __name__ == '__main__':
    """ demo to generate an ER graph with 5 nodes, and maximum length of edge being 10 """
    graph_type = 'ER'  # create an ER graph
    g = Graph(graph_type=graph_type,
              N=5, p=0.5, max_len=10, plot_g=True)
    peer = g.peer  # peer_{ij} = 1 if (i,j) is an edge
    W = g.W  # the weight matrix, W_{ij} is the length of edge (i,j)
    print(f'The graph weights has been created: W =\n  {W}')
