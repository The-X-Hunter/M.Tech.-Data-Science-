import numpy
import sympy
from scipy.optimize import minimize_scalar

#x(k+1) = xk - (ak * df(xk))


#x1 = x0 - (ak * df(x0))
#x0 is given
#ak >= 0
#f(x) is given,
#	take df(x)
#	put x0 in df(x) and get df(x0)


#x2 = x1 - (ak - df(x1))
#x1 is what we got previously
#ak >= 0
#f(x) is given
#	take df(x)
#	put x1 in df(x) and get df(x1)

def aReturn(a):
    return a0[0]
def derivationOfEquation(variable):
	return sympy.Derivative(equationReturn(x, y, z), variable).doit()
def equationReturn(x, y, z):
	return ((x - 4) ** 4) + ((y - 3) ** 2) - (4 * ((z + 5) ** 4))

x, y, z, a = sympy.symbols('x y z a')
x0 = [4, 2, -1]
derivationRespectToX = derivationOfEquation(x)
derivationRespectToY = derivationOfEquation(y)
derivationRespectToZ = derivationOfEquation(z)
df = sympy.Matrix([
	derivationRespectToX,
	derivationRespectToY,
	derivationRespectToZ
	])

df0 = numpy.array(df.subs({x: x0[0], y: x0[1], z: x0[2]}))
#ak = [[xk[0] - a * dfk[0], ....]
equationForDerivationOfX = numpy.subtract(x0[0], a * df0[0])
equationForDerivationOfY = numpy.subtract(x0[1], a * df0[1])
equationForDerivationOfZ = numpy.subtract(x0[2], a * df0[2])
a0 = sympy.Matrix(equationReturn(equationForDerivationOfX, equationForDerivationOfY, equationForDerivationOfZ))
print(a0)
minimizationResult = minimize_scalar(aReturn)
print(minimizationResult)
#a = sympy.Matrix([a0, a0, a0, a0, a0, a0])
for i in range(0, 6): 
	print(a0.subs({a: i}))
