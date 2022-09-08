import os
import config as c
import random


def generarCiclo(file, n):
    file.write(str(n) + "\n")
    file.write(str(n) + "\n")
    for page in range(1, n):
	    file.write(str(page) + " " + str(page + 1) + "\n")
    file.write(str(n) + " 1" + "\n")

def generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(file, n):
    file.write(str(n) + "\n")
    file.write(str(n - 1) + "\n")
    for page in range(1, n - 1):
        file.write(str(page) + " " + str(n - 1) + "\n")
    file.write(str(n - 1) + " " + str(n) + "\n")

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

def generarCaminoLargoParaTestearP(file, n):
    file.write(str(n) + "\n")
    file.write(str(n - 1) + "\n")
    for page in range(1, n):
        file.write(str(page) + " " + str(page + 1) + "\n")

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

def testCiclo(smallestSize, largestSize):
    print("Generando: Ciclo")

    path = "./ciclo"
    if not os.path.exists(path):
        os.makedirs(path)

    for i in range(smallestSize, largestSize + 1):
        output = open("./ciclo/ciclo_" + str(i) + ".txt", "w")
        generarCiclo(output, i)
        output.close()

def testEstrellaQueApunteAUnaPaginaQueNoApunteANadie(smallestSize, largestSize):
    print("Generando: Estrella que apunta a una pagina que no apunta a nadie")

    path = "./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie"
    if not os.path.exists(path):
        os.makedirs(path)

    for i in range(smallestSize, largestSize + 1):
        output = open(
            "./estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie/estrella_que_apunte_a_una_pagina_que_no_apunte_a_nadie_" + str(
                i) + ".txt", "w")
        generarEstrellaQueApunteAUnaPaginaQueNoApunteANadie(output, i)
        output.close()

def testEstrellaVsClique(smallestSize, largestSize):
    print("Generando: Estrella vs clique")

    path = "./estrella_vs_clique"
    if not os.path.exists(path):
        os.makedirs(path)

    pathClique = path + "/variando_clique"
    if not os.path.exists(pathClique):
        os.makedirs(pathClique)

    pathEstrella = path + "/variando_estrella"
    if not os.path.exists(pathEstrella):
        os.makedirs(pathEstrella)

    fixedN = 500

    #variando tamaño de la clique
    for i in range(smallestSize, largestSize + 1):
        output = open(pathClique + "/estrella_vs_clique_" + str(fixedN) + "_" + str(i) + ".txt", "w")
        generarEstrellaVsClique(output, fixedN, i)
        output.close()

    #variando tamaño de la estrella
    for i in range(smallestSize, largestSize + 1):
        output = open(pathEstrella + "/estrella_vs_clique_" + str(i) + "_" + str(fixedN) + ".txt", "w")
        generarEstrellaVsClique(output, i, fixedN)
        output.close()

def testCaminoLargoParaTestearP(smallestSize, largestSize):
    print("Generando: Camino largo para testear p")

    path = "./camino_largo_para_testear_p"
    if not os.path.exists(path):
        os.makedirs(path)

    for i in range(smallestSize, largestSize + 1):
        output = open("./camino_largo_para_testear_p/camino_largo_para_testear_p_" + str(i) + ".txt", "w")
        generarCaminoLargoParaTestearP(output, i)
        output.close()

def testGrafoRalo(smallestSize, largestSize):
    print("Generando: Grafo Ralo")

    path = "./grafo_ralo"
    if not os.path.exists(path):
        os.makedirs(path)

    for n in range(smallestSize, largestSize + 1):
        output = open(path + "/grafo_ralo_" + str(n) + ".txt", "w")
        generarGrafoRalo(output, n)
        output.close()

def testGrafoControl(smallestSize, largestSize):
    print("Generando: Grafo Control")

    path = "./grafo_control"
    if not os.path.exists(path):
        os.makedirs(path)

    for n in range(smallestSize, largestSize + 1):
        output = open(path + "/grafo_control_" + str(n) + ".txt", "w")
        generarGrafoControl(output, n)
        output.close()

def testGrafoDenso(smallestSize, largestSize):
    print("Generando: Grafo Denso")

    path = "./grafo_denso"
    if not os.path.exists(path):
        os.makedirs(path)

    for n in range(smallestSize, largestSize + 1):
        output = open(path + "/grafo_denso_" + str(n) + ".txt", "w")
        generarGrafoDenso(output, n)
        output.close()

def generarTests(smallestSize, largestSize):
    print("Generando tests")

    testCiclo(smallestSize, largestSize)
    testEstrellaQueApunteAUnaPaginaQueNoApunteANadie(smallestSize, largestSize)
    testEstrellaVsClique(smallestSize, largestSize)
    testCaminoLargoParaTestearP(smallestSize, largestSize)
    testGrafoRalo(smallestSize, largestSize)
    testGrafoControl(smallestSize, largestSize)
    testGrafoDenso(smallestSize, largestSize)

    print("Tests generados")

