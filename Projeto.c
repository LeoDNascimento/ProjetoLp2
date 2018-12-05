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

typedef struct carrinho{
  int quantidade;
	struct item prodNoCarrinho;
};

FILE *produtotxt;
FILE *produtos;
FILE *notaFiscal;

//Loja
void loja (struct item *prod, struct carrinho *carroAtual){
	int nItens=0, utility, produtosNoCarrinho=0, quantidade;
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
				  lista[nItens]=produto;
					nItens++;
			}else{
			// No fim do arquivo, encerra-se o loop
			break;
			}}
//---------------------------------------------------------------------------
do{
	printf("\tInforme o ID do item que deseja adquirir e sua quantidade:\n\t0 0 se querer encerrar.\n");
	scanf("%d %d", &utility, &quantidade);
	if(utility<nItens){
			carroAtual[produtosNoCarrinho].prodNoCarrinho.ID=lista[utility].ID;
			//carroAtual[produtosNoCarrinho].prodNoCarrinho.nome=lista[utility].nome;
			strcpy(lista[utility].nome, carroAtual[produtosNoCarrinho].prodNoCarrinho.nome);
			carroAtual[produtosNoCarrinho].prodNoCarrinho.presso=lista[utility].presso;
			carroAtual[produtosNoCarrinho].quantidade=quantidade;
		}
		else{	};
	}
while(utility>0);

fclose(produtos);

return;
}

//cria o arquivo que será a nota fiscal
void notaf(struct carrinho *carroAtual){
    int resultado, i, pressoaux[50], pressoTotal = 0;
	item produto;
    notaFiscal = fopen("nota.txt", "w");
    for(i=0;i<50;i++){
        pressoaux[i] = carroAtual[i].prodNoCarrinho.presso * carroAtual[i].quantidade;
        if(carroAtual[i].prodNoCarrinho.presso!=0 && carroAtual[i].prodNoCarrinho.presso>-21474836){
            fprintf(notaFiscal, "%s    ", carroAtual[i].prodNoCarrinho.nome);
            fprintf(notaFiscal, "%f\n", pressoaux[i]);
        }
        pressoTotal += pressoaux[i];
    }
    fprintf(notaFiscal, "Preço total: %d", pressoTotal);
    fclose(notaFiscal);
    printf("\tEssa boffta foi gerada com sucesso\n");
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
    produtotxt = fopen("produtos.txt", "a+");

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
    fclose(produtos);
    break;
    }
    // Incrementa variável para caso retorne o loop
    i++;
    }while(resultado==1); // Loop dura enquanto houver conteúdo no arquivo

        do{
    // Verifica se há conteúdo naquele trecho do disco
    resultado = fread(&produto, i*sizeof(produto),1,produtotxt);
    // Se não houver, insere o conteúdo passado pelo usuario
    if (resultado != 1 || produto.ID == 0){
    fseek(produtotxt, 0, SEEK_SET);
    fprintf(produtotxt, "%d\n", cont);
    fprintf(produtotxt, "%s\n", nome);
    fprintf(produtotxt, "%f\n", preco);
    fclose(produtotxt);
    return;
    }
    // Incrementa variável para caso retorne o loop
    i++;
    }while(resultado==1);
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
void menu(struct item *prod, struct carrinho *carAtual){
    setlocale(LC_ALL, " ");
    //variavel de menu
    int escolha, ans;
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
				loja(prod, carAtual);
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
            notaf(carAtual);
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
    struct carrinho carAtual[50];
    menu(produtos, carAtual);
    return 0;
}
