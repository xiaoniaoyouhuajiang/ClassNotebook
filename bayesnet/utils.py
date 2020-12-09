# -*- coding: utf-8 -*-
"""
Created on Thu Nov 12 15:19:23 2020

@author: pp
"""


import re
import itertools
import random
import numpy as np
import pandas as pd

from abc import abstractmethod
from collections import OrderedDict as odict
from collections import defaultdict
from itertools import product
from graphviz import Digraph, Graph
from tabulate import tabulate
from copy import deepcopy

import matplotlib.pyplot as plt
import matplotlib as mpl

import sys, time

class GraphBase:
    #默认使用一个字典嵌套数组的结构存储图
    #推测存储的方式是链接表
    def __init__(self, graph = defaultdict(list)):
        self.graph = graph
        
    def __getitem__(self, key):
        return self.graph[key]
    
    def __iter__(self):
        return iter(self.graph)
    
    def __len__(self):
        return self.graph.__len__()
    
    def keys(self):
        return self.graph.keys()
    
    def items(self):
        return self.graph.items()
    
    #插入的时候由于使用的数据结构是collection内的字典，所以尽管原先并不存在这样的键值，还是能够直接插入
    def insert_node(self, node):
        self.graph[node] = []
        
        
    def remove_nodes(self, nodes:set = set()):
        '''
        

        Parameters
        ----------
        nodes : set, optional
            a set of nodes. The default is set().

        Returns
        -------
        children of ...

        '''
        #delete nodes
        G = self.graph
        children = defaultdict(list)
        
        for n in nodes:
            children[n] = G[n]
            del G[n]
            
        #把链接表里的也删除            
        for n in nodes:
            for i in G:
                if n in G[i]:
                    G[i].remove(n)
        return children
    
    def remove_node(self, node):
        return self.remove_nodes(set([node]))
    
    def pop(self, key):
        return self.remove_node(self, key)
    
    def __delitem__(self, key):
        self.remove_node(key)
        
    @abstractmethod
    def connect_edge(self, node1, node2):
        #因为是abstract，所以自然不需要实现
        pass
    
    def disconnect_edge(self, node1, node2):
        #该函数的功能与上一个函数相反
        pass
    

#下面实现一个具体的，而且我们需要的贝网原型：DAG
class DAG(GraphBase):
    
    def __init__(self, graph = defaultdict(list)):
        super(DAG, self).__init__(graph)
        
    def __setitem__(self, key,value):
        self.graph[key] = value
        return self
    
    def display_graph(self):
        #得做一个方法把图的内容可视化
        g = self.graph
        dot = Digraph(engine="dot")
        for v in g.keys():
            dot.node(v)
        for v in g.keys():
            for w in g[v]:
                dot.edge(v, w)
        return dot
    
    def children(self, v):
        return self.graph[v]
    
    def _transpose_graph(self):
        G = self.graph
        #GT是存储转置图的东东
        GT = dict((v, []) for v in G)
        for v in G:
            for w in G[v]:
                if w in GT:
                    GT[w].append(v)
                #注意else分支
                else:
                    GT[w] = [v]
        return GT
    
    def transpose_graph(self):
        return DAG(self._transpose_graph())
    
    def generate_parents(self):
        #生成一个转置图属性
        self.reverse_graph = self._transpose_graph()

    #找到父母节点，那显然就是转置的孩子嘛
    def parents(self, v):
        return self.reverse_graph[v]
            
    def __str__(self):
        return self.display_graph().__str__()
    
    def _repr_svg_(self):
        return self.display_graph()._repr_svg_()
    
    def connect_edge(self, node1, node2):
        if node2 not in self.graph[node1]:
            self.graph[node1].append(node2)
    
    def disconnect_edge(self, node1, node2):
        if node2 in self.graph[node1]:
            self.graph[node1].remove(node2)
            
    def find_leaves(self, S:set = set()):
        '''
        

        Parameters
        ----------
        S : set, optional
            找到除了S集合中的所有叶子. The default is set().

        Returns
        -------
        返回叶子.

        '''
        leaves = set()
        
        for v in self.graph:
            if self.graph[v] == [] and v not in S:
                leaves.add(v)
                
        return leaves
    
    def transfor2UndirectedGraph(self):
        ugraph = deepcopy(self.graph)
        for i in self.graph:
            for j in self.graph[i]:
                #因为没方向嘛,so...
                ugraph[j].append(i)
        return UndirectedGraph(graph = ugraph)
    
    
    def _topologicalOrdering_r(self, v, colour, stack):
        colour[v] = 'gray'
        
        for w in self.graph[v]:
            if colour[w] == 'white':
                self._topologicalOrdering_r(w, colour, stack)
        stack.append(v)
        colour[v] = 'black'
        
    def topologicalOrdering(self):
        colour = {node:'white' for node in self.graph.keys()}
        stack = []
        for v in self.graph:
            if colour[v] == 'white':
                #using DFS find topological order
                self._topologicalOrdering_r(v, colour, stack)
        return list(reversed(stack))
    
