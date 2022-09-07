import numpy as np

def calculateAbsoluteError(filename):
	y = []
	catedra = open("./enunciado/tests/" + filename + ".txt.out", "r")
	propio = open("./enunciado/tests/" + filename + ".txt_propio.out", "r")
	err = 0
	a = b = []
	for l1, l2 in zip(catedra, propio):
		a.append(float(l1))
		b.append(float(l2))
	
	err = np.linalg.norm(np.array(a)-np.array(b))
	print('El error absoluto es:' + str(err))

calculateAbsoluteError("test_15_segundos")