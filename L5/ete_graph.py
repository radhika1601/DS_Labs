import sys
from ete3 import Tree, TreeStyle

t = Tree("{}".format(sys.argv[1]), format = 1)

ts = TreeStyle()
ts.show_leaf_name = True
#ts.show_internal = True
ts.show_branch_length = True
print(t.get_ascii(attributes=["dist","name" ]))
t.show(tree_style = ts)

t.render("./ete_graph.pdf", w=10, units = "mm")
