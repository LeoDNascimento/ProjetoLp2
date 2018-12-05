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

//struct principal
typedef struct item {
    int ID;
    float presso;
    char nome[23];
};
typedef struct item item;

FILE *produtos;
FILE *notaFiscal;
FILE *prods;

//Loja
int loja (struct item *prod, struct item *carroAtual){
	int nItens=0, utility=1, produtosNoCarrinho=0;
	struct item lista[100];
	item produto;
	produtos = fopen("produtos.dat", "r+b");

	//Verifica se é o fim do arquivo, enquanto for zero não é o fim
	while(feof(produtos)==0){
			// lê o arquivo para ver se o conteúdo já acabou
			fread(&produto, sizeof(produto),1,produtos);
			//Caso não tenha acabado, imprime o conteúdo
			if(feof(produtos)==0 && produto.ID!=0){
					printf("\tID.......: %d\n", produto.ID);
					printf("\tNome.....: %s\n", produto.nome);
					printf("\tPreço....: %.2f\n\n", produto.presso);
				  lista[nItens].ID=produto.ID;
					strcpy(lista[nItens].nome, produto.nome);
					lista[nItens].presso=produto.presso;
					nItens++;
			}else{
			// No fim do arquivo, encerra-se o loop
			break;
			}}
//---------------------------------------------------------------------------
while (utility>=0){
	printf("\tInforme o ID do item que deseja adquirir:\n\t0 se querer encerrar.\n");
	scanf("%d", &utility);
	if(utility<=0){
		break;
		}
		else{
		strcpy(carroAtual[produtosNoCarrinho].nome, lista[utility-1].nome);
    printf("Nome: %s\n", carroAtual[produtosNoCarrinho].nome);
		carroAtual[produtosNoCarrinho].presso=lista[utility-1].presso;
    printf("presso: %f\n", carroAtual[produtosNoCarrinho].presso);
    produtosNoCarrinho++;
		}
	}
return produtosNoCarrinho;
}

//cria o arquivo que será a nota fiscal
void notaf(struct item *prod, struct item *carroAtual, int nItem){
  int resultado, i, pressoaux[50], pressoTotal = 0;
  	item produto;
      notaFiscal = fopen("nota.txt", "w");
      fprintf(notaFiscal, "\t---------NOTA FISCAL---------\n");
      for(i=0;i<nItem;i++){
              fprintf(notaFiscal, "\t%s", carroAtual[i].nome);
              fprintf(notaFiscal, "\t%2.f\n", carroAtual[i].presso);

          pressoTotal += carroAtual[i].presso;
      }
      fprintf(notaFiscal, "\tPreço total: %d", pressoTotal);
      fclose(notaFiscal);
      printf("\tSua nota foi gerada com sucesso\n");
      return;

    return;
}
//busca itens cadastrados
//done
void busca(){
    int id, check;

    // Usuário informa o ID
    printf("\tInforme o ID do produto: ");
    scanf("%d", &id);

    // Inicializando arquivo
    item produto;
    produtos = fopen("produtos.dat", "rb");

    //Processo de impressão dos dados sobre o produto desejado
    check = fread(&produto, id*sizeof(produto),1,produtos);
    if(check==1){
        printf("\tO nome do produto é: %s\n", produto.nome);
        printf("\tO produto custa R$%.2f\n", produto.presso);
    }else{
        printf("\tNão existe produto com tal ID\n");
    }
    fclose(produtos);
    return;
}

//função que irá cadastrar itens para a loja
void cadastrarItem(){
    int id,rec,resultado=0,cont=1, i=0;
    char nome[23];
    float preco;
    //Usuário informa os dados
    printf("\tInforme o nome do item: ");
		scanf("%50[^\n]", &nome);
    setbuf(stdin,0);
    printf("\tInforme o preço o item: ");
    scanf("%f", &preco);

    // Abrindo o arquivo
    item produto;
    produtos = fopen("produtos.dat", "a+b");
		prods = fopen("prods.txt", "wf");

    // Método para cálculo automático de ID
    for(i=0;i<MAX_PROD;i++){
    resultado = fread(&produto, sizeof(produto),1,produtos);
    if(resultado==1)
    cont++;
    }

    // Proibe mais que 30 produtos
    if(cont>MAX_PROD){
        cls();
        printf("Desculpe, está lotado.\n");
        return;
    }


    do{
    // Verifica se há conteúdo naquele trecho do disco
    resultado = fread(&produto, i*sizeof(produto),1,produtos);
    // Se não houver, insere o conteúdo passado pelo usuario
    if (resultado != 1 || produto.ID == 0){
    fseek(produtos, 0, SEEK_SET);
    strcpy(produto.nome, &nome);
    produto.ID = cont;
    produto.presso = preco;
    fwrite(&produto, sizeof(produto),1,produtos);
		fprintf(prods, "ID: %d\n", cont);
		fprintf(prods, "Nome: %s\n", nome);
		fprintf(prods, "Preço: %2.f\n", preco);
		fclose(prods);
    fclose(produtos);
    return;
    }
    // Incrementa variável para caso retorne o loop
    i++;
    }while(resultado==1); // Loop dura enquanto houver conteúdo no arquivo
}

