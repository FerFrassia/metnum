import numpy as np
import matplotlib.pyplot as plt
import config as c

def allElementsAreEqual(elements):
	return all(x == elements[0] for x in elements)

def generateCicloGraph():
	y = []
	for n in range(c.minNodes, c.maxNodes+1):
		file = open("./ciclo/ciclo_" + str(n) + ".txt.out", "r")
		lines = file.readlines()
		count = 0
		results = []
		for line in lines:
			if count != 0:
				results.append(float(line))
			count += 1

		y.append(sum(results) / len(results))

	x = list(range(c.minNodes, c.maxNodes+1))
	z = [1/z for z in range(c.minNodes, c.maxNodes+1)]
	plt.title("Resultados en grafo ciclo")
	plt.xlabel("Número de páginas")
	plt.ylabel("Promedio")
	plt.plot(x, z, color="blue", label="1/n")
	plt.plot(x, y, color="red", label="algorithm")
	plt.legend()
	plt.show()

def generateGraphs():
	generateCicloGraph()
