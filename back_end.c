/*
Gabriel Deodato Leite Brandão
2019134778
2019/2020
*/

#include "back_end.h"

void distribuir_aleatorio(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int i = 0, verifica_sala;

    ppessoas aux = p_pessoas;
    plocal mem = p_espaco;
    while (i < tamanho) {

        while (aux->prox != NULL) {
            //Contar pessoas na X sala
            verifica_sala = conta_pessoas_na_sala(mem->id, p_pessoas);
            if (verifica_sala < mem->capacidade) {
                //printf("A pessoa %s pode ir para a sala %d", aux->nome, mem->id);
                aux->x_sala = mem->id;
            }
            aux = aux->prox;
        }

        mem++;
        i++;
    }
}

void menu(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int escolha;
    printf("\n\n-------------MENU------------\n\n1 - Avancar 1 iteracao na simulacao \n 2 - Apresentar estatistica: \n 3 - Adicionar doente: \n 4 - Transferir pessoas: \n 5 - Terminar Simulacao \n A sua escolha: ");
    scanf("%d", &escolha);
    if (escolha == 1) {
        avancar_um_dia(p_pessoas, p_espaco, tamanho);
    } else if (escolha == 2) {
        apresentar_estatistica(p_pessoas, p_espaco, tamanho);
    } else if (escolha == 3) {
        adicionar_doente(p_pessoas, p_espaco, tamanho);
    } else if (escolha == 4) {
        transferir_pessoas(p_pessoas, p_espaco, tamanho);
    } else if (escolha == 5) {
        terminar_simulacao(p_pessoas, p_espaco, tamanho);
    } else {
        menu(p_pessoas, p_espaco, tamanho);
    }

}

void terminar_simulacao(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int escolha_stat, i, saudaveis = 0, imunes = 0, doentes = 0, n_pessoas = 0, numero_pessoas_na_sala;

    FILE *f = fopen("terminar_simulacao.txt", "w");
    if (f == NULL) {
        printf("Erro\n");
        exit(1);
    }

    ppessoas aux = p_pessoas;
    while (aux != NULL) {
        if (aux->estado_paciente[0] == 'S') {
            saudaveis++;
        } else if (aux->estado_paciente[0] == 'D') {
            doentes++;
        } else if (aux->estado_paciente[0] == 'I') {
            imunes++;
        }

        n_pessoas++;
        aux = aux->prox;
    }

    fprintf(f, "\n RELATÓRIO \n---------\nNumero de pessoas: %d \n Imunes-> %d \n Saudaveis-> %d \n Doentes-> %d \n --------- \n", n_pessoas, imunes, saudaveis, doentes);

    fclose(f);
}

