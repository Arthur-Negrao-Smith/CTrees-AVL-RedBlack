# CTrees-AVL-RedBlack

Este projeto foi desenvolvido para a disciplina Projeto de Algoritmos II, com o objetivo de implementar as seguintes estruturas de dados:

- **Árvore AVL**
- **Árvore Rubro-Negra**
---
As estruturas atendem a seguintes requisições de rotina:
- Inserção de elementos
- Remoção de elementos
- Pesquisa de elementos na árvore
- Exibição da árvore balanceada

A árvore AVL mantém seu balanceamento por meio do fator de balanceamento em cada nó da estrutura, não podendo ser maior que 1 ou menor que -1.

A árvore Rubro-Negra mantém seu balanceamento por meio das regras de coloração com seus nós tendo cor vermelha ou preta.

---
## Estrutura de Diretórios
Para manutenção da organização do projeto, adotou-se a seguinte estrutura de diretórios:
```
src/    # Localização dos códigos do projeto
├── include/          # Todos os arquivos cabeçalho(.h) 
│   ├── avl.h
│   └── redblack.h
│
├── avl.c             # Código da árvore avl
├── main.c            # Código onde as rotinas são chamadas
└── redblack.c        # Código da árvore rubro-negra

Makefile              # Script de compilação
README.md             # Documentação do projeto
```
---

## Observação

Os testes das estruturas são realizados diretamente no código-fonte (`main.c`), não havendo interação direta com o usuário durante a execução.  

Ambas as árvores percorrem uma lista de valores previamente definida, executando automaticamente as suas respectivas operações de inserção, busca, remoção e exibição da estrutura balanceada.




## Compilação do projeto

O projeto utiliza-se da ferramenta de compilação `make` para facilitar o processo de compilação do projeto.

O projeto possuí um arquivo `Makefile` para automatizar o processo de compilação e execução, permitindo que o código seja compilado de forma simples e portátil em outros sistemas operacionais. 

Comandos para uso:
      
    make run        # Roda os algoritmos caso já tenham sido compilados

    make clean      # Limpa todos os arquivos objetos e binários do projeto

    make help       # Mostra todos os comandos do arquivo Makefile

## Autores

- Arthur Negrão Smith
- Taygo Cezar Costa Pereira

