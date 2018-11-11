#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
//Função limpa tela
void cls(void){
    #ifdef WIN32
        system("CLS");
    #else
        system("clear");
    #endif // WIN32
}

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
typedef struct item tItem;
FILE *produtos;

//estrutura de carrinho de compras
typedef struct Icarrinho {
	//objeto do tipo item que esta nessa struct carrinho
	struct item pr;
	//quantidade de itens daqueles produto dentro do carrinho
	int quantidade;
};

//protoripo da função que irá mostrar ao cliente quanto ele já tem no carrinho
void precoAtual(/*struct item **/);

//função que irá cadastrar itens para a loja
void cadastrarItem(){
    int id,rec,resultado=0,cont=1, i=1;
    char nome[23];
    float preco;
    //Usuário informa os dados
    printf("Informe o nome do item: ");
    scanf("%s", &nome);
    setbuf(stdin,0);
    printf("Informe o preço o item: ");
    scanf("%f", &preco);

    // Abrindo o arquivo
    tItem produto;
    produtos = fopen("produtos.dat", "a+b");

    // Método para cálculo automático de ID
    for(i=0;i<30;i++){
    resultado = fread(&produto, sizeof(produto),1,produtos);
    if(resultado==1)
    cont++;
    }

    // Proibe mais que 30 produtos
    if(cont>30){
        cls();
        printf("Desculpe, está lotado.\n");
        return;
    }


    do{
    // Verifica se há conteúdo naquele trecho do disco
    resultado = fread(&produto, (i-1)*sizeof(produto),1,produtos);
    // Se não houver, insere o conteúdo passado pelo usuario
    if (resultado != 1){
    fseek(produtos, 0, SEEK_SET);
    strcpy(produto.nome, &nome);
    produto.ID = cont;
    produto.presso = preco;
    fwrite(&produto, sizeof(produto),1,produtos);
    fclose(produtos);
    return;
    }
    // Incrementa variável para caso retorne o loop
    i++;
    }while(resultado==1); // Loop dura enquanto houver conteúdo no arquivo
}

// Função mostra todos os produtos da loja
void lista(){
    // Abrindo arquivo
    tItem produto;
    produtos = fopen("produtos.dat", "r+b");

    //Verifica se é o fim do arquivo, enquanto for zero não é o fim
    while(feof(produtos)==0){
        // lê o arquivo para ver se o conteúdo já acabou
        fread(&produto, sizeof(produto),1,produtos);
        //Caso não tenha acabado, imprime o conteúdo
        if(feof(produtos)==0){
            printf("ID.......: %d\n", produto.ID);
            printf("Nome.....: %s\n", produto.nome);
            printf("Preço....: %.2f\n", produto.presso);
        }else{
        // No fim do arquivo, encerra-se o loop
        break;
        }}
    }


//função da loja
void loja();

//função de menu principal
void menu(struct item *prod, struct Icarrinho *car){
	//variavel de menu
	int escolha, ans;
do{
    cls();
	printf("\t=====JAC JOIAS=====\n");
	printf("\t1. Entrar na loja;\n\t2. \n\t3. Cadastrar item;\n\t4.  Carrinho de compras;\n\t5. Listar;\n\t6. Deletar item;\n\t7. Sair                ");
	scanf("%d", &escolha);
	//fzd tudo sumir
	cls();

	switch (escolha){
		//entrar na loja
		case 1:
		/*loja(prod, car);*/
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
        lista();
		break;

		case 6:
		break;

		default:
		printf("\t-----Muito obrigado volte sempre-----\n");
		return 0;
		break;
		escolha=NULL;
}
    printf("Deseja continuar? 1 para sim: ");
    setbuf(stdin,0);
    scanf("%d", &ans);
}while(ans==1);
}
//função do carrinho que irá incluir os produtos no vetor carrinho
void precoAtual(/*struct Icarrinho *carrinho*/){

}
/*
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
}*/

int main()
{
    //Português no windows né
    setlocale(LC_ALL," ");
	//vetor dos produtos da loja
	struct item produtos[MAX_PROD];
	//vetor do carrinho do cliente
	struct Icarrinho carrinho [MAX_PROD];
	menu(produtos, carrinho);
	return 0;
}