void transferir_pessoas(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int pessoas_transferidas, sala_escolhida_1, sala_escolhida_2, pessoas_total, i, x, z, v, q, ligacao, numero_pessoas_na_sala, erro = 0, sucesso = 1;
    char mensagem_erro[50];


    printf("\n Quantas pessoas deseja transferir: ");
    scanf("%d", &pessoas_transferidas);

    pessoas_total = conta_todas_as_pessoas(p_pessoas);

    if (pessoas_transferidas <= pessoas_total) {
        printf("\n----------\n");
        plocal mem = p_espaco;
        for (i = 0; i < tamanho; ++i) {
            printf("Sala %d \n", mem->id);
            mem++;
        }
        printf("\n Qual a sala: ");
        scanf("%d", &sala_escolhida_1);
        plocal mem_4 = p_espaco;
        for (i = 0; i < tamanho; ++i) {
            if (mem_4->id == sala_escolhida_1) {
                numero_pessoas_na_sala = conta_pessoas_na_sala(mem_4->id, p_pessoas);
                if (numero_pessoas_na_sala < pessoas_transferidas) {
                    ligacao = 0;
                }
            }
            mem_4++;
        }

        if (ligacao == 0) {
            printf("\n ----ERRO---- \n Nao existem pessoas suficientes nessa sala");
        } else {

            printf("\n----------\n");

            printf("Transferir %d para a sala:", pessoas_transferidas);
            plocal mem_2 = p_espaco;
            for (i = 0; i < tamanho; ++i) {
                if (mem_2->id == sala_escolhida_1) {
                    for (x = 0; x < 3; ++x) {
                        if (mem_2->liga[x] != -1) {
                            printf("\n- %d \n ", mem_2->liga[x]);
                        }
                    }
                }
                mem_2++;
            }

            printf("Para qual sala: ");
            scanf("%d", &sala_escolhida_2);

            ligacao = verificar_ligacao(p_espaco, sala_escolhida_1, sala_escolhida_2, tamanho);

            plocal mem_3 = p_espaco;
            for (i = 0; i < tamanho; ++i) {
                if (mem_3->id == sala_escolhida_2) {
                    numero_pessoas_na_sala = conta_pessoas_na_sala(mem_3->id, p_pessoas);
                    if (mem_3->capacidade == numero_pessoas_na_sala) {
                        ligacao = 0;
                    }
                }
                mem_3++;
            }
        }

        if (ligacao == 0) {
            printf("\n ----ERRO---- \n Sala Cheia | Nao existe ligacao com essa sala | \n \n");
        } else {
            printf("\n----------\n");
            ppessoas aux = p_pessoas;
            for (z = 0; z < pessoas_transferidas; ++z) {
                if (aux->x_sala == sala_escolhida_1) {
                    aux->x_sala = sala_escolhida_2;
                    printf("\n - %s foi transferido(a) da sala %d para a sala %d \n", aux->nome, sala_escolhida_1, sala_escolhida_2);
                } else {
                    z--;
                }
                aux = aux->prox;
            }
            printf("\n----------\n");
        }
    } else {
        printf("--- Erro --- \n So existem %d pessoas \n", pessoas_total);
    }

    
    menu(p_pessoas, p_espaco, tamanho);
}


int verificar_ligacao(local* p_espaco, int sala_escolhida_1, int sala_escolhida_2, int tamanho) {
    int x, i, sucesso = 0;

    plocal mem = p_espaco;
    for (i = 0; i < tamanho; ++i) {
        if (mem->id == sala_escolhida_1) {
            for (x = 0; x < 3; ++x) {
                if (mem->liga[x] == sala_escolhida_2) {
                    sucesso = 1;
                }
            }
        }
        mem++;
    }

    if (sucesso == 1) {
        return 1;
    } else {
        return 0;
    }
}


void adicionar_doente(pessoa* p_pessoas, local* p_espaco, int tamanho) {

    int i, sala, dias_infetados, idade, numero_pessoas_na_sala, erro = 0, x = 0;
    char nome[25], estado_paciente[0];

    ppessoas aux = p_pessoas;

    ppessoas novo = malloc(sizeof(pessoa));

    plocal mem = p_espaco;
    for (i = 0; i < tamanho; ++i) {
        printf("\n Sala: %d\n ", mem->id);
        mem++;
    }
    printf("\n Escolha a sala: ");
    scanf("%d", &novo->x_sala);



    if (erro == 0) {

        printf("\n Nome/Identificador: ");
        scanf("%s", novo->nome);

        printf("\n Idade: ");
        scanf("%d", &novo->idade);

        printf("\n S/D/I: ");
        scanf("%s", novo->estado_paciente);

        if (novo->estado_paciente[0] == 'D') {
            printf("\n Ha quantos dias infetado: ");
            scanf("%d", &novo->dias_infetados);
        } else {
            novo->dias_infetados = 0;
        }

        printf("Nome: %s \n Idade: %d \n Estado: %s \n \n", novo->nome, novo->idade, novo->estado_paciente);

        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        
        apresentar_estatistica(p_pessoas, p_espaco, tamanho);

    } else {
        printf("Essa sala ja esta cheia");
        menu(p_pessoas, p_espaco, tamanho);
    }
}

