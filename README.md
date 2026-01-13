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
