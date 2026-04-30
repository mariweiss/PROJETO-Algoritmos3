/*
Mariana Bissaro Weiss, 2281
Layla Victória Sousa Teles, 2426
Livia Oliveira Santos, 2290
Maria Clara Freitas Soares, 712
Miguel Borges Magalhães, 978
Ruan Carlo Martins Garcia,487
*/

#include <iostream>
#include <locale.h>
#include <list>
#include <string>
//biblioteca locale.h permite usar os caracteres da lingua portuguesa

#include <cstdlib>
#include <conio.h>
//bicliotecas para limpar o terminal e utilizar teclas especiais

#define RESET     "\033[0m"
#define VERDE     "\033[32m"
#define VERDE_ESC "\033[92m"  // verde mais brilhante
#define NEGRITO   "\033[1m"
//variaveis para decoracao do menu

using namespace std;

void centralizar(string texto, bool quebrarLinha = true){ //funcao que centraliza o texto
    int larguraTela = 80;
    int espacos = (larguraTela - texto.length()) / 2;

    for(int i = 0; i < espacos; i++)
        cout << " ";

    cout << texto;

    if(quebrarLinha)
        cout << endl;
}

//função para limpar a tela
void limparTela(){
    system("cls");
}

// função para poder utilizar ESC
void esperarESC(){
    cout << endl;
    cout << VERDE;

    centralizar("+-------------------------------------+");
    centralizar("Pressione ESC para voltar ao menu");
    centralizar("+-------------------------------------+");

    cout << RESET;
    char tecla;
    
    while(true){
        tecla = getch();
        if(tecla == 27) break;
    }
}

// para adicionar um novo item
struct inserirObj{
	string nomeItem, nomeDono, propMagica;
	int id, raridade; // raridade = numero de 0 a 100 onde 0=comum,100=rarÃ­ssimo
};

// Struct que representa uma aresta do grafo de similaridade
struct Aresta{
	int destino, peso; // nÃ£o precisa de origem pois o id do item ja nos dÃ¡ Ã  origem, destino = id do item relacionado, peso = valor de similaridade
};

struct No{
    inserirObj item;
    No* esq;
    No* dir;
};

list<Aresta> adj[1000];
No* raiz = NULL;
list<inserirObj> itens; // criei uma lista para adicionar os itens, cada posição da lista é um item

No* inserirABB(No* raiz, inserirObj novo){
    if(raiz == NULL){
        No* novoNo = new No;
        novoNo->item = novo;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
        return novoNo;
    }

    if(novo.id < raiz->item.id)
        raiz->esq = inserirABB(raiz->esq, novo);
    else if(novo.id > raiz->item.id)
        raiz->dir = inserirABB(raiz->dir, novo);

    return raiz;
}

No* buscarABB(No* raiz, int id){
    if(raiz == NULL || raiz->item.id == id)
        return raiz;

    if(id < raiz->item.id)
        return buscarABB(raiz->esq, id);
    else
        return buscarABB(raiz->dir, id);
}