void apresentar_estatistica(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int escolha_stat, i, saudaveis = 0, imunes = 0, doentes = 0, n_pessoas = 0, numero_pessoas_na_sala;
    //PESSOAS --------------------------------------------------------
    ppessoas aux = p_pessoas;
    while (aux != NULL) {
        if (aux->estado_paciente[0] == 'S') {
            saudaveis++;
        } else if (aux->estado_paciente[0] == 'D') {
            doentes++;
        } else if (aux->estado_paciente[0] == 'I') {
            imunes++;
        }

        n_pessoas++;
        printf("Nome: %s \n Idade: %d \n Estado: %s \n Sala: %d \n Dias infetado: %d \n------\n", aux->nome, aux->idade, aux->estado_paciente, aux->x_sala, aux->dias_infetados);
        aux = aux->prox;
    }
    printf("---------\nNumero de pessoas: %d \n Imunes-> %d \n Saudaveis-> %d \n Doentes-> %d \n --------- \n", n_pessoas, imunes, saudaveis, doentes);
    plocal mem = p_espaco;
    for (i = 0; i < tamanho; ++i) {
        numero_pessoas_na_sala = conta_pessoas_na_sala(mem->id, p_pessoas);
        printf("Pessoas na sala %d -> %d \n", mem->id, numero_pessoas_na_sala);
        mem++;
    }
    printf("------------");
    

    printf("\n 1 - Voltar ao menu \n 2 - Sair \n A sua escolha: ");
    scanf("%d", &escolha_stat);

    if (escolha_stat == 1) {
        menu(p_pessoas, p_espaco, tamanho);
    } else {
        exit(0);
    }
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int calcular_novos_infetados(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int i = 0, n_pessoas = 0, n_pessoas_totais = 0, n_pessoas_doentes = 0, novos_infetados, novos_infetados_totais = 0, contador = 0;

    ppessoas aux = p_pessoas;
    ppessoas aux_2 = p_pessoas;
    plocal mem = p_espaco;
    while (i < tamanho) {

        //BUSCAR OS DOENTES E AS PESSOAS TOTAIS DA SALA
        while (aux != NULL) {
            if (aux->x_sala == mem->id) {
                if (aux->estado_paciente[0] == 'D') {
                    n_pessoas_doentes++;
                }
                n_pessoas++;
            }
            aux = aux->prox;
        }

        novos_infetados = (5*n_pessoas/100)*n_pessoas_doentes;

        if (novos_infetados > 0) {

            while (contador != novos_infetados) {
                if (aux_2 == NULL) {
                    break;
                } else {
                    if (aux_2->estado_paciente[0] == 'S' && aux_2->x_sala == mem->id) {

                        strcpy(aux_2->estado_paciente, "D");

                        contador++;
                    }

                    aux_2 = aux_2->prox;
                }
                
            }

        }
        
        novos_infetados_totais = novos_infetados_totais + novos_infetados;
        
        mem++;
        i++;
    }
}

void avancar_um_dia(pessoa* p_pessoas, local* p_espaco, int tamanho) {
    int probabilidade_recuperar, n_digitos_na_idade, n_doentes, novos_infetados;
    int i;

    novos_infetados = calcular_novos_infetados(p_pessoas, p_espaco, tamanho);

    ppessoas aux = p_pessoas;
    while (aux != NULL) {


        if (aux->estado_paciente[0] == 'D') {


            //Número de digitos na idade
            n_digitos_na_idade = aux->idade;

            //Primeiro digito da idade
            while(n_digitos_na_idade >= 10) {
                n_digitos_na_idade = n_digitos_na_idade / 10;
            }

            //Duração máxima da infeção
            if (aux->dias_infetados >= (5 + n_digitos_na_idade)) {

                if (probEvento(0.20) == 1) { //Taxa de imunidade
                    strcpy(aux->estado_paciente, "I");
                } else {
                    strcpy(aux->estado_paciente, "S");
                }


            } else {
                //PROBABILIDADE DE RECUPERAR
                probabilidade_recuperar = 1/aux->idade;
                for(i=0; i<10; i++) {
                    if (probEvento(probabilidade_recuperar) == 1) { //Taxa de imunidade
                        if (probEvento(0.20) == 1) {
                            strcpy(aux->estado_paciente, "I");
                        } else {
                            strcpy(aux->estado_paciente, "S");
                        }
                        
                    }
                }
            }

            //Aumentar os dias infetados
            aux->dias_infetados = aux->dias_infetados + 1;
        }

        
        
        aux = aux->prox;
    }

    printf("\n------- Avancou um dia -------\n");
    menu(p_pessoas, p_espaco, tamanho);
}

int conta_pessoas_na_sala(int id_sala, pessoa* p_pessoas) {
    int conta_pessoas = 0;

    ppessoas aux = p_pessoas;
    while (aux != NULL) {
        if (aux->x_sala == id_sala) {
            conta_pessoas++;
        }
        aux = aux->prox;
    }

    return conta_pessoas;
}

int conta_todas_as_pessoas(pessoa* p_pessoas) {
    int conta_pessoas = 0;

    ppessoas aux = p_pessoas;
    while (aux != NULL) {
        conta_pessoas++;
        aux = aux->prox;
    }

    return conta_pessoas;
}


pessoa* read_pessoas() {
    struct pessoas pessoa;
    ppessoas atual, mem;
    ppessoas verificao_atual = NULL;

    char nome_ficheiro[25];

    printf("\n\n----------------------------------------\nLendo ficheiros .txt...\n----------------------------------------\n");


    printf("Digite o nome do ficheiro do Txt: ");
    gets(nome_ficheiro);


    if (strstr(nome_ficheiro, ".txt") == NULL) { //Se não encontrar .txt na var
        strcat(nome_ficheiro, ".txt"); //Adiciona .txt no final
    }



    FILE *ficheiro = fopen(nome_ficheiro, "r");
    printf("%s", nome_ficheiro);

    if (!ficheiro) {
        printf("Erro ao ler ficheiro");
        return NULL;
    } else {

     while (!feof(ficheiro)){
        ppessoas atual = malloc(sizeof(pessoa));
        if (atual == NULL){
            printf("ERRO");
        }


        fscanf(ficheiro, "%s %d %s", atual->nome, &atual->idade, atual->estado_paciente);

        if (atual->estado_paciente[0] == 'D'){
            fscanf(ficheiro, "%d", &atual->dias_infetados);
        } else {
            atual->dias_infetados = 0;
        }

        atual->x_sala = NULL;
        atual->prox = NULL;

        if (verificao_atual == NULL) {
            verificao_atual = atual;
        } else {
            mem = verificao_atual;
            while (mem->prox != NULL){
                mem = mem->prox;
            }
            mem->prox = atual;
        }

    }
    ficheiro = NULL;
    fclose(ficheiro);
    printf("\n--------------------------------------------------------------------------------\n");
    return verificao_atual;
}
}

local* read_espacos(int* tamanho) {
    struct sala local, *mem = NULL, *local_array;

    char nome_ficheiro[25];

    printf("----------------------------------------\nLendo ficheiros .bin...\n----------------------------------------\n");

    printf("Digite o nome do ficheiro do Espaco: ");
    gets(nome_ficheiro);

    if (strstr(nome_ficheiro, ".bin") == NULL) { //Se não encontrar .bin na var
        strcat(nome_ficheiro, ".bin"); //Adiciona .bin no final
    }



    FILE *ficheiro_binario = fopen(nome_ficheiro,"rb");

    if (!ficheiro_binario) {
        printf("Erro ao ler ficheiro");
        return NULL;
    } else {
        int x = 1;


        while (fread(&local, sizeof(struct sala), 1, ficheiro_binario)) {
            if (mem == NULL) {
                mem = malloc(sizeof(struct sala));
            } else {
                mem = realloc(local_array, sizeof(struct sala) * 1);
            }

            memcpy(&mem[x-1], &local, sizeof(local));
            if (mem != NULL) {
                local_array = mem;
                x++;
            }


        }

        *tamanho=x-1;

    }

    return mem;
    fclose(ficheiro_binario);

}