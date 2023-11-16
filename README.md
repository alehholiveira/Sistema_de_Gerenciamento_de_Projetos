# Sistema de Gerenciamento de Tarefas

## Introdução

O objetivo deste projeto é desenvolver um sistema de gerenciamento de tarefas utilizando estruturas de dados, como filas e listas. O sistema visa auxiliar indivíduos, equipes ou organizações na organização, monitoramento e administração de tarefas a serem concluídas. A principal proposta é aprimorar a eficiência, aumentar a produtividade e facilitar o acompanhamento de tarefas e atividades. O sistema oferece oito funções em seu menu, cada uma realizando ações específicas.

Além disso, o sistema foi projetado com foco no usuário final, uma professora. Assim, é amigável, de fácil compreensão e manipulação.

## Desenvolvimento do Projeto

Durante o processo de desenvolvimento, a equipe enfrentou desafios, destacando-se a transferência de tarefas entre filas e listas. Problemas surgiram ao atualizar o status das tarefas, especialmente na transição de pendente para "em dia" e vice-versa. A maior dificuldade foi a transferência de informações entre a lista e a fila. A solução envolveu a revisão minuciosa da remoção de tarefas das filas e listas, corrigindo os erros identificados.

A parte avançada do projeto inclui o uso de três filas para diferentes prioridades. O programa é inicializado com tarefas pré-inseridas, distribuídas entre as filas conforme as prioridades.

## Funcionalidades

1. **Adicionar Tarefa**
   - O usuário pode adicionar uma nova tarefa à fila de tarefas, inserindo informações através do terminal.

2. **Modificar Tarefa**
   - Permite a alteração dos dados de uma tarefa, fornecendo o código correspondente.

3. **Concluir Tarefa**
   - Tarefas concluídas são movidas para uma lista encadeada de tarefas concluídas, ordenadas pela data de término.

4. **Atualizar Tarefa**
   - O usuário pode atualizar o status de uma tarefa como pendente ou não pendente, movendo-a entre a lista de pendentes e a fila original.

5. **Listar Tarefas Pendentes**
   - Imprime a lista de tarefas pendentes.

6. **Listar Tarefas Concluídas**
   - Imprime a lista de tarefas concluídas.

7. **Listar Tarefas Concluídas com ou sem Atrasos**
   - Imprime duas informações: códigos das tarefas com atraso e depois tarefas sem atrasos.

8. **Listar Todas as Tarefas**
   - Imprime informações de todas as tarefas criadas e ainda não concluídas, independentemente de sua prioridade.

9. **Sair do Programa**
   - Encerra o funcionamento do programa.
