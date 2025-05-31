
// **Structs**

//Lista de tarefas
struct TpPontTarefas
{
	TpPontTarefas *prox, *ant;
	char Tipo[10], Desc[50];
	int TempoIn, TempoOut, TempoExec;
	int contExc;
};

struct TpDescTarefa
{
	TpPontTarefas *inicio, *fim;
};

struct TpTarefasConc
{
	int contUrg, contNor, contOpc;
};

struct TpTempoMedio
{
	int TempoUrg,TempoNor,TempoOpc,cURG, cNOR, cOPC;
};

//Lista de Operadores
struct TpOperador
{
	TpOperador *prox;
	TpDescTarefa *DescTarefas;
	TpPontTarefas TarefaAtual;
	int Qtde, Status;
	TpTarefasConc Concluida;
	char nome[20];
};

struct TpDescOp
{
	TpOperador *inicio, *fim;		
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// **Prototipos**

//Molduras
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF,int SupE,int SupD,int InfE,int InfD);
void InterfaceMenu(void);
void InterfaceOperacoes(void);
void InterfaceLateral(int linha,int corT,int corF);

//Inicializadores
void InicializarLT(TpDescTarefa *DescT);
void InicializarOp (TpDescOp &Desc);

//Buscas
TpOperador *BuscaMenorQtde (TpOperador *Operador, TpOperador *menor);
TpOperador *BuscaMenorQtdeEXCLUSAOOP (TpOperador *Operador, TpOperador *menor, TpOperador *atual);
TpPontTarefas *BuscaPrioridade (TpPontTarefas *Desc, TpPontTarefas Tarefa);
TpPontTarefas *BuscaPrioridadeComPonteiro(TpPontTarefas *Desc, TpPontTarefas *NovaTarefa);

//Exibições
void ExibirOps(TpOperador *Op, int &coluna, int &linha);
void ExibirTarefas(TpOperador *ListaOp, int &coluna, int &linha);
void ExibirTarefaAtual(TpPontTarefas TarefaAtual);

//Verificadores
int TipoTarefa (char Tipo[]);
void VerificarExecucao(TpDescOp &DescOp , int cont);

//Inserções e afins
void NovaTarefa (TpDescOp &DescOp, TpPontTarefas Tarefa, int cont);
void DistribuirTarefa (TpDescOp &DescOp, TpPontTarefas *pTarefa, TpOperador *atual);
void NovoOperador (TpDescOp &DescOp, char nomeOp[]);
void InserirNoOp(TpDescOp &DescOp , int cont);

//Liberacoes
void LiberarListaTarefas(TpPontTarefas *ListaTarefa);
void LiberarListaOperadores(TpOperador *ListaOp);
void Excluir(TpDescOp &DescOp, char nome[], int &QtdeOp, int &linha);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// **Operações**

//Molduras
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF,int SupE,int SupD,int InfE,int InfD)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",SupE);
	gotoxy(CI,LF);
	printf("%c",InfE);
	gotoxy(CF,LI);
	printf("%c",SupD);
	gotoxy(CF,LF);
	printf("%c",InfD);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI);
		printf("%c",205); 
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void InterfaceMenu(void)
{
	clrscr();
	//valores: (CL,LI,CF,LF,CorT,CorF,SupE,SupD,InfE,InfD)
	Moldura(1,1,106,30,0,15,201,187,200,188);
	//Titulo 
	Moldura(1,5,106,30,0,15,204,185,200,188); 
	textcolor(8);
	gotoxy(35,3);
	
}

void InterfaceOperacoes(void)
{
	clrscr();
	//valores: (CL,LI,CF,LF,CorT,CorF,SupE,SupD,InfE,InfD)
	Moldura(1,1,106,5,0,1,201,187,204,185);
	gotoxy(35,3);
}

