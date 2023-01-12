import pandas as pandas
import numpy as numpy
import matplotlib.pyplot as pyplot

def printFunctionData(matrix, functionMatrix, plotColor, plotMarker, plot_xlabel, plot_ylabel):
    numberOfRows, numberOfColumns = functionMatrix.shape
    for i in range(numberOfRows):
        for j in range(numberOfColumns):
            print(functionMatrix[i][j], end = "\t")
        print(" ")
    pyplot.plot(matrix, functionMatrix, color = plotColor, marker = plotMarker)
    pyplot.xlabel(plot_xlabel)
    pyplot.ylabel(plot_ylabel)
    pyplot.show()

def getExponentialFunctionData(matrix):
    exponentialFunctionMatrix = numpy.exp(matrix)
    print("Exponential Function Data")
    printFunctionData(matrix, exponentialFunctionMatrix, "green", "*", "Matrix Data", "Exponential Function Data");

def getSineFunctionData(matrix):
    sineFunctionMatrix = numpy.sin(matrix)
    print("Sine Function Data")
    printFunctionData(matrix, sineFunctionMatrix, "blue", "*", "Matrix Data", "Sine Function Data");

def getSigmoidFunctionData(matrix):
    sigmoidFunctionMatrix = 1 / (1 + numpy.exp(-matrix))
    print("Sigmoid Function Data")
    printFunctionData(matrix, sigmoidFunctionMatrix, "red", "*", "Matrix Data", "Sigmoid Function Data");

matrixA = numpy.array(pandas.read_csv("MatrixA.csv", sep =',', header = None, index_col = False))#.astype("float")
numberOfRows_MatrixA, numberOfColumns_MatrixA = matrixA.shape
print("Matrix A")
for i in range(numberOfRows_MatrixA):
    for j in range(numberOfColumns_MatrixA):
        print(matrixA[i][j], end = "\t")
    print(" ")
print(" ")
getExponentialFunctionData(matrixA)
print(" ")
getSineFunctionData(matrixA)
print(" ")
getSigmoidFunctionData(matrixA)
print(" ")
