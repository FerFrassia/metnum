import subprocess as sub
import config as c

def runCiclo():
	print("Corriendo test: Ciclo")
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./ciclo/ciclo_" + str(i) + ".txt " + str(c.p), shell=True)

def runEstrellaQueApunteAUnaPaginaQueNoApunteANadie():
	print("Corriendo test: Estrella que apunta a una pagina que no apunta a nadie")
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(i) + ".txt " + str(c.p), shell=True)

def runEstrellaVsClique():
	print("Corriendo test: Estrella vs clique")

	fixedN = 500
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_vs_clique/variando_clique/estrella_vs_clique_" + str(fixedN) + "_" + str(i) + ".txt " + str(c.p), shell=True)
		
	for i in range (c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_vs_clique/variando_estrella/estrella_vs_clique_" + str(i) + "_" + str(fixedN) + ".txt " + str(c.p), shell=True)

def runCaminoLargoParaTestearP():
	print("Corriendo test: Camino largo para testear p")
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./camino_largo_para_testear_p/camino_largo_para_testear_p_" + str(i) + ".txt " + str(c.p), shell=True)

def runPaginaTramposaGrafoInicial():
	print("Corriendo test: Pagina tramposa, grafo inicial")
	for i in range(1, c.repetitionsForCheaterTest+1):
		sub.run("../tp1 ./pagina_tramposa/grafo_inicial/grafo_inicial_" + str(i) + ".txt " + str(c.p), shell=True)

def runPaginaTramposaEstrellaFantasma():
	print("Corriendo test: Pagina tramposa, estrella fantasma")
	for i in range(1, c.repetitionsForCheaterTest+1):
		sub.run("../tp1 ./pagina_tramposa/estrella_fantasma/estrella_fantasma_" + str(i) + ".txt " + str(c.p), shell=True)

def runPaginaTramposaCliqueFantasma():
	print("Corriendo test: Pagina tramposa, clique fantasma")
	for i in range(1, c.repetitionsForCheaterTest+1):
		sub.run("../tp1 ./pagina_tramposa/clique_fantasma/clique_fantasma_" + str(i) + ".txt " + str(c.p), shell=True)

def runPaginaTramposaCortandoEnlaces():
	print("Corriendo test: Pagina tramposa, cortando enlaces")
	for i in range(1, c.repetitionsForCheaterTest+1):
		sub.run("../tp1 ./pagina_tramposa/cortando_enlaces/cortando_enlaces_" + str(i) + ".txt " + str(c.p), shell=True)

def runTests():
	print("Corriendo tests")

	runCiclo()
	runEstrellaQueApunteAUnaPaginaQueNoApunteANadie()
	runEstrellaVsClique()
	runCaminoLargoParaTestearP()
	runPaginaTramposaGrafoInicial()
	runPaginaTramposaEstrellaFantasma()
	runPaginaTramposaCliqueFantasma()
	runPaginaTramposaCortandoEnlaces()

	print("Tests corridos")