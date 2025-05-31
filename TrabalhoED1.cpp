//////////////////////////////////////////////////////////////////////////////////////////////////////////
//																										//
//																										//
//			Nathanael Nunes				Felipe de Oliveira Barbosa				Vitor Lacerda			//
// 																										//
// 																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <conio2.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "TADFilaD.h"


TpPontTarefas LerArq(FILE *Arq, int cont){
	TpPontTarefas Tarefa;
	
	fscanf(Arq, " %[^,],%d,%[^\n]\n", &Tarefa.Tipo, &Tarefa.TempoExec, &Tarefa.Desc);
	Tarefa.TempoIn = cont;
	
	return Tarefa;
}


int main(){
	int linha = 7,coluna = 5; 
	srand(time(NULL));
	char *nomes[20] = {
	  "Estrela","Grow","Toyster","Bandeirante",
	  "Candide","Multibrink","Cotiplas","Cardoso Toys",
	  "Xalingo","Maral","Yes Toys","Mimo","Pais & Filhos","Zuca Toys",
	  "Simba Toys","Dican","DTC","New Toys","Baby Brink","Lider"
	};
	
	int cont = 0, tempoSimu, QtdeOp, i = 0;
	char opcao, nome[20];
	TpTempoMedio TempoM;
	TpDescOp DescOp;
	TpPontTarefas Tarefa;
	InicializarOp (DescOp);
	TpTarefasConc Conc;
	Conc.contNor = Conc.contOpc = Conc.contUrg = 0;
	TempoM.cNOR = TempoM.cOPC = TempoM.cURG = TempoM.TempoNor = TempoM.TempoOpc = TempoM.TempoUrg = 0;
	TpOperador *ExibirNome = new TpOperador;
	int x;
	Moldura(28,9,71,19,3,0,201,187,200,188);
	gotoxy(31,10);
	textcolor(13);
	printf("# # #  P R O G R A M A D O R E S  # # #");
	gotoxy(32,13);
	textcolor(2);
	printf("Felipe Barbosa");
	gotoxy(43,15);
	printf("Nathanael Nunes");
	gotoxy(54,17);
	printf("Vitor Lacerda");
	getch();
	InterfaceMenu();
	printf("### GERENCIADOR DE TAREFAS ###");
	//Moldura das perguntas
	Moldura(22,9,79,19,11,11,201,187,200,188);
	gotoxy(25,11);
	textcolor(5);
	printf("Qual sera o tempo de simulacao?");
	gotoxy(25,12);
	textcolor(2);
	scanf("%d", &tempoSimu);
	gotoxy(25,15);
	textcolor(5);
	printf("Quantos fabricantes (Operadores) terao na simulacao?");
	gotoxy(25,16);
	textcolor(2);
	scanf("%d", &QtdeOp);
	FILE *Arq = fopen("tarefas.txt", "r");

	while (QtdeOp <= 0 || i < QtdeOp){
		if(QtdeOp > 0 && QtdeOp <= 20){
		NovoOperador(DescOp, nomes[i]);
		i++;
		}
		else
			{
			clrscr();
			Moldura(22,9,79,19,8,7,201,187,200,188);
			gotoxy(25,11);
			textcolor(8);
			printf("Numero de Operadores insuficiente!");
			gotoxy(30,12);
			textcolor(4);
			printf("No minimo 1 e no maximo 20 para comecar");
			gotoxy(25,14);
			textcolor(8);
			printf("Quantos fabricantes (Operadores) terao na simulacao?");
			gotoxy(25,15);
			textcolor(2);
			scanf("%d", &QtdeOp);
			}
	}

	
	while(cont < tempoSimu){
	do{
		if(QtdeOp == 0){
			i = 0;
			while (QtdeOp <= 0 || i < QtdeOp){
				if(QtdeOp > 0 && QtdeOp <= 20){
					NovoOperador(DescOp, nomes[i]);
					i++;
				}
				else
				{
					clrscr();
					Moldura(22,9,79,19,8,7,30,30,31,31);
					gotoxy(25,11);
					textcolor(8);
					printf("Numero de Operadores insuficiente!");
					gotoxy(30,12);
					textcolor(4);
					printf("No minimo 1 e no maximo 20 para comecar");
					gotoxy(25,14);
					textcolor(8);
					printf("Quantos fabricantes (Operadores) terao na simulacao?");
					gotoxy(25,15);
					textcolor(2);
					scanf("%d", &QtdeOp);
				}
			}
		}
		clrscr();
		if(rand() % 2 == 0){
			
				Tarefa = LerArq(Arq, cont);
				NovaTarefa(DescOp, Tarefa, cont);	

		}
		
		InserirNoOp(DescOp, TempoM,cont);
		VerificarExecucao(DescOp, TempoM,Conc, cont); //Para verificar se o tempo de execução não foi concluido
		ExibirOps(DescOp.inicio,coluna,linha);
	
		Sleep(50);
		cont++;
	}while(!kbhit() && cont < tempoSimu);
	if(cont < tempoSimu)
	{
		gotoxy(coluna,linha++);
		textcolor(2);
		printf("Deseja Inserir (I) | Excluir (E) | Sair (S) | Voltar (ESC)");
		getch();
		opcao = toupper(getch());
		
		switch(opcao){
			case 'I':
				if(QtdeOp <20)
				{
					gotoxy(38,linha);
					textcolor(8);
					printf("Operador Inserido!");
					NovoOperador(DescOp, nomes[QtdeOp]);
					QtdeOp++;
					Sleep(400);
				}
				else
				{
					gotoxy(35,linha);
					textcolor(4);
					printf("Numero maximo de Operador atingindo");
					getch();
				}
				break;
			case 'E':
				clrscr();
				linha=10;
				Moldura(28,9,82,26,7,0,201,187,200,188);
				gotoxy(45,linha++);
				textcolor(13);
				printf("## Exclusao ##");
				gotoxy(35,++linha);
				textcolor(8);
				printf("Lista de Operadoracoes: ");
				gotoxy(30,++linha);
				textcolor(6);
				ExibirNome = DescOp.inicio;
				x=0;
				while(x<QtdeOp)
				{
					if(x%4==0 && x>=3)
						gotoxy(30,++linha);
					printf("%s | ",DescOp.inicio->nome);
					x++;
					DescOp.inicio = DescOp.inicio->prox;
				}
				DescOp.inicio = ExibirNome;
				linha++;
				gotoxy(30,++linha);
				textcolor(11);
				printf("Digite o nome do Operador que deseja excluir: ");
				gotoxy(30,++linha);
				textcolor(4);
				fflush(stdin);
				gets(nome);
				//mexer nele amanha
				Excluir(DescOp, nome, QtdeOp, linha);
				break;
			case 'S':
			
				gotoxy(25,linha++);
				textcolor(13);
				printf("# # #  S A I N D O  D A  S I M U L A C A O  # # #\n");
				cont = tempoSimu;
				Sleep(200);
				break;
				
			default:
				break;
				
		}
		}
	}
	//Tarefas concluidas
	InterfaceRelatorioInicio();
	linha=6;
	gotoxy(35,5);
	textcolor(13);
	printf("## RELATORIO DE TAREFAS CONCLUIDAS ##");
	InterfaceLateralRel(linha,7,0);
	ExibirNome = DescOp.inicio;
	x=0;
	while(x<QtdeOp)
	{
		gotoxy(27,++linha);
		textcolor(13);
		printf("Total Concluidas de %s : %d",DescOp.inicio->nome,(DescOp.inicio->Concluida.contUrg
		+DescOp.inicio->Concluida.contNor+DescOp.inicio->Concluida.contOpc));
		InterfaceLateralRel(linha,7,0);
		x++;
		DescOp.inicio = DescOp.inicio->prox;
	}
	gotoxy(34,++linha);
	textcolor(4);
	printf("Total Concluidas de cada tipo: ");
	InterfaceLateralRel(linha,7,0);
	gotoxy(27,++linha);
	textcolor(9);
	printf("Urgente -> ");
	textcolor(2);
	printf("%d",Conc.contUrg);
	InterfaceLateralRel(linha,7,0);
	textcolor(9);
	gotoxy(27,++linha);
	printf("Normal -> ");
	textcolor(2);
	printf("%d",Conc.contNor);
	InterfaceLateralRel(linha,7,0);
	textcolor(9);
	gotoxy(27,++linha);
	printf("Opcional -> ");
	textcolor(2);
	printf("%d",Conc.contOpc);
	InterfaceLateralRel(linha,7,0);
	DescOp.inicio = ExibirNome;
	InterfaceRelatorioFim(linha);
	getch();
	//Tempo medio de espera
	InterfaceRelatorioInicio();
	linha=6;
	gotoxy(38,5);
	textcolor(4);
	printf("## RELATORIO DE TEMPO MEDIO ##");
	InterfaceLateralRel(linha,7,0);


	float mediaUrg = 0, mediaNor = 0, mediaOpc = 0;

		gotoxy(27,++linha);
		textcolor(13);
		mediaUrg = (float) TempoM.TempoUrg/TempoM.cURG;
		mediaNor = (float) TempoM.TempoNor/TempoM.cNOR;
		mediaOpc = (float) TempoM.TempoOpc/TempoM.cOPC;

		textcolor(9);
		printf("Urgente -> ");
		textcolor(2);
		if(TempoM.cURG != 0)
			printf("%.2f",mediaUrg);
		else
			printf("Nenhuma Tarefa");
		textcolor(9);
		gotoxy(27,++linha);
		printf("Normal -> ");
		textcolor(2);
		if(TempoM.cNOR != 0)
			printf("%.2f",mediaNor);
		else
			printf("Nenhuma Tarefa");
		textcolor(9);
		gotoxy(27,++linha);
		printf("Opcional -> ");
		textcolor(2);
		if(TempoM.TempoOpc != 0)
			printf("%.2f",mediaOpc);
		else
			printf("Nenhuma Tarefa");
		InterfaceLateralRel(linha,7,0);


	
	InterfaceRelatorioFim(linha);
	getch();
	//Taferas não conluidas
	InterfaceRelatorioInicio();
	linha=6;
	gotoxy(32,5);
	textcolor(4);
	printf("## RELATORIO DE TAREFAS NAO CONCLUIDAS ##");
	InterfaceLateralRel(linha,7,0);
	ExibirNome = DescOp.inicio;
	x=0;
	while(x<QtdeOp)
	{
		if(DescOp.inicio->Status==1)
			DescOp.inicio->Qtde++;
		gotoxy(27,++linha);
		textcolor(13);
		printf("%s : ",DescOp.inicio->nome);
		textcolor(7);
		printf("%d",DescOp.inicio->Qtde);
		InterfaceLateralRel(linha,7,0);
		x++;
		DescOp.inicio = DescOp.inicio->prox;
	}
	DescOp.inicio = ExibirNome;
	
	InterfaceRelatorioFim(linha);
	getch();
	return 0;
}

