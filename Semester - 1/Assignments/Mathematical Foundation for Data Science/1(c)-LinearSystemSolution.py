import pandas as pandas
import numpy as numpy
from scipy.linalg import solve

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
vectorB = numpy.array(pandas.read_csv("VectorB.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_VectorB, numberOfColumns_VectorB = vectorB.shape
print("Matrix A\t\t\tVector B")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        space = ' '
        if(matrixA[i][j] < 0):
            space = ''
        print(space + format(numpy.round(matrixA[i][j], 2)), end = "\t")
    print(" ", end = "\t")
    for j in range(numberOfColumns_VectorB):
        space = ' '
        if(vectorB[i][j] < 0):
            space = ''
        print(space + format(numpy.round(vectorB[i][j], 2)), end = "\t")
    print(" ")
print(" ")
print("Vector X")
vectorX = solve(matrixA, vectorB)
for i in range(numberOfColumns_MatrixA):
    for j in range(numberOfColumns_VectorB):
        space = ' '
        if(vectorX[i][j] < 0):
            space = ''
        print(space + format(numpy.round(vectorX[i][j], 2)))