class UndirectedGraph(GraphBase):
    def __init__(self, graph = defaultdict(list)):
        super(UndirectedGraph, self).__init__(graph)

    def __setitem__(self, key,value):
        '''
        G[(A,B,C)] = [(C,D), (B,H)]
        '''
        self.graph[key] = value
        self.graph[value] = key
        return self
    

    
    def add_fill_in_edges(self, neighbors):
        for i in itertools.combinations(neighbors, 2):
            self.connect_edge(i[0], i[1])
    
    def remove_node_with_added_fill_in_edges(self, v):
        neighbors = self.graph[v]
        self.add_fill_in_edges(neighbors)
        self.remove_node(v)
        
    def neighbors(self, v):
        return self.graph[v]
    
    def degree(self, v):
        return len(self.neighbors(v))
    
    def min_degree_node(self):
        return min(self.graph, key = self.degree)
    
    def display_graph(self):
        g = self.graph
        dot = Graph(engine="dot")
        
        for v in g.keys():
            dot.node(v)
            
        already_display = set()
        for v in g.keys():
            already_display |= set([v])
            for w in g[v]:
                if w not in already_display:
                    dot.edge(v, w)
        return dot  
    
    def __str__(self):
        return self.display_graph().__str__()
    
    def _repr_svg_(self):
        return self.display_graph()._repr_svg_()
    
    def connect_edge(self, node1, node2):
        '''
        add an edge from node1 to node2
        '''
        if node2 not in self.graph[node1]:
            self.graph[node1].append(node2)
            self.graph[node2].append(node1)
    
    def disconnect_edge(self, node1, node2):
        '''
        remove an edge from node1 to node2
        '''
        if node1 in self.graph[node2]:
            self.graph[node1].remove(node2)
            self.graph[node2].remove(node1)
            
