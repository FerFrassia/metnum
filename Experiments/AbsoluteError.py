import numpy as np
import subprocess as sub

tests = ["test_15_segundos", "test_30_segundos", "test_aleatorio", "test_aleatorio_desordenado", "test_completo", "test_sin_links", "test_trivial"]

result_dicc = {}

def calculateAbsoluteError(filename, p):
	sub.run("./tp1 ./enunciado/tests/" + filename + ".txt " + str(p), shell=True)
	catedra = open("./enunciado/tests/" + filename + ".txt.out", "r")
	propio = open("./enunciado/tests/" + filename + ".txt.propio.out", "r")
	err = 0
	a = b = []
	for l1, l2 in zip(catedra, propio):
		a.append(float(l1))
		b.append(float(l2))
	
	err = np.linalg.norm(np.array(a)-np.array(b))
	result_dicc[filename] = err

for test in tests:
	prob = open("./enunciado/tests/" + test + ".txt.out", "r").readline()
	print(str(prob))
	calculateAbsoluteError(test, prob)
