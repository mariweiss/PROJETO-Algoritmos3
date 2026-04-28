/*
Mariana Bissaro Weiss, 2281
Layla Victória Sousa Teles, 2426
livia oliveira santos, 2290
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

using namespace std;

//função para limpar a tela
void limparTela(){
    system("cls");
}

// função para poder utilizar ESC
void esperarESC(){
    cout << "Pressione ESC para voltar ao menu..." << endl;
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
    cout << "=== INSERIR ITEM ===" << endl;
    
	inserirObj novo;// criei uma variavel do tipo da struct

	cout << "Nome do Item: " << endl;
	cin.ignore();
	getline(cin, novo.nomeItem);

	cout << "Nome do Dono: " << endl;
	getline(cin, novo.nomeDono);

	cout << "Propriedade mÃ¡gica do item: " << endl;
	getline(cin, novo.propMagica);

	cout << "ID: " << endl;
	cin >> novo.id;

	cout << "Raridade(0 a 100): " << endl;
	cin >> novo.raridade;

	itens.push_back(novo);// adicionei na minha lista de itens o meu novo item, eu adiciono o item no final da lista
	raiz = inserirABB(raiz, novo);

	cout << "Item adicionado!" << endl;
	
	esperarESC();
}

void cadastrarSimilaridades(){
	
	limparTela();
    cout << "=== CADASTRAR SIMILARIDADE ===" << endl;
    
	int id1, id2, s;
	cout << "Digite o ID do item 1: " << endl;
	cin >> id1;
	cout << "Digite o ID do item 2: " << endl;
	cin >> id2;
	cout << "Similaridade entre eles: " << endl;
	cin >> s;

	adj[id1].push_back( {id2, s}); // // aresta de id1 ? id2 com peso s
	adj[id2].push_back( {id1, s}); // se for um grafo nÃ£o orientado

	cout << "Similaridade cadastrada!" << endl;
	
	esperarESC();
}

void buscarItens(){
	limparTela();
	cout << "=== BUSCAR ITENS ===" << endl;

	int idC;
	double X;
	string jogadorJ;
	list<Aresta>::iterator it;
	list<inserirObj>::iterator it2;

	cout << "Digite o código do item:" << endl;
	cin >> idC;

	cout << "Digite o valor minimo de similaridade:" << endl;
	cin >> X;

	cout << "Digite o nome do jogador:" << endl;
	cin >> jogadorJ;

	bool encontrou = false;
	for(it = adj[idC].begin(); it != adj[idC].end(); it++){ // aqui ele percorre todos os vizinhos do item C,  porque na lista de adjacencia Ã© armazenado os vizinhos de cada id
		if(it->peso > X){ // verifica se a similaridade Ã© maior que X
			for(it2 = itens.begin(); it2 != itens.end(); it2++){ //aqui ele percorre a lista com os itens
				if(it2->id == it->destino && it2->nomeDono != jogadorJ){ //aqui ele verifica se o id do item Ã© igual o id do item que eu quero verificar
					cout << "ID: " << it2->id;
					cout << " | Nome: " << it2->nomeItem;
					cout << " | Dono: " << it2->nomeDono;
					cout << " | Similaridade: " << it->peso << endl;
					encontrou = true;
				}
			}
		}
	}

	if(!encontrou)
		cout<< "Item nao encontrado!" << endl;

	esperarESC();
}

void verificarItem(){
	
	limparTela();
    cout << "Funcionalidade em construcao" << endl;
    esperarESC();
}

void listarItemA(){  //listar item em ordem alfabÃ©tica

	limparTela();
    cout << "Funcionalidade em construcao" << endl;
    esperarESC();
}

void listarItemR(){  //listar itens em ordem decrescente de raridade
	limparTela();
    cout << "Funcionalidade em construcao" << endl;
    esperarESC();
}

void contarItens(){
	limparTela();
    cout << "Funcionalidade em construcao" << endl;
    esperarESC();
}

void remover(){  //remover itens menos raros
	limparTela();
    cout << "Funcionalidade em construcao" << endl;
    esperarESC();
}


int main (){

	setlocale(LC_ALL, "Portuguese");
//funÃ§Ã£o da biblioteca locale

	int opcao;
	do{
		limparTela();
		
		cout << "================== BOLSA DEVORADORA =================" << endl;
		cout << "| 1. Inserir item                                   |" << endl;
		cout << "| 2. Cadastrar similaridade entre itens;            |" << endl;
		cout << "| 3. Buscar itens similares;                        |" << endl;
		cout << "| 4. Verificar a existencia de um item;             |" << endl;
		cout << "| 5. Listar itens (ordem alfabetica de nome);       |" << endl;
		cout << "| 6. Listar itens (ordem decrescente de raridade)   |" << endl;
		cout << "| 7. Contar itens com mesma propriedade magica;     |" << endl;
		cout << "| 8. Remover itens menos raros;                     |" << endl;
		cout << "| 9. Sair                                           |" << endl;
		cout << "=====================================================" << endl;
		cout << "Escolha uma opcao: " << endl;
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
