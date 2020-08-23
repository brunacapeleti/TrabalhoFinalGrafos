/*
Trabalho Pratico - Algoritmos em Grafos

Bruna Santana Capeleti (10A);
Caio Gottmann Fernandes Morais (10A);
Guilherme Henrique Pena Sousa (14A);

Descricao do algoritmo: Utilizamos o algoritmo de Dijkstra para calcular a melhor rota de entrega bem como o valor de combustível gasto

*/

#include <iostream>
#include <list>	 //incluindo a biblioteca para utilização de uma lista
#include <queue> //incluindo a biblioteca para utilização de uma fila

#define INFINITO 10000000	// defindo nosso valor infinito
#define PRECO_GASOLINA 4.49 // definindo o preco atual da gasolina
#define KM_POR_LITRO 30		// definindo quantos km a moto faz por litro

using namespace std;

class Grafo // classe grafo
{
private:
	int V;					   // numero de vertices
	int *parent;			   // ponteiro de vetor para indicar quem sao os "parentes" de um vertice
	list<string> GPS;		   // lista armazenando o caminho a ser percorrido
	string *nomeRuas;		   // ponteiro para string com o nome das ruas
	list<pair<int, int>> *adj; // ponteiro para um array contendo as listas de adjacencias (informacoes do mapa)

public:
	Grafo(int V) // construtor
	{
		this->V = V;					   // atribui a quantidade de vertices
		parent = new int[V];			   // aloca espaco para armazenar os parentes
		nomeRuas = new string[V];		   // alocando espaco para armazenar o nome das ruas
		nomeRuas[0] = "Loja";			   // declarando que na primeira rua registrada se situa a loja
		adj = new list<pair<int, int>>[V]; // cria as listas onde cada lista e uma lista de pairs e onde cada pair e formado pelo vertice destino e o custo
	}

	void addAresta(int v1, int v2, int custo, string nomeRua) // adiciona uma aresta ao grafo de v1 a v2
	{
		adj[v1].push_back(make_pair(v2, custo));
		nomeRuas[v2] = nomeRua;
	}

	string getNomeRua(int v1) // retorna o nome da rua de um dado vertice
	{
		return nomeRuas[v1];
	}

	void caminho() // funcao para indicar qual caminho deve ser seguido
	{
		string rotaAux;
		for (auto it = GPS.begin(); it != GPS.end(); ++it) // percorre todo o vetor com as informacoes de localizacao
		{
			/*
                Verificando se um nome que ja foi escrito e diferente do proximo nome que sera impresso.
                Exemplo: 
                    antes:  loja - Av. Central UFLA - Av. Central UFLA - Computacao(PONTO DE ENTREGA)
                    depois: loja - Av. Central UFLA - Computacao(PONTO DE ENTREGA)
            */
			if (*it != rotaAux) // se nome da rua for diferente da rotaAux
			{
				cout << " - " << *it; // imprime "-" e o nome da rua
			}
			rotaAux = *it; // rotaAux recebe o nome da rua
		}
		cout << endl;
	}

	void constroiCaminho(int j, int pontoEntrega) // funcao para construir o caminho de entrega
	{
		if (parent[j] == -1) // se nao houver parente na posicao j
		{
			return;
		}

		// pontoEntrega representa o proximo ponto de entrega
		constroiCaminho(parent[j], pontoEntrega);						// chama a funcao recursivamente passando novos parametros
		if (nomeRuas[j] == nomeRuas[pontoEntrega] && pontoEntrega != 0) // se a rua na posicao j for igual a rua da proxima entrega e nao for a volta para a loja
		{
			string entrega = nomeRuas[j] + " (PONTO DE ENTREGA)"; // armazena o nome da rua e fala que e um ponto de entrega
			GPS.push_back(entrega);								  // adiciona o endereco na lista do GPS
		}
		else
		{
			GPS.push_back(nomeRuas[j]); // adiciona o nome da rua na lista do GPS
		}
	}

