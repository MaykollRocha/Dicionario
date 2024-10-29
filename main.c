#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taddic.h"

Dic carregadi(char *nomearq);
Dic invertedi(Dic paramdic);
Dic combinadi(Dic diA, Dic diB);
Dic salvadi(Dic di, char *nomearq);

int main(){

    Dic di_pt_en = carregadi("di-pt-en.txt");
    Dic di_pt_es = carregadi("di-pt-es.txt");
    Dic di_pt_fr = carregadi("di-pt-fr.txt");
    Dic di_en_pt = invertedi(di_pt_en);
    Dic di_es_pt = invertedi(di_pt_es);
    Dic di_fr_pt = invertedi(di_pt_fr);
    Dic di_en_es = combinadi(di_pt_en,di_pt_es);
    Dic di_en_fr = combinadi(di_pt_en,di_pt_fr);
    Dic di_es_fr = combinadi(di_pt_es,di_pt_fr);


    Dic diMaster = criaDic();
    diMaster = adDic(diMaster, "pt-en", di_pt_en);
    diMaster = adDic(diMaster, "pt-es", di_pt_es);
    diMaster = adDic(diMaster, "pt-fr", di_pt_fr);
    diMaster = adDic(diMaster, "en-pt", di_en_pt);
    diMaster = adDic(diMaster, "fr-pt", di_es_pt);
    diMaster = adDic(diMaster, "es-pt", di_fr_pt);
    diMaster = adDic(diMaster, "en-fr", di_en_fr);
    diMaster = adDic(diMaster, "es-fr", di_es_fr);
    diMaster = adDic(diMaster, "en-es", di_en_es);

    printf("----------------------------------------------\n");
    printf("ED TRANSLATOR VERSÃO 1.0\n");

    char origem[3];  // Assuming language codes are 2 characters (e.g., "pt")
    char destino[3];
    char busca[100];  // Adjust the size based on your needs

    while (1) {

        printf("TRADUZIR DO IDIOMA (pt,en,fr,es): ");
        scanf("%3s", origem);
        while (getchar() != '\n');
        // Verificar se a palavra fornecida é "FIM"
        if (strcmp(origem, "FIM") == 0) {
            printf("Encerrando o programa...\n");
            break;  // Sair do loop
        }

        printf("PARA O IDIOMA(pt,en,fr,es): ");
        scanf("%2s", destino);
        while (getchar() != '\n');

        printf("ENTRE COM A PALAVRA A TRADUZIR: ");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = '\0';

        // Criar a chave no formato "origem-destino"
        char chave[6];
        snprintf(chave, sizeof(chave), "%s-%s", origem, destino);

        // Verificar se a chave existe no dicionário master
        if (inDic(diMaster, chave)) {
            // Obter o dicionário de idiomas correspondente à chave
            Dic dicIdiomas = (Dic)dadoDic(diMaster, chave);

            // Verificar se a palavra de origem está no dicionário de idiomas
            if (inDic(dicIdiomas, busca)) {
                // Obter a tradução
                char *traducao = (char *)dadoDic(dicIdiomas, busca);
                printf("TRADUÇÃO: %s\n", traducao);
            } else {
                printf("PALAVRA NÃO ENCONTRADA!\n");
            }
        } else {
            printf("Combinação de idiomas não encontrada no dicionário master.\n");
        }

        printf("----------------------------------------------\n");
    }


    destroiLista(di_pt_en);
    destroiLista(di_pt_es);
    destroiLista(di_pt_fr);
    destroiLista(di_en_pt);
    destroiLista(di_es_pt);
    destroiLista(di_fr_pt);
    destroiLista(diMaster);

    return 20412;
}

Dic carregadi(char *nomearq) {
    FILE *arquivo = fopen(nomearq, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    Dic dicionario = criaDic();
    char linha[128]; // Tamanho suficiente para armazenar a linha do arquivo

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Substitua o caractere de quebra de linha por terminador nulo
        linha[strcspn(linha, "\n")] = '\0';

        // Divide a linha em duas partes usando a vírgula como delimitador
        char *palavra_pt = strtok(linha, ",");
        char *palavra_en = strtok(NULL, ",");

        // Adiciona ao dicionário
        dicionario = adDic(dicionario, palavra_pt, strdup(palavra_en));
    }

    fclose(arquivo);
    return dicionario;
}


Dic invertedi(Dic paramdic) {
    Dic invertedDic = criaDic();
    int tamanho = lenDic(paramdic);

    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(paramdic, i);
        invertedDic = adDic(invertedDic, strdup((char *)item->valor), strdup(item->key));
    }

    return invertedDic;
}

Dic combinadi(Dic diA, Dic diB) {
    Dic combinedDic = criaDic();
    int tamanhoA = lenDic(diA);
    int tamanhoB = lenDic(diB);
    int tamanhoMinimo = (tamanhoA < tamanhoB) ? tamanhoA : tamanhoB;

    for (int i = 0; i < tamanhoMinimo; i++) {
        t_item itemA = (t_item)dadoLista(diA, i);
        t_item itemB = (t_item)dadoLista(diB, i);

        // Combina os dicionários associando a palavra destino de diA à palavra destino de diB
        combinedDic = adDic(combinedDic, strdup((char *)itemA->valor), strdup((char *)itemB->valor));
    }

    return combinedDic;
}

Dic salvadi(Dic di, char *nomearq) {
    FILE *arquivo = fopen(nomearq, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    int tamanho = lenDic(di);

    for (int i = 0; i < tamanho; i++) {
        t_item item = (t_item)dadoLista(di, i);
        fprintf(arquivo, "%s,%s\n", item->key, (char *)item->valor);
    }

    fclose(arquivo);
    return di;
}
