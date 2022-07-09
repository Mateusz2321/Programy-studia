
def get_functions():
    python_file = open("user_actions/actions.txt").read()
    ns = {}
    exec(python_file, globals(), ns)
    ns2 = {}
    for a in ns.keys():
        ns2["user_"+a] = ns.get(a)
    return ns2

