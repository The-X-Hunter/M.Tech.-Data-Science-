import pandas as pandas
import numpy as numpy

def luDecomposition(matrix, numberOfColumns_Matrix):
    lower = [[0 for x in range(numberOfColumns_Matrix)]
             for y in range(numberOfColumns_Matrix)]
    upper = [[0 for x in range(numberOfColumns_Matrix)]
             for y in range(numberOfColumns_Matrix)]
    for i in range(numberOfColumns_Matrix):
        for k in range(i, numberOfColumns_Matrix):
            sum = 0
            for j in range(i):
                sum += lower[i][j] * upper[j][k]
            upper[i][k] = matrix[i][k] - sum
        for k in range(i, numberOfColumns_Matrix):
            if(i == k):
                lower[i][i] = 1
            else:
                sum = 0
                for j in range(i):
                    sum += lower[k][j] * upper[j][i]
                lower[k][i] = int((matrix[k][i] - sum) / upper[i][i])
    print("Lower Triangular\t\tUpper Triangular")
    for i in range(numberOfColumns_Matrix):
        for j in range(numberOfColumns_Matrix):
            print(lower[i][j], end = "\t")
        print(" ", end = "\t")
        for j in range(numberOfColumns_Matrix):
            print(upper[i][j], end = "\t")
        print(" ")

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
print("Matrix A")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(matrixA[i][j], end = "\t")
    print(" ")
print(" ")

luDecomposition(matrixA, numberOfColumns_MatrixA)
