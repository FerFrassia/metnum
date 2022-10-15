import subprocess as sub
import config as c

def runCicloVariandoP():
	print("Corriendo test: Ciclo variando p")
	for p in range(c.minP, c.maxP*100+1):
		if p == 0:
			p = 0.01
		sub.run("../tp1 ./ciclo_variando_p/ciclo_7_p_" + str(p) + ".txt " + str(p/100), shell=True)

def runEstrellaQueApunteAUnaPaginaQueNoApunteANadieVariandoP():
	print("Corriendo test: Estrella que apunta a una pagina que no apunta a nadie variando p")
	for p in range(c.minP, c.maxP*100+1):
		if p == 0:
			sub.run("../tp1 ./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_variando_p/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_7_p_" + str(p) + ".txt " + str(p/100), shell=True)
			p = 0.01
		sub.run("../tp1 ./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_variando_p/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_7_p_" + str(p) + ".txt " + str(p/100), shell=True)

def runCiclo():
	print("Corriendo test: Ciclo")
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./ciclo/ciclo_" + str(i) + ".txt " + str(c.p), shell=True)

def runEstrellaQueApunteAUnaPaginaQueNoApunteANadie():
	print("Corriendo test: Estrella que apunta a una pagina que no apunta a nadie")
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(i) + ".txt " + str(c.starVsNodeP), shell=True)

def runEstrellaVsClique():
	print("Corriendo test: Estrella vs clique")

	fixedN = 500
	for i in range(c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_vs_clique/variando_clique/estrella_vs_clique_" + str(fixedN) + "_" + str(i) + ".txt " + str(c.p), shell=True)
		
	for i in range (c.minNodes, c.maxNodes+1):
		sub.run("../tp1 ./estrella_vs_clique/variando_estrella/estrella_vs_clique_" + str(i) + "_" + str(fixedN) + ".txt " + str(c.p), shell=True)

def runTestP():
	print("Corriendo test: Test p")
	for p in range(c.minP, c.maxP*100+1):
		if p == 0:
			sub.run("../tp1 ./testeo_p/grafo_1/grafo_1_testeo_p_" + str(p) + ".txt " + str(p), shell=True)
			p = 0.01
		sub.run("../tp1 ./testeo_p/grafo_1/grafo_1_testeo_p_" + str(p) + ".txt " + str(p/100), shell=True)

	for p in range(c.minP, c.maxP*100+1):
		if p == 0:
			sub.run("../tp1 ./testeo_p/grafo_2/grafo_2_testeo_p_" + str(p) + ".txt " + str(p), shell=True)
			p = 0.01
		sub.run("../tp1 ./testeo_p/grafo_2/grafo_2_testeo_p_" + str(p) + ".txt " + str(p/100), shell=True)

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

def runGrafoRaloParaTiempo(sizes):
	print("Corriendo test: grafo ralo para medir tiempo")
	for i in sizes:
		for j in range(1, 6):
			print("\tIteración " + str(j) + " de grafo tamaño " + str(i))
			sub.run("../tp1 ./grafo_ralo/grafo_ralo_" + str(i) + ".txt " + str(c.p) + " -t " + str(j), shell=True)

def runGrafoControlParaTiempo(sizes):
	print("Corriendo test: grafo control para medir tiempo")
	for i in sizes:
		for j in range(1, 6):
			print("\tIteración " + str(j) + " de grafo tamaño " + str(i))
			sub.run("../tp1 ./grafo_control/grafo_control_" + str(i) + ".txt " + str(c.p) + " -t " + str(j), shell=True)

def runGrafoDensoParaTiempo(sizes):
	print("Corriendo test: grafo denso para medir tiempo")
	for i in sizes:
		for j in range(1, 6):
			print("\tIteración " + str(j) + " de grafo tamaño " + str(i))
			sub.run("../tp1 ./grafo_denso/grafo_denso_" + str(i) + ".txt " + str(c.p) + " -t " + str(j), shell=True)

def runTests():
	print("Corriendo tests")

	timeExperimentGraphSizes = [8, 16, 32, 64, 128, 256, 512, 1024]

	runCicloVariandoP()
	runEstrellaQueApunteAUnaPaginaQueNoApunteANadieVariandoP()
	runCiclo()
	runEstrellaQueApunteAUnaPaginaQueNoApunteANadie()
	runEstrellaVsClique()
	runTestP()
	runPaginaTramposaGrafoInicial()
	runPaginaTramposaEstrellaFantasma()
	runPaginaTramposaCliqueFantasma()
	runPaginaTramposaCortandoEnlaces()
	runGrafoRaloParaTiempo(timeExperimentGraphSizes)
	runGrafoControlParaTiempo(timeExperimentGraphSizes)
	runGrafoDensoParaTiempo(timeExperimentGraphSizes)

	print("Tests corridos")