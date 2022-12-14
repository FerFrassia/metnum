import os
import config as c
import random

#Aux:
def crearRuta(path):
    if not os.path.exists(path):
        os.makedirs(path)
    return path

#Test: Ciclo
def generarCiclo(file, n):
    file.write(str(n) + "\n")
    file.write(str(n) + "\n")
    for page in range(1, n):
	    file.write(str(page) + " " + str(page + 1) + "\n")
    file.write(str(n) + " 1" + "\n")

def testCiclo():
    print("Generando: Ciclo")
    path = crearRuta("./ciclo")
    for i in range(c.minNodes, c.maxNodes + 1):
        output = open(path + "/ciclo_" + str(i) + ".txt", "w")
        generarCiclo(output, i)
        output.close()

#Test: Estrella vs Nodo con grado de salida 0
def generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(file, n):
    file.write(str(n) + "\n")
    file.write(str(n - 1) + "\n")
    for page in range(1, n - 1):
        file.write(str(page) + " " + str(n - 1) + "\n")
    file.write(str(n - 1) + " " + str(n) + "\n")

def testEstrellaQueApunteAUnaPaginaQueNoApunteANadie():
    print("Generando: Estrella que apunta a una pagina que no apunta a nadie")
    path = crearRuta("./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie")

    for i in range(c.minNodes, c.maxNodes + 1):
        output = open(path + "/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(i) + ".txt", "w")
        generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(output, i)
        output.close()

#Test: Estrella vs Clique
def generarEstrellaVsClique(file, starSize, cliqueSize):
    totalNodes = starSize + cliqueSize
    file.write(str(totalNodes) + "\n")

    starLinks = starSize - 1
    cliqueLinks = cliqueSize * (cliqueSize - 1)
    inBetweenLinks = cliqueSize
    file.write(str(starLinks + cliqueLinks + inBetweenLinks) + "\n")

    # generate star links
    for page in range(1, starSize):
        file.write(str(page) + " " + str(starSize) + "\n")

    # generate in between links
    for page in range(starSize + 1, totalNodes + 1):
        file.write(str(starSize) + " " + str(page) + "\n")

    # generate cliqueLinks
    for i in range(starSize + 1, totalNodes + 1):
        for j in range(starSize + 1, totalNodes + 1):
            if i != j:
                file.write(str(i) + " " + str(j) + "\n")

def testEstrellaVsClique():
    print("Generando: Estrella vs clique")
    path = crearRuta("./estrella_vs_clique")
    pathClique = crearRuta(path + "/variando_clique")
    pathEstrella = crearRuta(path + "/variando_estrella")
    fixedN = 500

    #variando tama??o de la clique
    for i in range(c.minNodes, c.maxNodes + 1):
        output = open(pathClique + "/estrella_vs_clique_" + str(fixedN) + "_" + str(i) + ".txt", "w")
        generarEstrellaVsClique(output, fixedN, i)
        output.close()

    #variando tama??o de la estrella
    for i in range(c.minNodes, c.maxNodes + 1):
        output = open(pathEstrella + "/estrella_vs_clique_" + str(i) + "_" + str(fixedN) + ".txt", "w")
        generarEstrellaVsClique(output, i, fixedN)
        output.close()

#Test: Camino para testear p
def generarCaminoLargoParaTestearP(file, n):
    file.write(str(n) + "\n")
    file.write(str(n - 1) + "\n")
    for page in range(1, n):
        file.write(str(page) + " " + str(page + 1) + "\n")

def generarGrafo1TesteoP(file):
    file.write("4\n")
    file.write("3\n")
    file.write("1 2\n")
    file.write("3 2\n")
    file.write("1 4\n")

def generarGrafo2TesteoP(file):
    file.write("6\n")
    file.write("4\n")
    file.write("1 2\n")
    file.write("3 2\n")
    file.write("1 4\n")
    file.write("5 6\n")

def testGrafo1P():
    path = crearRuta("./testeo_p/grafo_1")
    for p in range(c.minP, c.maxP*100+1):
        if p == 0:
            p = 0.01
        output = open(path + "/grafo_1_testeo_p_" + str(p) + ".txt", "w")
        generarGrafo1TesteoP(output)
        output.close()

def testGrafo2P():
    path = crearRuta("./testeo_p/grafo_2")
    for p in range(c.minP, c.maxP*100+1):
        if p == 0:
            p = 0.01
        output = open(path + "/grafo_2_testeo_p_" + str(p) + ".txt", "w")
        generarGrafo2TesteoP(output)
        output.close()

def testP():
    print("Generando: Test p")
    
    testGrafo1P()
    testGrafo2P()

#Test: Grafos ralos, densos y de control
def generarRandomLink(n):
	possiblePages = [x for x in range(1,n+1)]
	referencingPage = random.choice(possiblePages)
	possiblePages.remove(referencingPage)
	referencedPage = random.choice(possiblePages)
	return (referencingPage, referencedPage)

def generarGrafo(file, n, cantLinks):
	file.write(str(n) + "\n")
	file.write(str(cantLinks) + "\n")

	writtenLinks = []
	for i in range(1, cantLinks+1):
		link = generarRandomLink(n)
		while link in writtenLinks:
			link = generarRandomLink(n)
		file.write(str(link[0]) + " " + str(link[1]) + "\n")
		writtenLinks.append(link)

def generarGrafoRalo(file, n):
    generarGrafo(file, n, int(n*(n-1)*0.05))

def generarGrafoControl(file, n):
	generarGrafo(file, n, int(n*(n-1)*0.4))

def generarGrafoDenso(file, n):
	cantLinks = int(n*(n-1)*0.9)
	file.write(str(n) + "\n")
	file.write(str(cantLinks) + "\n")

	possibleLinks = []
	for i in range(1, n+1):
		for j in range(1, n+1):
			if i!= j:
				possibleLinks.append((i,j))

	for i in range(1, cantLinks+1):
		link = random.choice(possibleLinks)
		file.write(str(link[0]) + " " + str(link[1]) + "\n")
		possibleLinks.remove(link)

def testGrafoRalo(sizes):
    print("Generando: Grafo Ralo")
    path = crearRuta("./grafo_ralo")

    for n in sizes:
        output = open(path + "/grafo_ralo_" + str(n) + ".txt", "w")
        generarGrafoRalo(output, n)
        output.close()

def testGrafoControl(sizes):
    print("Generando: Grafo Control")
    path = crearRuta("./grafo_control")

    for n in sizes:
        output = open(path + "/grafo_control_" + str(n) + ".txt", "w")
        generarGrafoControl(output, n)
        output.close()

def testGrafoDenso(sizes):
    print("Generando: Grafo Denso")
    path = crearRuta("./grafo_denso")

    for n in sizes:
        output = open(path + "/grafo_denso_" + str(n) + ".txt", "w")
        generarGrafoDenso(output, n)
        output.close()

#Test: P??gina tramposa, grafo inicial
def testPaginaTramposaGrafoInicial():
    print("Generando: Pagina tramposa, grafo inicial")
    path = crearRuta("./pagina_tramposa/grafo_inicial")

    for i in range(1, c.repetitionsForCheaterTest+1):    
        output = open(path + "/grafo_inicial_" + str(i) + ".txt", "w")
        generarGrafoControl(output, c.cheaterGraphSize)
        output.close()

#Test: P??gina tramposa, estrella fantasma
def generarEstrellaFantasma(file, totalNodesBefore, totalLinksBefore, inputLinks):
    totalNodesAfter = totalNodesBefore + c.cheaterPageBudget
    totalLinksAfter = totalLinksBefore + c.cheaterPageBudget
    file.write(str(totalNodesAfter) + "\n")
    file.write(str(totalLinksAfter) + "\n")
    for line in inputLinks:
        file.write(line)

    for k in range(totalNodesBefore+1, totalNodesAfter+1):
        file.write(str(k) + " " + str(c.cheaterPage) + "\n")

def testPaginaTramposaEstrellaFantasma():
    print("Generando: Pagina tramposa, estrella fantasma")
    inputPath = crearRuta("./pagina_tramposa/grafo_inicial")
    outputPath = crearRuta("./pagina_tramposa/estrella_fantasma")

    for i in range(1, c.repetitionsForCheaterTest+1):
        inputGraph = open(inputPath + "/grafo_inicial_" + str(i) + ".txt", "r")
        inputLinks = inputGraph.readlines()
        totalNodesBefore = int((inputLinks.pop(0))[:-1])
        totalLinksBefore = int((inputLinks.pop(0))[:-1])
        inputGraph.close()

        output = open(outputPath + "/estrella_fantasma_" + str(i) + ".txt", "w")
        generarEstrellaFantasma(output, totalNodesBefore, totalLinksBefore, inputLinks)
        output.close()

#Test: P??gina tramposa, clique fantasma
def generarCliqueFantasma(file, totalNodesBefore, totalLinksBefore, inputLinks):
    totalNodesAfter = totalNodesBefore + c.cheaterPageBudget
    totalLinksAfter = totalLinksBefore + c.cheaterPageBudget + c.cheaterPageBudget*(c.cheaterPageBudget-1)
    file.write(str(totalNodesAfter) + "\n")
    file.write(str(totalLinksAfter) + "\n")

    for line in inputLinks:
        file.write(line)

    for i in range(totalNodesBefore+1, totalNodesAfter+1):
        for j in range(totalNodesBefore + 1, totalNodesAfter + 1):
            if i != j:
                file.write(str(i) + " " + str(j) + "\n")
        file.write(str(i) + " " + str(c.cheaterPage) + "\n")

def testPaginaTramposaCliqueFantasma():
    print("Generando: Pagina tramposa, clique fantasma")
    inputPath = crearRuta("./pagina_tramposa/grafo_inicial")
    outputPath = crearRuta("./pagina_tramposa/clique_fantasma")

    for i in range(1, c.repetitionsForCheaterTest+1):   
        inputGraph = open(inputPath + "/grafo_inicial_" + str(i) + ".txt", "r")
        inputLinks = inputGraph.readlines()
        totalNodesBefore = int((inputLinks.pop(0))[:-1])
        totalLinksBefore = int((inputLinks.pop(0))[:-1])
        inputGraph.close()

        output = open(outputPath + "/clique_fantasma_" + str(i) + ".txt", "w")
        generarCliqueFantasma(output, totalNodesBefore, totalLinksBefore, inputLinks)
        output.close()

#Test: P??gina tramposa, cortando enlaces
def analizarGradosDeEntradaDeLasPaginasApuntadasPorLaPaginaTramposa(links):
    gradosDeEntrada = {}
    for link in links:
        referencedPage = int((link.split(" "))[1])
        if referencedPage in gradosDeEntrada.keys():
            gradosDeEntrada[referencedPage] = gradosDeEntrada[referencedPage] + 1
        else:
            gradosDeEntrada[referencedPage] = 1

    gradosDeApuntadosPorMi = []
    for link in links:
        referencingPage = int((link.split(" "))[0])
        referencedPage = int((link.split(" "))[1])
        if referencingPage == c.cheaterPage:
            gradosDeApuntadosPorMi.append((referencedPage, gradosDeEntrada[referencedPage]))

    gradosDeApuntadosPorMiOrdenadosDescendentementePorGrado = sorted(gradosDeApuntadosPorMi, key=lambda tup: tup[1], reverse=True)

    return gradosDeApuntadosPorMiOrdenadosDescendentementePorGrado


def testPaginaTramposaCortandoEnlacesDeSalida():
    print("Generando: Pagina tramposa, cortando enlaces")
    inputPath = crearRuta("./pagina_tramposa/grafo_inicial")
    outputPath = crearRuta("./pagina_tramposa/cortando_enlaces")

    for i in range(1, c.repetitionsForCheaterTest+1):
        inputGraph = open(inputPath + "/grafo_inicial_" + str(i) + ".txt", "r")
        inputLinks = inputGraph.readlines()
        totalNodesBefore = int((inputLinks.pop(0))[:-1])
        totalLinksBefore = int((inputLinks.pop(0))[:-1])
        inputGraph.close()

        grados = analizarGradosDeEntradaDeLasPaginasApuntadasPorLaPaginaTramposa(inputLinks)
        paginasADejarDeApuntar = grados[0:c.cheaterLinkBudget]

        totalNodesAfter = totalNodesBefore
        totalLinksAfter = totalLinksBefore - len(paginasADejarDeApuntar)
        output = open(outputPath + "/cortando_enlaces_" + str(i) + ".txt", "w")
        output.write(str(totalNodesAfter) + "\n")
        output.write(str(totalLinksAfter) + "\n")
        for link in inputLinks:
            referencingPage = int((link.split(" "))[0])
            referencedPage = int((link.split(" "))[1])
            if referencingPage != c.cheaterPage or referencedPage not in (map(lambda tup: tup[0], paginasADejarDeApuntar)):
                output.write(link)

        output.close()

def generarTests():
    print("Generando tests")

    timeExperimentGraphSizes = [8, 16, 32, 64, 128, 256, 512, 1024]

    testCiclo()
    testEstrellaQueApunteAUnaPaginaQueNoApunteANadie()
    testEstrellaVsClique()
    testP()
    testGrafoRalo(timeExperimentGraphSizes)
    testGrafoControl(timeExperimentGraphSizes)
    testGrafoDenso(timeExperimentGraphSizes)
    testPaginaTramposaGrafoInicial()
    testPaginaTramposaEstrellaFantasma()
    testPaginaTramposaCliqueFantasma()
    testPaginaTramposaCortandoEnlacesDeSalida()

    print("Tests generados")

