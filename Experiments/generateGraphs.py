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
		file.close()
		count = 0
		results = []
		for line in lines:
			if count != 0:
				results.append(float(line))
			count += 1

		y.append(sum(results) / len(results))

	x = list(range(c.minNodes, c.maxNodes+1))
	z = [1/z for z in range(c.minNodes, c.maxNodes+1)]
	plt.xlabel("Número de páginas")
	plt.ylabel("Promedio de todos los rankings")
	plt.plot(x, z, color="blue", label="Valor esperado")
	plt.plot(x, y, color="red", label="Experimento")
	plt.legend()
	plt.show()

def generateEstrellaQueApunteAUnaPaginaQueNoApunteANadieGraph():
	y = []
	for n in range(c.minNodes, c.maxNodes+1):
		file = open("./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(n) + ".txt.out", "r")
		lines = file.readlines()
		file.close()
		count = 0
		results = []
		for line in lines:
			if count != 0:
				results.append(float(line))
			count += 1

		y.append(results)

	x = list(range(c.minNodes, c.maxNodes+1))
	plt.title("Resultados en grafo estrella que apunta a un nodo con grado de salida 0")
	plt.xlabel("Número de páginas")
	plt.ylabel("")

	lastPageRankings = [x[-1] for x in y]
	plt.plot(x, lastPageRankings, label="Última página", color="green")

	secondToLastPageRankings = [x[-2] for x in y]
	plt.plot(x, secondToLastPageRankings, label = "Centro de la estrella", color="red")

	for i in range(c.minNodes, c.maxNodes+1):
		currentPageRankings = [x[-i] for x in y if i<=len(x)]
		x_i = list(range(i, c.maxNodes+1))
		plt.plot(x_i, currentPageRankings, color="black")

	plt.plot()
	plt.legend()
	plt.show()

def obtainAverageResultsFor(path):
	allResults = []
	for i in range(1, c.repetitionsForCheaterTest+1):
		file = open(path + str(i) + ".txt.out", "r")
		lines = (file.readlines())[1:]
		allResults.append([float(line) for line in lines])
		file.close()

	averageResults = []
	for i in range(0, c.cheaterGraphSize):
		sumRankingForIPage = 0
		for l in allResults:
			sumRankingForIPage += l[i]
		averageResults.append(sumRankingForIPage/len(allResults))

	return averageResults

def generatePaginaTramposaGrafoInicialGraph():
	averageResults = obtainAverageResultsFor("./pagina_tramposa/grafo_inicial/grafo_inicial_")

def generatePaginaTramposaEstrellaFantasmaGraph():
	averageResults = obtainAverageResultsFor("./pagina_tramposa/estrella_fantasma/estrella_fantasma_")

def generatePaginaTramposaCliqueFantasmaGraph():
	averageResults = obtainAverageResultsFor("./pagina_tramposa/clique_fantasma/clique_fantasma_")

def generatePaginaTramposaCortandoEnlacesGraph():
	averageResults = obtainAverageResultsFor("./pagina_tramposa/cortando_enlaces/cortando_enlaces_")

def generateGraphs():
	generateCicloGraph()
	generateEstrellaQueApunteAUnaPaginaQueNoApunteANadieGraph()
	generatePaginaTramposaGrafoInicialGraph()
	generatePaginaTramposaEstrellaFantasmaGraph()
	generatePaginaTramposaCliqueFantasmaGraph()
	generatePaginaTramposaCortandoEnlacesGraph()
