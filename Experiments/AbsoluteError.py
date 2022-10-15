import json
import numpy as np
import subprocess as sub
import matplotlib.pyplot as plt

tests = ["test_15_segundos", "test_30_segundos", "test_aleatorio_desordenado", "test_completo", "test_sin_links", "test_trivial"]

result_dict = {}

def calculateAbsoluteError(filename, p, runFile):
	if (runFile):
		sub.run("./tp1 ./enunciado/tests/" + filename + ".txt " + str(p), shell=True)
	catedra = open("./enunciado/tests/" + filename + ".txt.out", "r")
	propio = open("./enunciado/tests/" + filename + ".txt.propio.out", "r")
	err = 0
	a = []
	b = []
	for l1, l2 in zip(catedra, propio):
		a.append(float(l1))
		b.append(float(l2))

	arr_propio = np.array(a)
	arr_catedra = np.array(b)

	err = np.linalg.norm(arr_propio-arr_catedra)
	result_dict[filename] = err

def calculateCoordinatesError(filename):
	catedra = open("./enunciado/tests/" + filename + ".txt.out", "r")
	propio = open("./enunciado/tests/" + filename + ".txt.propio.out", "r")
	err = 0
	a = []
	b = []
	for l1, l2 in zip(catedra, propio):
		a.append(float(l1))
		b.append(float(l2))

	arr_propio = np.array(a)
	arr_catedra = np.array(b)

	err = max(np.abs(arr_propio-arr_catedra))
	result_dict[filename] = "{:.8f}".format(float(err))

for test in tests:
	prob = open("./enunciado/tests/" + test + ".txt.out", "r").readline()

	calculateAbsoluteError(test, prob, False)
	with open("./enunciado/tests/errores_absolutos.txt", 'w') as convert_file:
		convert_file.write(json.dumps(result_dict))

	calculateCoordinatesError(test)
	with open("./enunciado/tests/errores_coordenada.txt", 'w') as convert_file:
		convert_file.write(json.dumps(result_dict))
