import numpy
from scipy.optimize import minimize_scalar, minimize

def objectiveFunction(x):
    return ((x * x) + (4 * numpy.cos(x)))

#Below result is for single variable function
minimizationResult = minimize_scalar(objectiveFunction, method = 'bounded', bounds = (1, 2))
#print(minimizationResult)

#Below result is for multi varibale function
x0 = [1]
bounds = [(1, 2)]
minimizationResult = minimize(objectiveFunction, x0 = x0, bounds = bounds)
#print(minimizationResult)
if(minimizationResult.success == 1):
    print("Function f(x): {(x * x) + (4 * cos(x)), x belongs to R}")
    print("It is minima for x = " + format(numpy.round(minimizationResult.x[0], 2)) + ", where f(x) = " + format(numpy.round(minimizationResult.fun[0], 2)))
else:
    print("Can't minimize the function f(x): {(x * x) + (4 * cos(x)), x belongs to R}");