void inserirItem(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|          >> INSERIR ITEM <<         |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    inserirObj novo;

    centralizar("Nome do Item: ", false);
    cin.ignore();
    getline(cin, novo.nomeItem);

    centralizar("Nome do Dono: ", false);
    getline(cin, novo.nomeDono);

    centralizar("Propriedade magica do item: ", false);
    getline(cin, novo.propMagica);

    centralizar("ID: ", false);
    cin >> novo.id;

    centralizar("Raridade (0 a 100): ", false);
    cin >> novo.raridade;

    itens.push_back(novo);
    raiz = inserirABB(raiz, novo);

	cout << VERDE << NEGRITO;
    centralizar("+-------------------------------------+");
    centralizar("|        >> Item adicionado! <<       |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;

    esperarESC();
}

void cadastrarSimilaridades(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> CADASTRAR SIMILARIDADE <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int id1, id2, s;
    centralizar("ID do item 1: ", false);
    cin >> id1;
    centralizar("ID do item 2: ", false);
    cin >> id2;
    centralizar("Similaridade entre eles: ", false);
    cin >> s;

    adj[id1].push_back({id2, s});
    adj[id2].push_back({id1, s});

    cout << endl;
    centralizar("+-------------------------------------+");
    centralizar("|    >> Similaridade cadastrada! <<   |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;

    esperarESC();
}

void buscarItens(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> BUSCAR ITENS SIMILARES <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE << endl;

    int idC;
    double X;
    string jogadorJ;
    list<Aresta>::iterator it;
    list<inserirObj>::iterator it2;

    centralizar("Codigo do item: ", false);
    cin >> idC;
    centralizar("Similaridade minima: ", false);
    cin >> X;
    centralizar("Nome do jogador: ", false);
    cin >> jogadorJ;

    cout << endl;
    centralizar("+-------------------------------------+");
    centralizar("|          >> RESULTADOS <<           |");
    centralizar("+-------------------------------------+");

    bool encontrou = false;
    for(it = adj[idC].begin(); it != adj[idC].end(); it++){
        if(it->peso > X){
            for(it2 = itens.begin(); it2 != itens.end(); it2++){
                if(it2->id == it->destino && it2->nomeDono != jogadorJ){
                    cout << "| ID: "         << it2->id       << endl;
                    cout << "| Nome: "       << it2->nomeItem << endl;
                    cout << "| Dono: "       << it2->nomeDono << endl;
                    cout << "| Similaridade: " << it->peso   << endl;
                    centralizar("+-------------------------------------+");
                    encontrou = true;
                }
            }
        }
    }

    if(!encontrou)
        centralizar("| >> Nenhum item encontrado! <<       |");

    cout << RESET << endl;
    esperarESC();
}

void verificarItem(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|        >> VERIFICAR ITEM <<         |");
    centralizar("+=====================================+");
    cout << RESET << VERDE;
    centralizar("| Funcionalidade em construcao...     |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;
    esperarESC();
}

void listarItemA(){ //listar item em ordem alfabÃ©tica
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      >> LISTAR (ALFABETICA) <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE;
    centralizar("| Funcionalidade em construcao...     |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;
    esperarESC();
}

void listarItemR(){ //listar itens em ordem decrescente de raridade
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|        >> LISTAR (RARIDADE) <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE;
    centralizar("| Funcionalidade em construcao...     |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;
    esperarESC();
}

void contarItens(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|     >> CONTAR POR PROPRIEDADE <<    |");
    centralizar("+=====================================+");
    cout << RESET << VERDE;
    centralizar("| Funcionalidade em construcao...     |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;
    esperarESC();
}

void remover(){
    limparTela();
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      >> REMOVER MENOS RAROS <<      |");
    centralizar("+=====================================+");
    cout << RESET << VERDE;
    centralizar("| Funcionalidade em construcao...     |");
    centralizar("+-------------------------------------+");
    cout << RESET << endl;
    esperarESC();
}


// cabecalho estilizado
void cabecalhoDecorado() {
    cout << VERDE << NEGRITO;
    centralizar("+=====================================+");
    centralizar("|      ***  BOLSA DEVORADORA  ***     |");
    centralizar("+=====================================+");
    cout << RESET << endl;
}


int main (){

	setlocale(LC_ALL, "Portuguese");
	//funÃ§Ã£o da biblioteca locale

	int opcao;
	do{
		limparTela();
		
		cabecalhoDecorado();

		cout << VERDE;
    	centralizar("+-------------------------------------+");
    	centralizar("|            -- ACOES --              |");
    	centralizar("+-------------------------------------+");
    	centralizar("¦  [1] >> Inserir item                ¦");
    	centralizar("¦  [2] >> Cadastrar similaridade      ¦");
    	centralizar("¦  [3] >> Buscar itens similares      ¦");
    	centralizar("¦  [4] >> Verificar existencia        ¦");
    	centralizar("¦  [5] >> Listar (alfabetica)         ¦");
    	centralizar("¦  [6] >> Listar (raridade)           ¦");
    	centralizar("¦  [7] >> Contar por propriedade      ¦");
    	centralizar("¦  [8] >> Remover menos raros         ¦");
    	centralizar("¦  [9] >> Sair                        ¦");
    	centralizar("+-------------------------------------+");
    	cout << RESET << endl;

		centralizar("Escolha uma opcao: ", false);
		cin >> opcao;


		switch (opcao){
		case 1:
			inserirItem();
			break;
		case 2:
			cadastrarSimilaridades();
			break;
		case 3:
			buscarItens();
			break;
		case 4:
			verificarItem();
			break;
		case 5:
			listarItemA();
			break;
		case 6:
			listarItemR();
			break;
		case 7:
			contarItens();
			break;
		case 8:
			remover();
			break;
		case 9:
			cout << "Saindo..." << endl;
			break;
		}
	}
	while(opcao != 9);


	return 0;
}
