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

def generateGrafo1Graph():
	results1 = []
	results2 = []
	results3 = []
	results4 = []
	for p in range(c.minP, c.maxP*100+1):
		file = open("./testeo_p/grafo_1/grafo_1_testeo_p_" + str(p) + ".txt.out", "r")
		lines = (file.readlines())[1:]
		file.close()
		results1.append(float(lines[0]))
		results2.append(float(lines[1]))
		results3.append(float(lines[2]))
		results4.append(float(lines[3]))

	x = [x/100 for x in range(c.minP, c.maxP*100+1)]
	plt.xlabel("p")
	plt.ylabel("Rankings")
	plt.plot(x, results1, color="mediumblue", label="P1")
	plt.plot(x, results2, color="cornflowerblue", label="P2")
	plt.plot(x, results3, color="cyan", label="P3")
	plt.plot(x, results4, color="lightblue", label="P4")
	plt.legend()
	plt.show()

def generateGrafo2Graph():
	results1 = []
	results2 = []
	results3 = []
	results4 = []
	results5 = []
	results6 = []
	for p in range(c.minP, c.maxP*100+1):
		file = open("./testeo_p/grafo_2/grafo_2_testeo_p_" + str(p) + ".txt.out", "r")
		lines = (file.readlines())[1:]
		file.close()
		results1.append(float(lines[0]))
		results2.append(float(lines[1]))
		results3.append(float(lines[2]))
		results4.append(float(lines[3]))
		results5.append(float(lines[4]))
		results6.append(float(lines[5]))

	x = [x/100 for x in range(c.minP, c.maxP*100+1)]
	plt.xlabel("p")
	plt.ylabel("Rankings")
	plt.plot(x, results1, color="mediumblue", label="P1")
	plt.plot(x, results2, color="cornflowerblue", label="P2")
	plt.plot(x, results3, color="cyan", label="P3")
	plt.plot(x, results4, color="lightblue", label="P4")
	plt.plot(x, results5, color="red", label="P5")
	plt.plot(x, results6, color="maroon", label="P6")
	plt.legend()
	plt.show()

def generatePGraph():
	generateGrafo1Graph()
	generateGrafo2Graph()

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

	return averageResults[4]


def generatePaginaTramposaBarPlot():
	grafoInicialAvg = obtainAverageResultsFor("./pagina_tramposa/grafo_inicial/grafo_inicial_")
	estrellaFantasmaAvg = obtainAverageResultsFor("./pagina_tramposa/estrella_fantasma/estrella_fantasma_")
	cliqueFantasmaAvg = obtainAverageResultsFor("./pagina_tramposa/clique_fantasma/clique_fantasma_")
	cortandoEnlacesAvg = obtainAverageResultsFor("./pagina_tramposa/cortando_enlaces/cortando_enlaces_")
	data = {'Grafo Inicial': grafoInicialAvg, 'Cortando Enlaces': cortandoEnlacesAvg, 'Estrella Fantasma': estrellaFantasmaAvg, 'Clique Fantasma': cliqueFantasmaAvg}
	courses = list(data.keys())
	values = list(data.values())
	
	fig = plt.figure(figsize = (10, 5))
	
	# creating the bar plot
	plt.bar(courses, values, color ='lightblue', width = 0.4)
	
	plt.xlabel("Estrategias")
	plt.ylabel("Ranking")
	plt.title("Ranking de nodo 5 variando estrategias")
	plt.show()

def generateGraphs():
	print("Generando gráficos")

	#generateCicloGraph()
	#generateEstrellaQueApunteAUnaPaginaQueNoApunteANadieGraph()
	#generateEstrellaVsCliqueGraph()
	generatePGraph()
	#generatePaginaTramposaBarPlot()

	print("Gráficos generados")
