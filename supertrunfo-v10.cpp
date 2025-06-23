#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIDADES 100
#define MAX_ESTADO 50
#define MAX_NOME 100

typedef struct
{
  char estado[MAX_ESTADO];
  int codigo;
  char nome[MAX_NOME];
  long populacao;
  double pib;
  double area; // em km²
  int pontos_turisticos;
  double densidade;      // populacao / area
  double pib_per_capita; // pib / populacao
} Carta;

// Função para ler uma linha de texto (string) pulando o '\n' deixado por scanf
void read_line(char *buffer, int size)
{
  int c;
  // descarta até o newline anterior, se houver
  while ((c = getchar()) != '\n' && c != EOF)
    ;
  fgets(buffer, size, stdin);
  // remove eventual '\n' final
  buffer[strcspn(buffer, "\n")] = '\0';
}

int main(void)
{
  int n;
  printf("Quantas cartas (cidades) deseja cadastrar (max %d)? ", MAX_CIDADES);
  if (scanf("%d", &n) != 1 || n < 1 || n > MAX_CIDADES)
  {
    fprintf(stderr, "Quantidade inválida.\n");
    return 1;
  }

  Carta *baralho = (Carta *)malloc(sizeof(Carta) * n);
  if (!baralho)
  {
    perror("malloc");
    return 1;
  }

  for (int i = 0; i < n; i++)
  {
    printf("\n--- Carta %d ---\n", i + 1);
    printf("Estado: ");
    read_line(baralho[i].estado, MAX_ESTADO);

    printf("Código (inteiro): ");
    scanf("%d", &baralho[i].codigo);

    printf("Nome da cidade: ");
    read_line(baralho[i].nome, MAX_NOME);

    printf("População (número inteiro): ");
    scanf("%ld", &baralho[i].populacao);

    printf("PIB (em bilhões, vírgula como ponto): ");
    scanf("%lf", &baralho[i].pib);

    printf("Área (km²): ");
    scanf("%lf", &baralho[i].area);

    printf("Número de pontos turísticos: ");
    scanf("%d", &baralho[i].pontos_turisticos);

    // cálculos derivados
    baralho[i].densidade = baralho[i].populacao / baralho[i].area;
    baralho[i].pib_per_capita = (baralho[i].populacao > 0)
                                    ? (baralho[i].pib * 1e9) / baralho[i].populacao
                                    : 0.0;
  }

  // Exibe todas as cartas
  printf("\n\n===== CARTAS CADASTRADAS =====\n");
  for (int i = 0; i < n; i++)
  {
    Carta *c = &baralho[i];
    printf("\nCarta %d: Código %d — %s/%s\n",
           i + 1, c->codigo, c->nome, c->estado);
    printf(" População: %ld\n", c->populacao);
    printf(" PIB: %.2f bilhões\n", c->pib);
    printf(" Área: %.2f km²\n", c->area);
    printf(" Pontos turísticos: %d\n", c->pontos_turisticos);
    printf(" → Densidade: %.2f hab/km²\n", c->densidade);
    printf(" → PIB per capita: R$ %.2f\n", c->pib_per_capita);
  }

  free(baralho);
  return 0;
}
