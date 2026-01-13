# PROJETO 1 - Implementação de Ordenação Externa com K-way Merge Sort em C

Este repositório contém o **Projeto 1 e 2 da disciplina de Pesquisa e Ordenação de Dados**, desenvolvido no curso de **Ciência da Computação da UTFPR – Campus Santa Helena**.

O projeto tem como objetivo implementar, em linguagem C, um algoritmo de **ordenação externa**, voltado para cenários em que o volume de dados é maior do que a capacidade da memória principal.

---

##  Objetivo do Projeto
Implementar o algoritmo **K-way Merge Sort** para ordenar grandes volumes de dados armazenados em arquivos, utilizando a memória apenas para blocos menores de dados.

O projeto busca demonstrar, na prática, como funcionam técnicas de ordenação externa e a importância da divisão do problema em etapas.

---

##  Fundamentação
Quando os dados não cabem inteiramente na memória, torna-se inviável aplicar algoritmos de ordenação interna diretamente.  
Nesse contexto, a **ordenação externa** divide os dados em partes menores, ordena cada parte individualmente e, ao final, realiza a intercalação desses blocos.

Neste trabalho:
- O algoritmo base utilizado foi o **Merge Sort**
- A intercalação foi feita no modelo **K-way**
- Para a ordenação interna dos blocos, foi utilizado o **Selection Sort**, pela simplicidade de implementação

---

##  Metodologia e Implementação
O programa foi desenvolvido em **linguagem C** e dividido nas seguintes etapas:

###  1 - Geração do Arquivo de Entrada
- Criação de um arquivo `entrada.txt` contendo números inteiros aleatórios.

###  2️ - Criação dos Blocos
- Leitura do arquivo de entrada em blocos de tamanho definido.
- Ordenação interna de cada bloco utilizando **Selection Sort**.
- Gravação dos blocos ordenados em arquivos temporários (`bloco0.txt`, `bloco1.txt`, etc.).

### 3️ - Intercalação K-way
- Abertura simultânea dos arquivos de blocos.
- Intercalação dos dados para gerar um único arquivo final ordenado (`saida.txt`).

O programa também possui um **menu interativo**, permitindo:
- Visualizar o arquivo de entrada
- Visualizar os blocos intermediários
- Visualizar o arquivo final ordenado

---

##  Resultados
Os testes foram realizados com:
- **150 registros**
- **Tamanho de bloco igual a 10**

Como resultado:
- Foram gerados **15 blocos intermediários**
- O arquivo final `saida.txt` apresentou todos os números corretamente ordenados em ordem crescente

Os testes demonstraram o impacto do tamanho do bloco no desempenho, evidenciando o equilíbrio necessário entre:
- Custo de ordenação interna
- Quantidade de operações de leitura e escrita em disco

---

##  Conclusão
O algoritmo de **K-way Merge Sort** foi implementado com sucesso em C, atendendo ao objetivo proposto.  
O projeto permitiu compreender, de forma prática, o funcionamento da ordenação externa e a importância da divisão do problema em etapas bem definidas.

---

## Tecnologias Utilizadas
- Linguagem C
- Manipulação de arquivos
- Algoritmos de ordenação
- Conceitos de ordenação externa

---

## Autores
- Jefferson Korte Junior  
- Igor Carvalho Marchi  

Curso de Ciência da Computação – UTFPR  
Campus Santa Helena – PR






# PROJETO 2 -  Simulação de Memória Secundária utilizando Árvore B em C

Este repositório contém o **Projeto 2 da disciplina de Pesquisa e Ordenação de Dados**, desenvolvido no curso de **Ciência da Computação da UTFPR – Campus Santa Helena**.

O projeto tem como objetivo simular o funcionamento de uma **memória secundária (disco)** utilizando a estrutura de dados **Árvore B**, devido à sua semelhança com o modelo de acesso por blocos utilizado em sistemas reais.

---

## Objetivo do Projeto
Simular o gerenciamento de memória secundária por meio de uma **Árvore B**, implementando operações de **inserção** e **busca**, com controle e monitoramento das operações de leitura e escrita em disco.

O projeto busca demonstrar, na prática, como estruturas de dados são utilizadas para organizar e acessar grandes volumes de dados de forma eficiente.

---

## Fundamentação
A Árvore B é amplamente utilizada em **sistemas de arquivos** e **sistemas gerenciadores de banco de dados (SGBDs)**, pois mantém a árvore sempre balanceada e reduz a quantidade de acessos ao disco.

Neste trabalho, a Árvore B foi utilizada para:
- Representar páginas (blocos) da memória secundária
- Reduzir a altura da estrutura
- Minimizar o número de operações de leitura e escrita simuladas

---

## Metodologia e Implementação
O projeto foi implementado em **linguagem C**, sendo dividido em três módulos principais:

### 1 - Implementação da Árvore B
- Criação da estrutura da árvore e dos nós
- Operações de inserção com tratamento de overflow (split)
- Operação de busca recursiva
- Impressão hierárquica da árvore

### 2️ - Simulação de Disco
- Representação da memória secundária por meio de um vetor de páginas
- Funções para simular leitura e escrita em disco
- Contadores para registrar operações de I/O (leitura e escrita)

### 3️ - Entrada e Saída de Dados
- Interface de linha de comando
- Comandos como `INSERT` e `SEARCH`
- Registro das operações em arquivo de texto

---

## Resultados
A simulação apresentou resultados satisfatórios, com:
- Execução correta das operações de inserção e busca
- Controle preciso das operações de leitura e escrita
- Redução do número de acessos ao disco devido ao balanceamento da Árvore B

Os resultados confirmam a eficiência da Árvore B para organização de dados em memória secundária simulada.

---

## Conclusão
O projeto atingiu seu objetivo ao simular de forma eficiente uma memória secundária utilizando Árvore B.  
A implementação permitiu compreender o impacto da organização dos dados na redução de latência e no desempenho das operações de busca e inserção.

---

## Tecnologias Utilizadas
- Linguagem C
- Estrutura de dados Árvore B
- Manipulação de arquivos
- Simulação de memória secundária
- Conceitos de gerenciamento de I/O

---

## Autores
- Caio Macedo Lima da Cruz  
- José Carlos Seben de Souza Leite  
- Igor Carvalho Marchi  
- Jefferson Korte Júnior  

Curso de Ciência da Computação – UTFPR  
Campus Santa Helena – PR

