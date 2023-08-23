# Binary Tree Implementation
# 3 methods: add new element, delete element, show_tree (depth and breadth)

class Node:
    def __init__(self, data):  # class constructor
        self.data = data
        self.left = self.right = None


class Tree:
    def __init__(self):
        self.root = None

    # this method is recursive
    def __find(self, node, parent, value):
        if node is None:  # tree is empty
            return None, parent, False

        if value == node.data:
            return node, parent, True  # True means that we don't need to add our value to BT

        if value < node.data:
            if node.left:  # !None
                return self.__find(node.left, node, value)

        if value > node.data:
            if node.right:  # !None
                return self.__find(node.right, node, value)

        return node, parent, False  # False means that we can add our value to BT


    def append(self, obj):  # adding new element to binary tree
        # obj Is the instance of class Node
        if self.root is None:  # if tree was empty
            self.root = obj
            return obj

        s, p, flag_find = self.__find(self.root, None, obj.data)
        # s - the vertex to which we attach the added element
        # p - the ancestor of s

        if not flag_find and s: # s exists and we can add the new vertex
            # right or left appending?
            if s.data > obj.data:  # left
                s.left = obj
            else:  # right
                s.right = obj

        return obj

    # algorithm LNR
    # depth-first search and printing of vertexes in sorted order
    def show_tree(self, node):
        if node is None:
            return

        self.show_tree(node.left)
        print(node.data)
        self.show_tree(node.right)

    # breadth-first search
    def show_wide_tree(self, node):
        if node is None:
            return
        verts = [node]
        while verts:
            verts_next = []
            for v in verts:
                print(v.data, end = ' ')
                if v.left:
                    verts_next.append(v.left)
                if v.right:
                    verts_next.append(v.right)
            print()
            verts = verts_next

    # reverse breadth-first search (from the lower layers to the upper from left to right)
    def show_wide_tree_adv(self, node):
        if node is None:
            return

        v = [node]
        rezz = [node]
        while v:
            vn = []
            for x in v:
                if x.right:
                    vn += [x.right]
                if x.left:
                    vn += [x.left]
            rezz += vn
            v = vn
        for i in range(len(rezz) - 1, -1, -1):
            print(rezz[i].data, end=' ')

    def __delete_leaf(self, s, p):
        if p.left == s:
            p.left = None
        elif p.right == s:
            p.right = s
        # s will be deleted by the garbage collector

    def __delete_one_child(self, s, p):
        if s == p.left: # Left branch
            if s.left is None:
                p.left = s.right
            else:
                p.left = s.left

        elif s == p.right: # Left branch
            if s.left is None:
                p.right = s.right
            else:
                p.right = s.left

    # recursive method
    def __find_min(self, node, parent):
        # node exactly is not None
        if node.left: # is not None
            return self.__find_min(node.left, node)
        return node, parent

    def delete_node(self, key):
        s, p, flag_find = self.__find(self.root, None, key)
        # s is a node to delete
        if not flag_find:
            return None  # There is no object to delete

        # if we find our vertex - s will be our vertex
        # flag_find == True

        # 1st situation - leaf vertex (no descendants)
        if s.left is None and s.right is None:
            self.__delete_leaf(s, p)

        # 2nd situation - vertex has 1 descendant
        elif s.left is None or s.right is None:
            self.__delete_one_child(s, p)

        # 3rd situation - vertex has 2 descendants
        else:
            s_mn, pr_mn = self.__find_min(s.right, s)
            s.data = s_mn.data
            self.__delete_one_child(s_mn, pr_mn)


vert = [10, 5, 7, 16, 13, 2, 20]
#vert = [20, 5, 24, 2, 16, 11, 18]
tr = Tree()
for x in vert:
    tr.append(Node(x))

#tr.delete_node(5)
tr.show_wide_tree_adv(tr.root)