class FactorsBase:
    def __init__(self, outcome_space, factors = {}):
        self.outcome_space = outcome_space
        self.factors = factors
    
    def __getitem__(self, key):
        return self.factors[key]
    
    def __setitem__(self, key, value):
        self.factors[key] = value
        return self
    
    def __iter__(self):
        return iter(self.factors)
    
    def __len__(self):
        return self.factors.__len__()
    
    def __delitem__(self, key):
        del self.factors[key]
        
    def part_copy(self, keys:set()):
        temp = {}
        for i in keys:
            temp[i] = self.factors[i]
        return Factors(deepcopy(self.outcome_space), deepcopy(temp))
    
    def pop(self, key):
        return self.factors.pop(key)
    
    def keys(self):
        return self.factors.__iter__()
    
    def values(self):
        return self.factors.values()
    
    def items(self):
        return self.factors.items()
    
    def get_factor(self, f):
        return self.factors[f]
    
    def get_factors(self):
        return self.factors
    
    def get_outcome_space(self):
        return self.outcome_space
    
    def add_factor(self, node, factor, outcom_space = None):
        #在概率表上加入一个因子
        if outcom_space != None:
            self.outcome_space[node] = outcom_space
        
        self.factors[node] = factor
        
    def remove_factor(self, node):
        self.__delitem__(node)
        
    def remove_factors(self,nodes:set = set()):
        for i in nodes:
            self.remove_factor(i)
            
    def update_factor(self , node, factor):
        '''
        update_factor doesn't update outcome_space
        '''
        self.factors[node] = factor
    
    def update_outcome_space(self, dom , value):
        self.outcome_space[dom] = value
    
    def rename_factor(self, old_factor, new_name):
        self.factors[new_name] = self.factors.pop(old_factor)
        
    def evidence(self, var, e):
        #用于更新 outcome_space
        self.outcome_space[var] = (e, )
        
    def evidences(self, e:dict = {}):
        for i in e:
            self.evidence(i, e[i])
            
    def __generateRow(self, t, index, dom, outcomespace, row, new_row, prob, new_dom):
        if index == len(dom):
            prob.append((tuple(new_row), t[tuple(row)]))
            return
        for i in outcomespace[dom[index]]:
            row.append(i)
            if dom[index] in new_dom:
                new_row.append(i)
            
            self.__generateRow(t, index+1, dom, outcomespace, row, new_row, prob, new_dom)
            row.pop()
            if dom[index] in new_dom:
                new_row.pop()
    
    def __generateTable(self, t, dom, outcome_space, new_dom):
        row = []
        new_row = []
        prob = []
        self.__generateRow(t, 0, dom, outcome_space, row, new_row, prob, new_dom)
        factor = {'dom': tuple(new_dom), 'table': odict(prob)}
        return factor
    
    def update_factor_given_evidence(self, f, new_outcome_space, new_dom_set:set):
        new_dom = []
        for i in self.factors[f]['dom']:
            if i in new_dom_set:
                new_dom += [i]
        return self.__generateTable(self.factors[f]['table'], self.factors[f]['dom'], new_outcome_space, new_dom)
    

class CPTs(FactorsBase):
    # 对应一个条件概率表
    # 因子之和未必为1
    # CPTs的概率
    def __init__(self, outcome_space, factors):
        super(CPTs, self).__init__(outcome_space, factors)
        
    def prob(self, f, *entry):
        """
        

        Parameters
        ----------
        f : TYPE
            域和概率值的字典.
        *entry : TYPE
            一组存储facor的值.

        Returns
        -------
        p(entry).

        """
        return self.get_value(f, *entry)
    
    def to_cluster_factor(self):
        cluster_factor = defaultdict(dict)
        for i in self.factors:
            cluster_factor[Cluster(self.factors[i]['dom'])] = self.factors[i]
        return cluster_factor
        
        
class BayesianNet:
    def __init__(self, path:str = "", graph:DAG = None, cpts: CPTs = None):
        if path == "":
            self.graph = graph
            self.cpts = cpts
        else:
            self.graph, self.cpts = self.load_BN(path)
            
    
    def insert_node(self, node, parents:list, cpt, outcome_space = None):
        '''
        If there are some new variables in new node, the coresponding outcome_space also should be updated
        Insert one node, should give all parents
        '''
        self.graph.insert_node(node)
        for p in parents:
            self.graph.connect_edge(p, node)
            
        self.cpts.add_factor(node, cpt, outcome_space)
        
    def remove_node(self, node, cpts = None):
        #一旦删除一个节点，所有子节点的分布都需要重新计算
        children = self.graph[node]
        self.graph.remove_node(node)
        self.cpts.remove_factor(node)
        self.cpts.remove_outcome_space(node)
        for i in children:
            self.cpts.update_factor(i, cpts[i])
            
    def update_factor_in_a_node(self, node, cpt):
        # 并不改变BN的结构，仅仅是更新factor
        if sorted(self.cpts[node]['dom']) == sorted(cpt['dom']):
            self.cpts[node] = cpt
        
        
        