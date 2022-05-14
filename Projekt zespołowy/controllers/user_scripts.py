import sys
import inspect
def get_functions():
    dictionary={}
    list=inspect.getmembers(sys.modules[__name__], \
        predicate = lambda f: inspect.isfunction(f) and f.__module__ == __name__)
    dictionary = dict((x, y) for x, y in list)
    dictionary.pop("get_functions")
    return dictionary

#======================
#User-defined-functions
#======================
def function1():
    print("function1")
def function2():
    print("function2")
def function3():
    print("function3")
def function4():
    print("function4")
def function5():
    print("function5")