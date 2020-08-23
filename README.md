# Trabalho Final Grafos

Relatório Trabalho Final de Algoritmos em Grafos:
Problema do delivery na Universidade

Bruna Santana Capeleti - 201720473 - 10A
Caio Gottmann Fernandes de Morais - 201910348 - 10A
Guilherme Henrique Pena Sousa - 201710836 - 14A

Motivação

Nossa ideia foi baseada em sistemas de entrega por aplicativo. Muitas vezes, ao comprar uma refeição, a mesma leva mais tempo do que o estimado para chegar, além de muitas vezes a comida não chegar quente o suficiente. Sabemos que isso pode ocorrer, pois, ao determinar a rota de entrega, pode haver um mau planejamento da mesma, de forma que o entregador gaste muito mais tempo do que o necessário para realizar todas as entregas, fazendo com que o produto muitas vezes perca um pouco de sua qualidade ou que leve mais tempo do que o desejado e previsto para chegar.

Sabemos também que, com os conhecimentos adquiridos na disciplina de “Algoritmos em Grafos”, podemos aplicar algoritmos que auxiliem em um melhor cálculo da rota, fazendo com que o entregador não perca muito tempo e os pedidos cheguem sempre em ordem e bem quentes.

Levamos em consideração também que muitos alunos e colaboradores da Universidade podem realizar pedidos enquanto estão em seu local de trabalho/estudo, visto que não existem muitas opções baratas e viáveis dentro do campus. Para isso, pensamos em modelar um problema para otimizar as entregas para os clientes, considerando os departamentos como pontos de entrega.

Definição Formal

Para resolver o problema descrito em nossa motivação, modelamos o algoritmo considerando que o restaurante e todos os departamentos onde as entregas devem ser realizadas são vértices, e as ruas que as ligam, arestas. Utilizamos Grafos Hamiltonianos, por meio do algoritmo de Dijkstra, onde o próximo vértice a ser visitado deve ser o que estiver mais próximo do vértice atual. Dessa forma, otimizamos as entregas, evitando que o entregador volte duas vezes ao mesmo ponto. Para também poupar o tempo do entregador depois que o último pedido for efetuado, calcularemos qual será o caminho mais rápido para que ele retorne ao restaurante, além da distância percorrida e do total de combustível gasto no processo.







Algoritmo

Grafo gerado no Jupyter para ilustrar a modelagem do problema:



Resultados Computacionais

Para nosso trabalho, estamos simulando um sistema de entregas para dentro da UFLA, visando que muitas vezes os estudantes não se sentem confortáveis com as opções disponíveis dentro da universidade. Dessa forma, realizamos a criação de pontos nos baseando em um mapa já existente da universidade disponível pela Google.
Em seguida, a fim de exemplificar, fizemos uma simulação no mapa da rota a ser percorrida a partir do restaurante até os departamentos onde os pedidos foram realizados.
No mapa, os pontos em amarelo são os locais de entrega e os locais em azul são pontos pertencentes à rota. 


(Mapa contendo os pontos de entrega)

Na imagem abaixo, os pedidos recebidos pelo restaurante foram dos seguintes pontos, nessa ordem:

10 - Hospital Veterinário
22 - Cantina
02 - PRPG
18 -  Departamento de Ciência da Computação

Também realizamos um comparativo entre os algoritmos de rota da Google e o desenvolvido por nós.


Rota padrão com o caminho pelo algoritmo da Google.

Rota do caminho com os pontos definidos executados pelo algoritmo da Google.

Com isso, conseguimos otimizar o caminho em 200 metros.


Rota desenvolvida pelo grupo já otimizada com base nos valores recebidos. 

Mapa disponível em: https://www.google.com/maps/d/edit?mid=1frap4rvB_tBPP0mZuwK_kqmQtg4er_7d&usp=sharing









Experimentos

As duas imagens de terminais abaixo ilustram os testes onde as entregas seriam realizadas nos pontos: 

10 - Hospital Veterinário
22 - Cantina
02 - PRPG
18 -  Departamento de Ciência da Computação


Print da página do compilador online: https://www.codechef.com/ide



No projeto entregue, inserimos apenas quatro valores para condizer com a capacidade de entrega do motoboy. Entretanto, também realizamos testes onde todos os vértices seriam visitados, a fim de verificar se a melhor rota continuaria sendo calculada. O resultado obtido foi:



Forças e Fraquezas

Como forças, podemos considerar que nosso algoritmo traz uma solução inovadora quando pensada no cenário em que se é aplicado. Atualmente é possível fazer pedidos de dentro da universidade, entretanto, muitas vezes ocorrem erros e falhas de comunicação acerca do local onde a entrega deve ser realizada. Dessa forma, acreditamos que nossa solução possa auxiliar a reduzir tais falhas, estabelecendo pontos de entrega mais claros e especificados. Entretanto, podemos considerar como uma fraqueza o fato de que ainda podem existir áreas da universidade que não são completamente cobertas pela solução, de maneira que em alguns casos, os clientes tenham que se deslocar até um dos pontos de entrega para receber o seu pedido.

Conclusão

De maneira geral, este estudo buscou encontrar uma solução para facilitar as entregas por delivery dentro da Universidade, estabelecendo pontos fixos por onde o entregador poderá se guiar. Dessa forma, ao receber os pedidos, o algoritmo retorna para o proprietário do estabelecimento qual a melhor rota a ser feita, bem como a distância e o valor de combustível gasto no processo. 

Entretanto, também identificamos que podem haver algumas falhas e gaps nos locais de entrega, visto que para uma primeira versão, trabalhamos com pontos de entrega fixos nos departamentos. Como um estudo futuro, pensamos que seria relevante buscar por formas de otimizar ainda mais as entregas e de identificar ainda mais a localização dos clientes, a fim de permitir que eles não tenham que se locomover até um dos pontos de entrega.

