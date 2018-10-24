#include <stdio.h>
#include <stdlib.h>


//função de menu principal
void menu(){
	//variavel de menu
	int escolha;

	printf("\t=====JAC JOIAS=====\n");
	printf("\t1. Calcular a nota;\n\t2. Incluir item;\n\t3. Editar item;\n\t4. Mostrar tudo;\n\t5. Buscar;\n\t6. Deletar item;\n");
	scanf("%d", &escolha);

	switch (escolha){

		case 1:
		precoAtual();
		break;
		case 2:
		printf("l2\n" );
		break;
		case 3:
		printf("l3\n");
		break;
		case 4:
		printf("l4\n" );
		break;
		default:
		break;
}
}
void precoAtual(){
}


int main()
{
	menu();
	return 0;
}