	int dijkstra(int origem, list<int> destino) // algoritmo de Dijkstra
	{
		int custoTotal = 0;
		int destinoAux;
		bool voltaLoja = false;
		cout << nomeRuas[0]; // imprime a origem, que nesse caso e a loja

		while (!destino.empty()) // enquanto houver destino
		{
			int menorCusto = INT16_MAX;

			int dist[V];	  // vetor de distâncias
			int visitados[V]; // vetor de visitados serve para caso o vertice ja tenha sido expandido (visitado), nao expandir mais

			priority_queue<pair<int, int>, // fila de prioridades de pair (distancia, vertice)
						   vector<pair<int, int>>, greater<pair<int, int>>>
				pq;

			for (int i = 0; i < V; i++) // inicializa o vetor de distancias e visitados
			{
				dist[i] = INFINITO;	  // definindo as distancias como infinito
				visitados[i] = false; // definindo que nenhum vertice foi visitado
			}
			parent[origem] = -1; // definindo que a origem nao possui nenhum parente
			dist[origem] = 0;	 // a distância de origem para origem e 0

			pq.push(make_pair(dist[origem], origem)); // insere na fila de prioridade

			while (!pq.empty()) // enquanto a fila de prioridade tiver elementos
			{
				pair<int, int> p = pq.top(); // extrai o pair do topo
				int u = p.second;			 // obtem o vertice do pair
				pq.pop();					 // remove o primeiro elemento da fila

				if (visitados[u] == false) // verifica se o vertice nao foi expandido
				{
					visitados[u] = true; // marca o vertice como visitado

					for (auto it = adj[u].begin(); it != adj[u].end(); it++) // percorre os vertices "v" adjacentes de "u"
					{
						// obtem o vertice adjacente e o custo da aresta
						int v = it->first;
						int custo_aresta = it->second;

						if (dist[v] > (dist[u] + custo_aresta)) // relaxamento (u, v)
						{
							dist[v] = dist[u] + custo_aresta; // atualiza a distancia de "v"
							pq.push(make_pair(dist[v], v));	  // insere v na fila
							parent[v] = u;					  // marca u como "parente" de v
						}
					}
				}
			}
			for (auto it = destino.begin(); it != destino.end(); ++it) // percorre a lista com os destinos
			{
				// buscando pelo menor caminho
				if (menorCusto > dist[*it])
				{
					menorCusto = dist[*it];
					destinoAux = *it;
				}
			}
			destino.remove(destinoAux);				 // remove o menor caminho ja visitado da lista de destinos
			origem = destinoAux;					 // a origem agora e o destino com o menor caminho
			constroiCaminho(destinoAux, destinoAux); // constroi o caminho
			custoTotal += menorCusto;				 // custo total recebe seu acumulado mais o peso do menor caminho
			if (destino.empty() && !voltaLoja)		 // se nao tiver mais destino e nao tiver voltado para a loja
			{
				destino.push_back(0); // adiciona a loja na lista de destinos
				voltaLoja = true;	  // marca que voltou para a loja
			}
		}
		return custoTotal; // retorna o custo total do caminho
	}
};

