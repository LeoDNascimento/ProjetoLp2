#include <stdio.h>
#include <stdlib.h>
//quantidade de produtos maxima na loja
#define MAX_PROD 30
//quantidade de produtos no Carrinho
int produtosNoCarrinho=0;
//numeros de produtos na loja
int nProduto=0;

//struct principal
typedef struct item {
	int ID;
	float presso;
	char nome[23];
};

//estrutura de carrinho de compras
typedef struct Icarrinho {
	//objeto do tipo item que esta nessa struct carrinho
	struct item pr;
	//quantidade de itens daqueles produto dentro do carrinho
	int quantidade;
};

//protoripo da função que irá mostrar ao cliente quanto ele já tem no carrinho
void precoAtual(struct item *);

//função que irá cadastrar itens para a loja
void cadastrarItem(struct item *);

//função da loja
void loja()

//função de menu principal
void menu(struct item *prod, struct Icarrinho *car){
	//variavel de menu
	int escolha;

	printf("\t=====JAC JOIAS=====\n");
	printf("\t1. Entrar na loja;\n\t2. \n\t3. Cadastrar item;\n\t4.  Carrinho de compras;\n\t5. Buscar;\n\t6. Deletar item;\n\t7. Sair");
	scanf("%d", &escolha);
	//fzd tudo sumir
	system("clear");

	switch (escolha){
		//entrar na loja
		case 1:
		loja(prod, car);
		break;

		//
		case 2:

		break;

		//Cadastrar item
		case 3:
		cadastrarItem(prod);
		break;

		//carrinho de compras
		case 4:
		precoAtual(car);
		break;

		case 5:

		break;

		case 6:
		break;

		default:
		printf("\t-----Muito obrigado volte sempre-----\n", );
		break;
		escolha=NULL;
}
}
//função do carrinho que irá incluir os produtos no vetor carrinho
void precoAtual(struct Icarrinho *carrinho){

}

//função que cadastra produtos que serão incluidos no inventario e vendidos na loja
void cadastrarItem(struct item *produtos){
	//se cadastrar mais que a quantidade do inventario não será possivel cadastrar mais
	if(nProduto == MAX_PROD){
		printf("Esta lotado.\n");
		return;
	}
	//cadastrando o ID do item
	printf("Inclua o numero de cadastro do item:\n" );
	scanf("%d", &produtos[nProduto].ID);
	//nome do produto, colocar o tipo de item no inicil
	//ia criar uma variavel para tipo mas fiquei com preguiça :3
	printf("Inclua o nome do item:\n" );
	scanf("%22[^\n]", produtos[nProduto].nome);
	//limpando o buffer de levis
	setbuf(stdin, NULL);
	//colocando o \0 no final para não dar merda
	produtos[nProduto].nome[22] = '\0';
	//preço do produto
	printf("Inclua o preco do item:\n" );
	scanf("%f", &produtos[nProduto].presso);

	nProduto++;
}

int main()
{
	//vetor dos produtos da loja
	struct item produtos[MAX_PROD];
	//vetor do carrinho do cliente
	struct Icarrinho carrinho [MAX_PROD];
	menu(produtos, carrinho);
	return 0;
}
