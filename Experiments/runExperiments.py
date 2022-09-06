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

def runTests():
	print("Corriendo tests")

	runCiclo()
	runEstrellaQueApunteAUnaPaginaQueNoApunteANadie()
	runEstrellaVsClique()
	runCaminoLargoParaTestearP()

	print("Tests corridos")