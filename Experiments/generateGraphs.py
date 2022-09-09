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
	plt.xlabel("Número de páginas")
	plt.ylabel("Ranking")

	lastPageRankings = [x[-1] for x in y]
	plt.plot(x, lastPageRankings, label="P2", color="blue")

	secondToLastPageRankings = [x[-2] for x in y]
	plt.plot(x, secondToLastPageRankings, label = "P1", color="red")

	for i in range(c.minNodes, c.maxNodes+1):
		currentPageRankings = [x[-i] for x in y if i<=len(x)]
		x_i = list(range(i, c.maxNodes+1))
		plt.plot(x_i, currentPageRankings, color="black")

	plt.plot()
	plt.legend()
	plt.show()

def generateEstrellaVsCliqueGraph():
	resultsVariandoEstrella = []
	for i in range(c.minNodes, c.maxNodes+1):
		file = open("./estrella_vs_clique/variando_estrella/estrella_vs_clique_" + str(i) + "_500.txt.out", "r")
		lines = (file.readlines())[1:]
		file.close()
		resultsVariandoEstrella.append(float(lines[i-1]))

	resultsVariandoClique = []
	for i in range(c.minNodes, c.maxNodes+1):
		file = open("./estrella_vs_clique/variando_clique/estrella_vs_clique_500_" + str(i) + ".txt.out", "r")
		lines = (file.readlines())[1:]
		file.close()
		resultsVariandoClique.append(float(lines[500-1]))

	x = list(range(c.minNodes, c.maxNodes+1))
	plt.xlabel("Número de páginas")
	plt.ylabel("Ranking de P1")
	plt.plot(x, resultsVariandoEstrella, color="blue", label="Variando estrella")
	plt.plot(x, resultsVariandoClique, color="red", label="Variando clique")
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
	generateEstrellaVsCliqueGraph()
	generatePaginaTramposaGrafoInicialGraph()
	generatePaginaTramposaEstrellaFantasmaGraph()
	generatePaginaTramposaCliqueFantasmaGraph()
	generatePaginaTramposaCortandoEnlacesGraph()

generateEstrellaVsCliqueGraph()