void InterfaceLateral(int linha,int corT,int corF)
{
	for(int l=linha-1;l<=linha+4;l++)
	{
		textcolor(corT);
		textbackground(corF);
		gotoxy(1,l);
		printf("%c",186);
		gotoxy(106,l);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void InterfaceLateralRel(int linha,int corT,int corF)
{
	for(int l=linha-1;l<=linha+1;l++)
	{
		textcolor(corT);
		textbackground(corF);
		gotoxy(25,l);
		printf("%c",186);
		gotoxy(90,l);
		printf("%c",186);
	}
	textcolor(7);
	textbackground(0);
}

void InterfaceRelatorioInicio(void)
{
	clrscr();
	textcolor(7);
	gotoxy(25,4);
	printf("%c",201);
	gotoxy(90,4);
	printf("%c",187);
	for(int c=26; c<90; c++)
	{ 
		gotoxy(c,4);
		printf("%c",205);
	}
}

void InterfaceRelatorioFim(int linha)
{
	textcolor(7);
	textbackground(0);
	gotoxy(25,linha+2);
	printf("%c",200);
	gotoxy(90,linha+2);
	printf("%c",188);
	for(int c=26; c<90; c++)
	{ 
		gotoxy(c,linha+2);
		printf("%c",205);
	}
	textbackground(0);
}

//Inicializações
void InicializarLT(TpDescTarefa *DescT)
{
	DescT -> inicio = DescT -> fim = NULL;
}

void InicializarOp (TpDescOp &DescOp)
{

	DescOp.inicio = NULL;
	DescOp.fim = NULL;

}

//Definição de prioridade
int TipoTarefa (char Tipo[]){
	if(strcmp(Tipo, "Urgente") == 0)
		return 3;
	else if (strcmp(Tipo, "Normal") == 0)
			return 2;
			
		else
			return 1;
}

//Busca Recursiva pela MENOR Qtde
TpOperador *BuscaMenorQtde (TpOperador *Operador, TpOperador *menor){
	if(Operador -> prox != NULL){
		if(Operador -> Qtde < menor -> Qtde)
			menor = Operador;
		return BuscaMenorQtde(Operador -> prox, menor);
	}
	
	//Verifica o último também
	if (Operador->Qtde < menor->Qtde)
        menor = Operador;


	return menor;
}

//Busca MENOR Qtde exceto o do Operador mandado por parâmetro(*atual)
TpOperador *BuscaMenorQtdeEXCLUSAOOP (TpOperador *Operador, TpOperador *menor, TpOperador *atual){
	if(Operador -> prox != NULL){
		if(Operador -> Qtde < menor -> Qtde && Operador != atual)
			menor = Operador;
		return BuscaMenorQtdeEXCLUSAOOP(Operador -> prox, menor,atual);
	}
	
	//Verifica o último também
	if (Operador->Qtde < menor->Qtde && Operador != atual)
        menor = Operador;


	return menor;
}


TpPontTarefas *BuscaPrioridade(TpPontTarefas *Desc, TpPontTarefas NovaTarefa){
	if(Desc -> prox != NULL)
		if(TipoTarefa(Desc -> Tipo) > TipoTarefa(NovaTarefa.Tipo))
			return BuscaPrioridade(Desc -> prox, NovaTarefa);
	
	return Desc;
}

TpPontTarefas *BuscaPrioridadeComPonteiro(TpPontTarefas *Desc, TpPontTarefas *NovaTarefa){
	if(Desc -> prox != NULL)
		if(TipoTarefa(Desc -> Tipo) > TipoTarefa(NovaTarefa -> Tipo))
			return BuscaPrioridadeComPonteiro(Desc -> prox, NovaTarefa);
	
	return Desc;
}


//Inserções
void NovaTarefa (TpDescOp &DescOp, TpPontTarefas Tarefa, int cont){
	//Deve ser inserida na Fila com MENOR número dos Operadores
	
	TpPontTarefas *pTarefa = new TpPontTarefas;
	strcpy(pTarefa -> Tipo, Tarefa.Tipo);
	strcpy(pTarefa -> Desc, Tarefa.Desc);
	pTarefa -> TempoExec = Tarefa.TempoExec;
	pTarefa -> TempoIn = cont;
	pTarefa -> prox = pTarefa -> ant = NULL;
	
	TpOperador *Menor = BuscaMenorQtde(DescOp.inicio, DescOp.inicio);
	
	if(Menor -> DescTarefas -> inicio == NULL){
		Menor -> DescTarefas -> inicio = Menor -> DescTarefas -> fim = pTarefa;
	}
	else{
		if(TipoTarefa(Menor -> DescTarefas -> inicio -> Tipo) <= TipoTarefa(pTarefa -> Tipo))
			{
				Menor -> DescTarefas -> inicio -> ant = pTarefa;
				pTarefa -> prox = Menor -> DescTarefas -> inicio;
				Menor -> DescTarefas -> inicio = pTarefa;	
			}
			else
				if(TipoTarefa(Menor -> DescTarefas -> inicio -> Tipo) == TipoTarefa(pTarefa -> Tipo))
				{
					pTarefa -> ant = Menor -> DescTarefas -> inicio;
					Menor -> DescTarefas -> inicio -> prox -> ant = pTarefa;
					pTarefa -> prox = Menor -> DescTarefas -> inicio -> prox;
					Menor -> DescTarefas -> inicio -> prox = pTarefa;	
				}
				else if(TipoTarefa(Menor -> DescTarefas -> fim -> Tipo) >= TipoTarefa(pTarefa -> Tipo))
						{
							pTarefa -> ant = Menor -> DescTarefas -> fim;
							Menor -> DescTarefas -> fim -> prox = pTarefa;
							Menor -> DescTarefas -> fim = pTarefa;
						}
						else
							{
								TpPontTarefas *atual = BuscaPrioridade(Menor -> DescTarefas -> inicio, Tarefa);
								pTarefa -> ant = atual -> ant;
								atual -> ant -> prox = pTarefa;
								pTarefa -> prox = atual;
								atual -> ant = pTarefa;
									
							}
	}
	Menor -> Qtde++;
}


//Distribuir a tarefa quando é retirada de um Operador Excluido
void DistribuirTarefa (TpDescOp &DescOp, TpPontTarefas *pTarefa, TpOperador *atual){
	//Deve ser inserida na Fila com MENOR número dos Operadores
	
	pTarefa -> prox = pTarefa -> ant = NULL;
	TpOperador *OpInicial = DescOp.inicio;
	TpOperador *OpAtual = atual;
	TpOperador *Menor = BuscaMenorQtdeEXCLUSAOOP(OpInicial, OpInicial, OpAtual);
		if(Menor -> DescTarefas -> inicio == NULL){
			Menor -> DescTarefas -> inicio = Menor -> DescTarefas -> fim = pTarefa;
		}
		else{
			if(TipoTarefa(Menor -> DescTarefas -> inicio -> Tipo) <= TipoTarefa(pTarefa -> Tipo))
				{
					Menor -> DescTarefas -> inicio -> ant = pTarefa;
					pTarefa -> prox = Menor -> DescTarefas -> inicio;
					Menor -> DescTarefas -> inicio = pTarefa;	
				}
				else
					if(TipoTarefa(Menor -> DescTarefas -> inicio -> Tipo) == TipoTarefa(pTarefa -> Tipo))
					{
						pTarefa -> ant = Menor -> DescTarefas -> inicio;
						Menor -> DescTarefas -> inicio -> prox -> ant = pTarefa;
						pTarefa -> prox = Menor -> DescTarefas -> inicio -> prox;
						Menor -> DescTarefas -> inicio -> prox = pTarefa;	
					}
					else if(TipoTarefa(Menor -> DescTarefas -> fim -> Tipo) >= TipoTarefa(pTarefa -> Tipo))
							{
								pTarefa -> ant = Menor -> DescTarefas -> fim;
								Menor -> DescTarefas -> fim -> prox = pTarefa;
								Menor -> DescTarefas -> fim = pTarefa;
							}
							else
								{
									TpPontTarefas *atual = BuscaPrioridadeComPonteiro(Menor -> DescTarefas -> inicio, pTarefa);
									pTarefa -> ant = atual -> ant;
									atual -> ant -> prox = pTarefa;
									pTarefa -> prox = atual;
									atual -> ant = pTarefa;
									
								}
		}
	Menor -> Qtde++;
}



void NovoOperador (TpDescOp &DescOp, char nomeOp[]){
	
	
	TpOperador *Operador = new TpOperador;
	Operador -> DescTarefas = new TpDescTarefa;
	Operador -> DescTarefas -> inicio = Operador -> DescTarefas -> fim = NULL;
	Operador -> Qtde = Operador -> Status = 0;
	Operador -> prox = NULL;
	Operador->Concluida.contUrg = Operador->Concluida.contNor = Operador->Concluida.contOpc = 0;
	strcpy(Operador -> nome ,nomeOp);
	
	if(DescOp.inicio == NULL){
		DescOp.inicio = DescOp.fim = Operador;
	}
	else
		{
			DescOp.fim -> prox = Operador;
			DescOp.fim = Operador;
			
		}
}

void InserirNoOp(TpDescOp &DescOp, TpTempoMedio &Media, int cont){
	TpOperador *inicial = DescOp.inicio;
	while(DescOp.inicio != NULL && DescOp.inicio -> DescTarefas -> inicio != NULL){
		if(DescOp.inicio -> Status == 0){
			
			//Gravação da tarefa no Operador
			DescOp.inicio -> TarefaAtual.TempoExec = DescOp.inicio -> DescTarefas -> inicio -> TempoExec;
			DescOp.inicio -> TarefaAtual.TempoIn = 	DescOp.inicio -> DescTarefas -> inicio -> TempoIn;
			strcpy(DescOp.inicio -> TarefaAtual.Desc, DescOp.inicio -> DescTarefas -> inicio -> Desc);
			strcpy(DescOp.inicio -> TarefaAtual.Tipo, DescOp.inicio -> DescTarefas -> inicio -> Tipo);
			DescOp.inicio -> TarefaAtual.TempoOut = cont;
			if(strcmp(DescOp.inicio->TarefaAtual.Tipo, "Urgente") == 0)
			{
				Media.TempoUrg += (cont - DescOp.inicio -> TarefaAtual.TempoIn);
				Media.cURG++;
			}
			else if (strcmp(DescOp.inicio->TarefaAtual.Tipo, "Normal") == 0)
			{
				Media.TempoNor += (cont - DescOp.inicio -> TarefaAtual.TempoIn);
				Media.cNOR++;
			}
			
			else
			{
				Media.TempoOpc += (cont - DescOp.inicio -> TarefaAtual.TempoIn);
				Media.cOPC++;
			}
			DescOp.inicio -> Status = 1;
			DescOp.inicio->TarefaAtual.contExc=0;
			
			//Retira a tarefa da Fila
			TpPontTarefas *TarefaInicio = DescOp.inicio -> DescTarefas -> inicio;
			DescOp.inicio -> DescTarefas -> inicio = TarefaInicio -> prox;
			if(DescOp.inicio -> DescTarefas -> inicio != NULL)
				DescOp.inicio -> DescTarefas -> inicio -> ant = NULL;
			else
				DescOp.inicio -> DescTarefas -> fim = NULL;
			
			delete TarefaInicio;
			
			DescOp.inicio -> Qtde--;		
		}
		
		
		DescOp.inicio = DescOp.inicio -> prox;
			
	}
	
	DescOp.inicio = inicial;
}

//Exibições
void ExibirTarefaAtual(TpPontTarefas TarefaAtual)
{
	printf("Tipo: %s, Desc: %s, Tempo de Exec: %d, Exec Atual: %d", TarefaAtual.Tipo, TarefaAtual.Desc, TarefaAtual.TempoExec, TarefaAtual.contExc);
}

void ExibirOps(TpOperador *Op, int &coluna, int &linha){
	linha = 7;
	coluna = 5;
	InterfaceOperacoes();
	textcolor(7);
	printf("### PROCESSANDO OPERACOES ###");
	while(Op != NULL){
		if(Op -> Status == 1)
		{
			InterfaceLateral(linha,0,1);
			gotoxy(coluna,linha++);
			textcolor(14);
			printf("Fabricante:"); textcolor(4);
			printf(" %s", Op -> nome);
			InterfaceLateral(linha,0,1);
			gotoxy(coluna,linha++);
			textcolor(9);
			printf("TAREFA ATUAL: ");
			InterfaceLateral(linha,0,1);
			gotoxy(coluna,linha++);
			textcolor(8);
			ExibirTarefaAtual (Op -> TarefaAtual);
			InterfaceLateral(linha,0,1);
			gotoxy(coluna,linha++);
			textcolor(9);
			printf("Tarefas na Fila: ");
			InterfaceLateral(linha,0,1);
			ExibirTarefas(Op,coluna,linha);
			InterfaceLateral(linha,0,1);
			linha++;
			gotoxy(coluna,linha++);
			textcolor(7);
			printf("-------------------------------------------------------------------------------");
		}
		Op = Op -> prox;
	}
	textcolor(0);
	textbackground(1);
	linha++;
	gotoxy(1,linha+2);
	printf("%c",200);
	gotoxy(106,linha+2);
	printf("%c",188);
	for(int c=2; c<106; c++)
	{ 
		gotoxy(c,linha+2);
		printf("%c",205);
	}
	textbackground(0);
}


void ExibirTarefas(TpOperador *ListaOp, int &coluna, int &linha) {
	if(ListaOp -> DescTarefas -> inicio != NULL)
	{
		TpPontTarefas *CaixaAux;
		CaixaAux = ListaOp -> DescTarefas -> inicio;
		while(CaixaAux != NULL)
		{
			gotoxy(coluna,linha++);
			textcolor(6);
			printf("%s, %s, %d", CaixaAux -> Tipo, CaixaAux -> Desc, CaixaAux -> TempoExec);
			InterfaceLateral(linha,0,1);
			CaixaAux = CaixaAux -> prox;
		}	
	} else {
		gotoxy(coluna,linha++);
		textcolor(6);
		printf("Nenhuma Tarefa em Fila!");
	} 
}


//Liberacoes
void LiberarListaTarefas(TpPontTarefas *ListaTarefa)
{
	if(ListaTarefa != NULL)
	{
		LiberarListaTarefas(ListaTarefa -> prox);	
		delete ListaTarefa;
	}
}

void LiberarListaOperadoresTudo(TpOperador *ListaOp)
{
	if(ListaOp != NULL)
	{
		LiberarListaOperadoresTudo(ListaOp -> prox);
		LiberarListaTarefas(ListaOp -> DescTarefas -> inicio);
		delete ListaOp;
	}
}

void VerificarExecucao(TpDescOp &DescOp ,TpTempoMedio &Media,TpTarefasConc &Conc, int cont)
{
	TpOperador *inicial = DescOp.inicio;
	int i=0, Tipo;
	while(DescOp.inicio != NULL && DescOp.inicio -> DescTarefas -> inicio != NULL){
		if(DescOp.inicio -> Status == 1 && DescOp.inicio->TarefaAtual.TempoExec == DescOp.inicio->TarefaAtual.contExc){
			Tipo=TipoTarefa(DescOp.inicio->TarefaAtual.Tipo);
			if(Tipo == 3){
				DescOp.inicio->Concluida.contUrg++;
				Conc.contUrg++;
			}
			else if(Tipo == 2)
			{
				DescOp.inicio->Concluida.contNor++;
				Conc.contNor++;
			}
			else
			{
				DescOp.inicio->Concluida.contOpc++;
				Conc.contOpc++;
			}
			DescOp.inicio -> Status = 0;
			i++; //esse i é só para saber se houve alguma alteração de status
		}
		else{
			DescOp.inicio->TarefaAtual.contExc++;
		}
		DescOp.inicio = DescOp.inicio -> prox;
	}
	
	DescOp.inicio = inicial;
	if(i>0) // se tiver alteração ira inserir outra tarefa
		InserirNoOp(DescOp , Media,cont);
}


//Exclusão do Operador
void Excluir(TpDescOp &DescOp, char nome[], int &QtdeOp, int &linha){
	TpOperador *atual = DescOp.inicio;
	char opc;
	while(atual != NULL && strcmp(atual -> nome , nome) != 0){
		atual = atual -> prox;
	}
	linha+=2;
	if(atual == NULL)
	{
		gotoxy(40,linha);
		textcolor(10);
		printf("Operador nao encontrado!");
		Sleep(500);	
	}	
	else{
		do{
		gotoxy(30,23);
		textcolor(2);
		printf("Operador %s encontrado, deseja mesmo excluir? ", atual -> nome);
		gotoxy(30,24);
		printf("(S / N)");
		opc = toupper(getch());
		
		switch(opc){
			case 'S':
				if(QtdeOp == 1){
					
					DescOp.inicio = DescOp.fim = NULL;
					atual -> prox = NULL;
					delete atual;
					QtdeOp--;
				}
				else
					{
				
					//Distrui as tarefas da Fila do Operador a ser excluido
					TpOperador *temp = atual;

					while(temp->DescTarefas->inicio != NULL) 
						{
					    DistribuirTarefa(DescOp, temp->DescTarefas->inicio, temp);
						temp->DescTarefas->inicio = atual->DescTarefas->inicio->prox;
						  
						}
						if(atual!=NULL && atual -> Status == 1){
						TpPontTarefas *pTarefa = new TpPontTarefas;
						strcpy(pTarefa -> Tipo, atual->TarefaAtual.Tipo);
						strcpy(pTarefa -> Desc, atual->TarefaAtual.Desc);
						pTarefa -> TempoExec = atual->TarefaAtual.TempoExec;
						pTarefa -> prox = pTarefa -> ant = NULL;
						DistribuirTarefa(DescOp, pTarefa, atual);
						}

					
					//Se o operador estiver no Inicio, arruma o Descritor para apontar pro próximo se existir. Se estiver no Fim msm coisa. Se estiver entre o -
					//- Fim e o Inicio msm coisa
					if (DescOp.inicio == atual) 
					{
					    DescOp.inicio = atual->prox;
					    if (DescOp.fim == atual)
					        DescOp.fim = NULL;
					}
					else
					{
						
						
						TpOperador *aux = DescOp.inicio;
						
						while(aux!= NULL && aux->prox != atual){
							aux = aux->prox;
						}
						aux -> prox = NULL;
							if (DescOp.fim == atual) {
							    if (DescOp.inicio == atual)
							        DescOp.fim = NULL;
							    else
							        DescOp.fim = aux;
							}
							else
								aux -> prox = atual -> prox;
								
					}
					
					delete atual;
					QtdeOp--;
					}
				break;				
				
				
			case 'N':
				gotoxy(38,25);
				textcolor(2);
				printf("Operacao abortada!");
				getch();
				break;
				
			default:
				gotoxy(38,25);
				textcolor(2);
				printf("Opcao invalida");
				getch();
				gotoxy(38,25);
				textcolor(0);
				printf("Opcao invalida");
				break;
			}
		}while(opc != 'N' && opc != 'S');
	}
}
