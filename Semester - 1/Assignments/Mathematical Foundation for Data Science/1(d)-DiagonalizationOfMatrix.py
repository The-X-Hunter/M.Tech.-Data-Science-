import pandas as pandas
import numpy as numpy
from scipy.linalg import eig
#from sympy import *

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
print("Matrix A")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(matrixA[i][j], end = "\t")
    print(" ")
print(" ")
eigenValuesOfMatrixA, eigenVectorsOfMatrixA = eig(matrixA)
diagonalizedMatrix = numpy.zeros((numberOfRows_MatrixA, numberOfColumns_MatrixA))
for i in range(numberOfRows_MatrixA):
    diagonalizedMatrix[i][i] = eigenValuesOfMatrixA[i].real
#modalMatrix, diagonalizedMatrix = Matrix(matrixA).diagonalize()
print("Diagonalized Matrix")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(diagonalizedMatrix[i][j], end = "\t\t\t")
    print(" ")
print(" ")