//Função apaga itens
void editarItem(){
	int id, ans=0;
	float newPresso;
	char newProduct[51];
	printf("\tInforme o ID do produto:\n");
	scanf("%d", &id);
	printf("\tInforme o novo nome:\n");
	setbuf(stdin, 0);
	scanf("%50[^\n]", &newProduct);

	printf("\tInforme o novo preço:\n");
	scanf("%f", &newPresso);

	// Abrindo o arquivo
	item produto;
	produtos = fopen("produtos.dat", "r+b");

ans=fread(&produto,id*sizeof(produto),1,produtos);
	if(ans==1){
		fseek(produtos,0, SEEK_SET);
		strcpy(produto.nome, &newProduct);
		produto.presso=newPresso;
		}
		else{
		printf("\tProduto não existe\n");}
		    fwrite(&produto, sizeof(produto),1,produtos);
fclose(produtos);
return;

		}

// Função mostra todos os produtos da loja
//done
void listar(){
	 // Abrindo arquivo
    item produto;
    produtos = fopen("produtos.dat", "r+b");

    //Verifica se é o fim do arquivo, enquanto for zero não é o fim
    while(feof(produtos)==0){
        // lê o arquivo para ver se o conteúdo já acabou
        fread(&produto, sizeof(produto),1,produtos);
        //Caso não tenha acabado, imprime o conteúdo
        if(feof(produtos)==0 && produto.ID!=0){
            printf("\tID.......: %d\n", produto.ID);
            printf("\tNome.....: %s\n", produto.nome);
            printf("\tPreco....: %.2f\n\n", produto.presso);
        }else{
        // No fim do arquivo, encerra-se o loop
        break;
        }}
    }


//função de menu principal
//done
void menu(struct item *prod, struct item *carAtual){
    setlocale(LC_ALL, " ");
    //variavel de menu
    int escolha, ans, nitens;
do{
    cls();
    printf("\t=====JAC JOIAS=====\n");
    printf("\t1. Loja;\n\t2. Buscar Item;\n\t3. Cadastrar item;\n\t4. Emitir nota fiscal;\n\t5. Listar;\n\t6. Editar item;\n\t7. Sair\n");
    scanf("%d", &escolha);
    setbuf(stdin,0);
    //fzd tudo sumir
    cls();

    switch (escolha){
        //entrar na loja
        case 1:
			//	loja(prod, carAtual);
        nitens = loja(prod, carAtual);

        break;

        //buscar itens
        case 2:
        busca();
        break;

        //Cadastrar item
        case 3:
        cadastrarItem(prod);
        break;

        //cria um arquivo que será a nota fiscal
        case 4:
        notaf(prod, carAtual, nitens);
        break;

				//mostra quais itens já tem cadastrados
        case 5:
        listar();
        break;

				//editar itens cadastrados
        case 6:
        editarItem();
        break;

        default:
        printf("\t-----Muito obrigado volte sempre-----\n");
        return;
        break;
        escolha=NULL;
}
    printf("\tDeseja continuar? 1 para sim: ");
    setbuf(stdin,0);
    scanf("%d", &ans);
}while(ans==1);
}

//main
//done
int main(){
    //Português no windows né
    setlocale(LC_ALL," ");
    //vetor dos produtos da loja
    struct item produtos[MAX_PROD];
    //vetor do carrinho do cliente
    //struct carrinho carAtual[50];
		struct item carAtual [50];
    menu(produtos, carAtual);
    return 0;
}
