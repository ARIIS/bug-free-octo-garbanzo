
=============

Este projeto tem como objetivo auxiliar o projetista de software logo nas fases iniciais do projeto de desenvolvimento e modelagem do software. A ferramenta possibilita que o projetista modele o comportamento do software frente a informações parciais e verifique se o mesmo atende a determinadas propriedades requeridas. Caso o modelo do sistema não atenda às propriedades, a ferramenta auxiliará o projetista sugerindo e corrigindo modelos do sistema até um que o satisfaça.

* [Contribua com o projeto](#contribua-com-o-projeto)
* [Dependêcias](#dependêcias)
* [Instalação](#instalação)
* [Time de Desenvolvimento](#time-de-desenvolvimento)
* [Mais Informações](#mais-informações)


###Contribua com o projeto


* Fork o projeto
* Clone em sua máquina o repositório que você acabou de dar fork
* Adicione o projeto original como upstream: `git remote add  upstream https://github.com/JandsonRibeiro/RefinamentoDeModelosKMTS`
* `git fetch upstream`
* `git merge upstream/master`
* Crie uma branch: `git checkout -b your_branch_name`
* Faça as alterações
* Commit as alterações e dê push para sua branch
* Crie um `Pull Request`

Para manter seu fork sincronizado:

* `git fetch upstream`
* `git checkout master`
* `git merge upstream/master`
* `git push origin master`
* [leia mais](https://help.github.com/articles/syncing-a-fork/)

###Dependêcias

* g++
* bison
* flex

###Instalação

1)`make`

2)`./refiner input`

###Time de Desenvolvimento

* [Jandson Ribeiro](mailto:jandsonsantos@gmail.com) [@JandsonRibeiro](https://github.com/JandsonRibeiro) [Página Pessoal](https://jandsonribeiro.wordpress.com)
* [Marino Hohenheim](mailto:intmarinoreturn0@gmail.com) [@Marinofull](https://github.com/Marinofull)
* [Miguel Dias](mailto:migueldias1602@gmail.com) [@migueldias](https://github.com/migueldias)

###Mais Informações

* [Informações/Ajuda/Sugestões](mailto:jandsonribeiro@gmail.com)
* Este algoritmo foi originalmente proposto em [GUERRA, P. T.; ANDRADE, A.; WASSERMAN, R. Toward the revision of CTL models through kripke modal transition systems. Brasília, Brazilian Symposium on Formal Methods (SBMF), Anais, p. 115-130, 2013.]
