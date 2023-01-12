import pandas as pandas
import numpy as numpy

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
vectorB = numpy.array(pandas.read_csv("VectorB.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_VectorB, numberOfColumns_VectorB = vectorB.shape
print("Matrix A\t\t\tVector B")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(matrixA[i][j], end = "\t")
    print(" ", end = "\t")
    for j in range(numberOfColumns_VectorB):
        print(vectorB[i][j], end = "\t")
    print(" ")
