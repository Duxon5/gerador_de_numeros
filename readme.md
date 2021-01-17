# Gerador de apostas

## Introdução
O projeto <i><b>gerador_de_numeros</b></i> foi desenvolvido com o intuito de que as pessoas que costumam apostar em sorteios, como por exemplo o <b>"Mega da Virada"</b>, não percam muito tempo pensando em números aleatórios para poderem apostar. 
<br/>Esta solução fica ainda mais eficiente em <i>"bolões"</i>, pois nessa circunstância é necessário realizar diversos jogos (sorteios).
<br/>Dessa forma, basta apenas digitar quantos jogos serão feitos e <i><b>Voilà!</b></i>, todos os resultados serão gravados em um arquivo. Basta apenas apostar!

### Imagens do programa
<table>
  <tr>
    <td>É possível gerar os números de acordo com os parametros digitados</td>
     <td>Além de serem gravados em um arquivo de sua escolha (txt ou csv), será apresentado na tela como foi gravado.</td>
  </tr>
  <tr>
    <td><img src="./img/opcao_salvar.png" width=300 height=480></td>
    <td><img src="./img/resultados_gravados.png" width=571 height=252></td>
  </tr>
 </table>
 
### Imagens do arquivo gerado
<table>
  <tr>
    <td>O arquivo quando gravado em .csv, cada valor será fixado em sua respectiva célula.</td>
     <td>Quando gravado em .txt, será separado por espaços.</td>
  </tr>
  <tr>
    <td><img src="./img/print_csv.png" width=450
	height=200 vertical-align="middle"></td>
    <td><img src="./img/print_txt.png" width=250 height=250></td>
  </tr>
 </table>

## Algumas limitações

* Só é possível gravar arquivos na pasta './files' (que se localiza no mesmo caminho do arquivo 'random_numer.cpp'
* Só é possível listar e gravar arquivos que possuem a extensão '.csv' ou '.txt' (minúsculo)
* Para rodar o programa é necessário instalar o MinGW e gerar o executável (explicação no próximo tópico)

## Como utilizar [Windows]

* Será necessário instalar o [MINGW](https://sourceforge.net/projects/mingw/)
* Ao instalar, será necessário marcar as opções de 'msys' e 'bin'
* Após a instalação, colocar o caminho <b>'DISCO:\MinGW\msys'</b> e <b>'DISCO:\MinGW\bin'</b> no <b>PATH</b> das variáveis do ambiente
* Abrir o cmd e acessar a pasta que o arquivo <b>'random_numer.cpp'</b> se encontra <i>(exemplo: cd C:\Users\Carlos\gerador_de_numeros')</i>
* Executar o comando g++ random_number.cpp -o qualquer_nome.exe

## Considerações finais

Peço que se possível, caso tiver interesse no programa e realizar o download, deixe uma avaliação e caso encontrar qualquer tipo de problema, me informe para poder corrigí-lo.

Agradeço a todos pela atenção!

Atenciosamente,
Sidnei G. de Azevedo Júnior.