int main(int argc, char *argv[])
{
	Grafo grafo(57);

	/*
		utilizamos if(true) para permitir que na leitura do codigo os dados de localizacao sejam minimizados 
	*/
	if (true) // Dados da UFLA
	{
		grafo.addAresta(0, 1, 1400, "saida da reitoria");

		grafo.addAresta(1, 2, 150, "PRPG");
		grafo.addAresta(2, 1, 150, "saida da reitoria");
		grafo.addAresta(2, 12, 170, "Av. Central UFLA");

		grafo.addAresta(2, 3, 210, "Av. Sul UFLA");
		grafo.addAresta(3, 2, 210, "PRPG");
		grafo.addAresta(3, 14, 140, "Av. Central UFLA");

		grafo.addAresta(3, 4, 120, "Direito");
		grafo.addAresta(4, 3, 120, "Av. Sul UFLA");

		grafo.addAresta(4, 5, 40, "Av. Sul UFLA");
		grafo.addAresta(5, 4, 40, "Direito");
		grafo.addAresta(5, 19, 110, "Av. Central UFLA");

		grafo.addAresta(5, 6, 130, "Av. Sul UFLA");
		grafo.addAresta(6, 5, 130, "Av. Sul UFLA");
		grafo.addAresta(6, 37, 120, "Nutricao");

		grafo.addAresta(6, 7, 130, "Engenharia");
		grafo.addAresta(7, 6, 130, "Av. Sul UFLA");

		grafo.addAresta(7, 8, 130, "Av. Sul");
		grafo.addAresta(8, 7, 130, "Engenharia");
		grafo.addAresta(8, 41, 130, "Av. Centro/Sul UFLA");

		grafo.addAresta(8, 9, 130, "Av. Sul");
		grafo.addAresta(9, 8, 130, "Av. Sul");

		grafo.addAresta(9, 10, 35, "Hospital Veterinario");
		grafo.addAresta(10, 9, 35, "Av. Sul");

		grafo.addAresta(9, 11, 35, "Medicina Veterinario");
		grafo.addAresta(11, 9, 35, "Av. Sul");
		grafo.addAresta(11, 42, 80, "Av. Centro/Sul UFLA");

		grafo.addAresta(1, 12, 85, "Av. Central UFLA");
		grafo.addAresta(12, 28, 30, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(12, 13, 180, "Av. Central UFLA");
		grafo.addAresta(13, 3, 140, "Av. Sul UFLA");
		grafo.addAresta(13, 56, 20, "Av. Central UFLA");

		grafo.addAresta(56, 14, 20, "Av. Central UFLA");
		grafo.addAresta(56, 26, 30, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(14, 15, 35, "ADM");

		grafo.addAresta(15, 16, 75, "Av. Central UFLA");
		grafo.addAresta(16, 24, 30, "Matematica");

		grafo.addAresta(16, 17, 20, "Av. Central UFLA");

		grafo.addAresta(17, 18, 35, "COMP");

		grafo.addAresta(18, 19, 45, "Av. Central UFLA");
		grafo.addAresta(19, 5, 110, "Av. Sul UFLA");

		grafo.addAresta(19, 20, 40, "Quimica");
		grafo.addAresta(20, 23, 40, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(20, 21, 100, "Biblioteca");

		grafo.addAresta(21, 22, 20, "Cantina");
		grafo.addAresta(22, 21, 20, "Biblioteca");

		grafo.addAresta(22, 23, 125, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(23, 19, 35, "Av. Central UFLA");
		grafo.addAresta(23, 33, 170, "Av. Norte UFLA");

		grafo.addAresta(23, 24, 100, "Matematica");
		grafo.addAresta(24, 17, 30, "Av. Central UFLA");

		grafo.addAresta(24, 25, 85, "Humanas");

		grafo.addAresta(25, 26, 60, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(26, 13, 35, "Av. Central UFLA");
		grafo.addAresta(26, 31, 180, "Av. Norte UFLA");

		grafo.addAresta(26, 27, 45, "Biologia");

		grafo.addAresta(27, 28, 180, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(28, 30, 80, "Av. Norte UFLA");

		grafo.addAresta(28, 29, 80, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(29, 1, 30, "saida da reitoria");
		grafo.addAresta(29, 0, 1400, "Loja");

		grafo.addAresta(30, 28, 80, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(30, 31, 270, "Av. Norte UFLA");
		grafo.addAresta(31, 26, 180, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(31, 30, 270, "Av. Norte UFLA");
		grafo.addAresta(31, 33, 240, "Av. Norte UFLA");

		grafo.addAresta(32, 31, 200, "Av. Norte UFLA");

		grafo.addAresta(33, 32, 50, "Fisica");
		grafo.addAresta(33, 23, 175, "Av. Central UFLA");

		grafo.addAresta(33, 34, 90, "RU");

		grafo.addAresta(34, 35, 80, "Pavilhoes");
		grafo.addAresta(35, 33, 170, "Av. Norte UFLA");

		grafo.addAresta(21, 36, 70, "Av. Central UFLA");
		grafo.addAresta(36, 37, 40, "Nutricao");
		grafo.addAresta(36, 38, 40, "Av. Central UFLA");

		grafo.addAresta(37, 36, 40, "Av. Central UFLA");
		grafo.addAresta(37, 6, 120, "Av. Sul UFLA");

		grafo.addAresta(38, 39, 60, "Alimentos");
		grafo.addAresta(39, 38, 60, "Av. Central UFLA");

		grafo.addAresta(39, 40, 120, "Agricola");
		grafo.addAresta(40, 39, 120, "Alimentos");

		grafo.addAresta(40, 41, 35, "Av. Centro/Sul UFLA");
		grafo.addAresta(41, 40, 35, "Agricola");
		grafo.addAresta(41, 8, 130, "Av. Sul UFLA");

		grafo.addAresta(41, 42, 140, "Av. Centro/Sul UFLA");
		grafo.addAresta(42, 41, 140, "Av. Centro/Sul UFLA");
		grafo.addAresta(42, 11, 80, "Medicina Veterinaria");

		grafo.addAresta(42, 43, 30, "Zootecnia");
		grafo.addAresta(43, 42, 30, "Av. Centro/Sul UFLA");

		grafo.addAresta(38, 44, 20, "Av. Central UFLA");

		grafo.addAresta(44, 45, 400, "Av. Central UFLA");

		grafo.addAresta(45, 46, 160, "Inova Cafe");
		grafo.addAresta(45, 47, 30, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(46, 47, 150, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(47, 48, 300, "Av. Central UFLA (Sentido Centro)");
		grafo.addAresta(48, 49, 80, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(49, 22, 160, "Cantina");
		grafo.addAresta(49, 52, 170, "Av. Norte/Centro UFLA");

		grafo.addAresta(35, 50, 160, "Av. Norte UFLA");

		grafo.addAresta(50, 51, 50, "Lemaf");
		grafo.addAresta(51, 50, 50, "Av. Norte UFLA");

		grafo.addAresta(51, 52, 20, "Av. Norte/Centro UFLA");
		grafo.addAresta(52, 51, 20, "Lemaf");
		grafo.addAresta(52, 49, 170, "Av. Central UFLA (Sentido Centro)");

		grafo.addAresta(52, 53, 90, "Av. Norte/Centro UFLA");
		grafo.addAresta(53, 52, 90, "Av. Norte/Centro UFLA");

		grafo.addAresta(53, 54, 60, "Florestal");
		grafo.addAresta(54, 53, 60, "Av. Norte/Centro UFLA");

		grafo.addAresta(53, 55, 30, "Agricultura");
		grafo.addAresta(55, 53, 30, "Av. Norte/Centro UFLA");
		grafo.addAresta(55, 48, 80, "Av. Central UFLA (Sentido Centro)");
	}

	int localEntrega; // localEntrega referente ao numero de um ponto de entrega

	list<int> arrayPedidos; // lista para armazenar os pedidos

	for (int i = 1; i <= 4; i++) // loop para alocar pedidos para uma entrega ate que a capacidade seja atingida
	{
		cin >> localEntrega;
		cout << "Entrega marcada para: " << grafo.getNomeRua(localEntrega) << endl;
		arrayPedidos.push_back(localEntrega); // adiciona local de entrega ao vetor de pedidos

		/* Caso Teste Montado - Mostrado na Documentacao:
            arrayPedidos.push_back(10); // Medicina veterinaria
            arrayPedidos.push_back(22); // Cantina
            arrayPedidos.push_back(2);  // PRPG
            arrayPedidos.push_back(18); // Comp
        */
	}
	cout << endl;

	float custo = 0; // declarando a variavel custo
	cout << "Rota: ";
	cout << endl
		 << endl;

	custo = grafo.dijkstra(0, arrayPedidos); // custo recebe o valor retornado pela funcao dijkstra
	grafo.caminho();						 // chama a funcao que exibe o caminho

	cout << endl
		 << endl;

	std::cout.precision(3);																   // funcao para garantir tres casas de precisao apos a virgula
	cout << "Km percorridos = " << custo / 1000 << endl;								   // imprime a km percorrida
	float valor = (PRECO_GASOLINA * (custo / 1000) / KM_POR_LITRO) + 4;					   // variavel valor armazena o resultado do calculo do valor do combustivel com um acrescimo de 4 reais(comissao do motoboy)
	cout << "Valor da gasolina gasta no trajeto + Bonus de 4 reais = R$" << valor << endl; // imprime o valor de combustivel gasto para a entrega mais a comissao do entregador

	return 0;
}
