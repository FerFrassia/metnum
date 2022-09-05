import subprocess as sub
import config as c

def runCiclo():
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./ciclo/ciclo_" + str(i) + ".txt " + str(c.p), shell=True)

def runEstrellaQueApunteAUnaPaginaQueNoApunteANadie():
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(i) + ".txt " + str(c.p), shell=True)

def runEstrellaVsClique():
	for i in range(c.minNodes, c.maxNodes+1):
		for j in range (c.minNodes, c.maxNodes+1):
			sub.run("../tp1 ./estrella_vs_clique/estrella_vs_clique_" + str(i) + "_" + str(j) + ".txt " + str(c.p), shell=True)

def runCaminoLargoParaTestearP():
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./camino_largo_para_testear_p/camino_largo_para_testear_p_" + str(i) + ".txt " + str(c.p), shell=True)

def runTests():
	runCiclo()
	runEstrellaQueApunteAUnaPaginaQueNoApunteANadie()
	runEstrellaVsClique()
	runCaminoLargoParaTestearP()

runTests()