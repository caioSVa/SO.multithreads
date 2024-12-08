Simula um jogo de cartas, "21", entre threads. Cada thread tenta somar números aleatórios gerados entre 1 e 11, tentando atingir exatamente 21. Caso uma thread ultrapasse 21, ela "estoura", assim perdendo. O jogo termina assim que uma das threads atinge exatamente 21 ou quando todas as threads estouram, ou seja. A sincronização entre as threads é garantida através do uso de um mutex.

Para rodar: gcc -o so SO2.c -lpthread
            ./so
