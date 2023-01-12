import pandas as pandas
import numpy as numpy
from scipy.linalg import eig

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
print("Matrix A")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(matrixA[i][j], end = "\t")
    print(" ")
print(" ")
eigenValuesOfMatrixA, eigenVectorsOfMatrixA = eig(matrixA)
print("Eigen Pairs")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print("{" + "{}, {}".format(eigenValuesOfMatrixA[j], eigenVectorsOfMatrixA[i][j]) + "}")
    print(" ")
