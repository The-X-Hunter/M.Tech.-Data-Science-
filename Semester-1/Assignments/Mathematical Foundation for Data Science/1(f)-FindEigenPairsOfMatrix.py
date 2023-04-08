import pandas as pandas
import numpy as numpy
from scipy.linalg import eig

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
eigenValuesOfMatrixA, eigenVectorsOfMatrixA = eig(matrixA)
print("Eigen Pairs")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print("{" + "{}, {}".format(numpy.round(eigenValuesOfMatrixA[j], 2), numpy.round(eigenVectorsOfMatrixA[i][j], 2)) + "}", end = "\t")
    print(" ")
