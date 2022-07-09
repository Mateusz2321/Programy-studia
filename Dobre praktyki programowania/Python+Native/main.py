import ctypes
import numpy
import time
import sys
import os
def read_data_from_file(filename, interpolation_points_x: list,interpolation_points_y: list, points: list):
    try:
        with open (filename,"r") as f:
            lst = f.readlines()
    except:
        return
    counter=0   #better use index and two for
    while counter < len(lst):
        temp = lst[counter].split(";")
        if len(temp) ==2:
            temp[1]= temp[1] [:-2]
            temp = [float(i) for i in temp]
            interpolation_points_x.append(temp[0])
            interpolation_points_y.append(temp[1])
            counter+=1
        else:
            break

    for a in range(counter, len(lst)):
        points.append(float(lst[a]))

print("Newton interpolation")
#file= input("Podaj nazwę pliku z danymi: ")
file = "interpolation.txt"
interpolation_points_x = []
interpolation_points_y = []
points = []
read_data_from_file(file, interpolation_points_x, interpolation_points_y , points)
length = len(interpolation_points_x)
if length == 0 or len(interpolation_points_y) != length or len(points) == 0:
    print("Nie podano poprawnych danych wejściowych!")
    sys.exit()
newton_approximator = ctypes.CDLL('./build//lib.linux-x86_64-3.8/approximate_point_using_newton_polynomial.cpython-38-x86_64-linux-gnu.so')
newton_approximator.approximate_point_using_newton_polynomial.restype = ctypes.c_double
newton_approximator.approximate_point_using_newton_polynomial.argtypes = [ctypes.c_double,ctypes.c_int,
                        ctypes.POINTER(ctypes.c_double),ctypes.POINTER(ctypes.c_double)]

for i in points:
    print("Newton approximate for "+str(i)+": "+str(newton_approximator.approximate_point_using_newton_polynomial(
        i, length,(ctypes.c_double *length)(*interpolation_points_x),(ctypes.c_double*length)(*interpolation_points_y)
    )))
time.sleep(10)


