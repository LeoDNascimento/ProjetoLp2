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
typedef struct item item;

//struct do carrinho
typedef struct car{
    int preco[30];
    char produto[30][23];
    int precototal;
};
typedef struct car car;


FILE *produtos;
FILE *carrinho;

void addcar(){
    int id, n, resultado = 0;
    car cart;
    item produto;

    //Usuário informa os dados
    printf("\tInsira o id do produto: ");
    scanf("%d", &id);
    printf("\tInsira a quantidade do produto: ");
    scanf("%d", &n);

    //Abrindo os arquivos
    carrinho = fopen("carrinho.dat", "wb");
    produtos = fopen("produtos.dat", "rb");

        // Verifica se há conteúdo naquele trecho do disco
        resultado = fread(&produto, id*sizeof(produto),1,produtos);
        if(resultado==1){
        fseek(produtos,id*sizeof(produto),SEEK_SET);
        fseek(carrinho,0,SEEK_SET);
        cart.preco[id-1] = produto.presso;
        strcpy(cart.produto[id-1], &produto.nome);
        printf("\n\n%s", cart.produto[id-1]);
        cart.precototal = 0;
        cart.precototal = cart.precototal + n*produto.presso;
        fwrite(&cart, sizeof(cart),1,carrinho);
        }else{
            printf("\tProduto nao existe\n");
        }
    fclose(carrinho);



}

void rmcar(){

}

//estrutura de carrinho de compras
void fCarrinho(){
        int i;

        car cart;

        produtos = fopen("produtos.dat", "r+b");
        carrinho = fopen("carrinho.dat", "rb");

        fread(&cart, sizeof(cart),1,carrinho);
        //Caso não tenha acabado, imprime o conteúdo
        if(feof(carrinho)==0){
            printf("\tPreco.......: %d\n", cart.preco[2]);
            printf("\tNome.....: %s\n", cart.produto[2]);
            printf("\tPreco Total....: %.2d\n\n", cart.precototal);
        }else{
            printf("\tCarrinho vazio\n");
        }
};

//protoripo da função que irá mostrar ao cliente quanto ele já tem no carrinho
void precoAtual(/*struct item **/);

//função que irá cadastrar itens para a loja
void cadastrarItem(){
    int id,rec,resultado=0,cont=1, i=1;
    char nome[23];
    float preco;
    //Usuário informa os dados
    printf("\tInforme o nome do item: ");
    scanf("%s", &nome);
    setbuf(stdin,0);
    printf("\tInforme o preço o item: ");
    scanf("%f", &preco);

    // Abrindo o arquivo
    item produto;
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

//Função apaga itens
void deletarItem(){
    int i,id, resultado;
    char null = '\0';
    cls();
    printf("\tInforme o ID do produto: ");
    scanf("%d", &id);

    item produto;
    produtos = fopen("produtos.dat", "a+b");

    resultado = fread(&produto, id*sizeof(produto),1,produtos);
    if(resultado==1)
    {
        fseek(produtos, id*sizeof(produto), SEEK_SET);
        strcpy(produto.nome, "\0");
        produto.ID = 0;
        produto.presso = 0;
        fwrite(&produto,sizeof(produto),1,produtos);
        fclose(produtos);
    }else{
        printf("\tProduto nao existe\n");
    }


    return;
}

// Função mostra todos os produtos da loja
void lista(){    // Abrindo arquivo
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


//função da loja
void loja(){
    int ans;
    cls();
    printf("\t=======LOJA========\n");
    printf("\t1. Adicionar produto ao carrinho;\n\t2. Tirar produto do carrinho;     ");
    scanf("%d", &ans);
    switch(ans){
        case 1:
            addcar();
            break;
        case 2:
            //rmcar();
            break;
        default:
            printf("\tOpcao invalida\n\n");
    }
}
//função de menu principal
void menu(struct item *prod, struct Icarrinho *car){
    setlocale(LC_ALL, " ");
    //variavel de menu
    int escolha, ans;
do{
    cls();
    printf("\t=====JAC JOIAS=====\n");
    printf("\t1. Entrar na loja;\n\t2. Buscar Item\n\t3. Cadastrar item;\n\t4. Carrinho de compras;\n\t5. Listar;\n\t6. Deletar item;\n\t7. Sair                ");
    scanf("%d", &escolha);
    //fzd tudo sumir
    cls();

    switch (escolha){
        //entrar na loja
        case 1:
        loja();
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
        fCarrinho();
        break;
        break;

        case 5:
        lista();
        break;

        case 6:
        deletarItem();
        break;

        default:
        printf("\t-----Muito obrigado volte sempre-----\n");
        return 0;
        break;
        escolha=NULL;
}
    printf("\tDeseja continuar? 1 para sim: ");
    setbuf(stdin,0);
    scanf("%d", &ans);
}while(ans==1);
}

//função do carrinho que irá incluir os produtos no vetor carrinho
void precoAtual(/*struct Icarrinho *carrinho*/){

}

int main()
{
    //Português no windows né
    setlocale(LC_ALL," ");
    //vetor dos produtos da loja
    struct item produtos[MAX_PROD];
    //vetor do carrinho do cliente
//    struct Icarrinho carrinho [MAX_PROD];
    menu(produtos, carrinho);
    return 0;
}
