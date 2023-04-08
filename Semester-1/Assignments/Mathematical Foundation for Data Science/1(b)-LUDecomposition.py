import pandas as pandas
import numpy as numpy
from scipy.linalg import lu

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
print("Matrix A")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        space = ' '
        if(matrixA[i][j] < 0):
            space = ''
        print(space + format(numpy.round(matrixA[i][j], 2)), end = "\t")
    print(" ")
print(" ")
permutationMatrix, lowerTriangularMatrix, upperTriangularMatrix = lu(matrixA)
#print(numpy.allclose(permutationMatrix @ (lowerTriangularMatrix @ upperTriangularMatrix), matrixA))
print("Lower Triangular\t\tUpper Triangular")
for i in range(numberOfColumns_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        space = ' '
        if(lowerTriangularMatrix[i][j] < 0):
            space = ''
        print(space + format(numpy.round(lowerTriangularMatrix[i][j], 2)), end = "\t")
    print(" ", end = "\t")
    for j in range(numberOfColumns_MatrixA):
        space = ' '
        if(upperTriangularMatrix[i][j] < 0):
            space = ''
        print(space + format(numpy.round(upperTriangularMatrix[i][j], 2)), end = "\t")
    print(" ")
