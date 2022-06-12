# Up.Temporizador
Atividade feita para o curso de automação industrial em 2020 no [TinkerCad](https://www.tinkercad.com/things/3UdoJ8yHSnB-up-temporizador).
O objetivo é, com um decodificador e um display de 7 segmentos, incrementar, decrementar e resetar(zerar) o display.

<div align="center">  
  
  ![temporizador](https://user-images.githubusercontent.com/95356877/173206885-c5f0302c-59be-4e2a-b233-c922c5fc9594.png)
  
</div>

##

🧱Equipamentos utilizados:
- Display de sete segmentos, comum: cátodo.
- Decodificador CD4511.
- Resistor 330 ohm.
- Botões.

##

👩‍💻 Explicação do código:
  - Inicialmente, é definido quais portas/inputs serão utilizadas para incrementar(increment), decrementar(decrement), resetar(reset)

    ![inputs](https://user-images.githubusercontent.com/95356877/173207326-ad4f31b9-9458-4bea-9998-edb4a60bf51d.png)

 
        #define increment 4
        #define decrement 5
        #define reset 6

- Em seguida, é definido as variáveis a ser utilizadas

      int cont = 0;
      unsigned long time = 0;
      unsigned long currentTime = 0;
      unsigned long previousTime = 0;

      bool valueBI = 0; 
      bool valueBD = 0; 
      bool valueR = 0; 
      bool previousStateBI = 0; 
      bool previousStateBD = 0; 
      bool previousStateR = 0; 
      
- Na função LOOP, chamamos outras duas funções

      void loop()
      {
        operation();
        blinking();
      }

- Na função SETUP é definido os inputs e outputs, como estamos utilizando um decodificador, podemos nos basear na [documentação](https://docs.arduino.cc/hacking/hardware/PinMapping168) para dividirmos as portas, nesta atividade, utilizei a porta B e a D

  Como visualizado na documentaçãom os pinos do 8 ao 13 são referêntes à porta B, e utilizaremos essas pinos como saídas(1), por conta disso ele recebe o valor de 255, que equivale à 11111111 quando se trata de binário. Neste caso, utilizamos a porta do 8 ao 10 e setamos todas as portas do 8 ao 13, não há problema nenhum nisto.
  Já a porta D, somente o pino 7 é setado como saída(1), os demais como entradas(0), afinal, serão as entradas que receberão os sinais dos botões.

      void setup()
      {
        DDRB = 255; //11111111
        DDRD = 128; //10000000
      }

- A função OPERATION, recebe o valor que o botão traz(true e false, afinal, ou o botão está ligado ou desligado) por conta da função dRead. Após isso, a variável PORTB vai receber o valor que será mostrado no display. Graças ao decodificador, conseguimos enviar números inteiros e ele converte para binário, já que é assim que o display de 7 segmento espera receber os números para mostrar.
   Portanto, se o valor do botão incrementa(valueBI) for true(1) E o estado anterior do botão incrementa(previusStateBI) for false(0), ele vai incrementar(cont++).
   Se o valor do botão Decrementa(valueBD) for true(1) E o estado anterior do botão decrementa(previusStateBD) for false(0), ele vai decrementar(cont--).
   Se o valor do botão Reset(valueR) for true(1) E o estado anterior do botão Reset(previusR) for false(0), ele vai zerar(cont = 0).
   Ademais, como é um contador que vai até nove, se a contagem passar do limite, ele zera novamente.
   

      void operation(){
        dRead();
        PORTB = cont;
        if(valueBI == 1 && previousStateBI == 0){
          PORTD = 128;
          cont++;
        }
        previousStateBI = valueBI;
        if(valueBD == 1 && previousStateBD == 0){
          PORTD = 128;
          cont--;
        }
        previousStateBD = valueBD;
        if(valueR == 1 && previousStateR == 0){
          PORTD = 128;
          cont = 0;
        }
        previousStateR = valueR;
        if(cont == 10){
          cont = 0;
        }
      }
      
- A função BLINKING, serve para fazer o contador piscar quando a contagem for maior ou igual a 7. Obs: Caso simule no Tinkercad, pode ser que tenha um delay por conta de ser um simulador.

      void blinking(){
        ms();
        if(cont >= 7 && time <= 500){
          PORTD = 128;
        }
        else if(time > 500 && time <= 1000){
          PORTD = 0;
        }
        else{
          previousTime = currentTime;   
        }
      }

      void ms(){
        currentTime = millis();
        time = currentTime - previousTime;
      }

##

🔌Explicação ligações:

- CD4511

![image](https://user-images.githubusercontent.com/95356877/173209672-da24266c-fe8b-4811-9bad-4289475840cf.png)

Alimentação:

![image](https://user-images.githubusercontent.com/95356877/173209426-663ad9d2-b94b-4ce5-b27f-f8d6a62aa3c9.png)

Para fazer o display piscar é utilizado o pino 7:

![image](https://user-images.githubusercontent.com/95356877/173209450-a02739fe-94ce-4a89-a57a-c5af109a250a.png)

Ligações com o display:
  Na parte inferior, pinos outputs de 8 à 11 que irão fazer a contagem em binário.
  Na parte superior, saídas que irão encaixar no display de acordo com sua letra.

![image](https://user-images.githubusercontent.com/95356877/173209613-a7aacada-75c1-489a-9636-a53c8d07c58f.png)

- Display 7 segmentos
Intermédio entre o decodificador e o display, se tem resistores.
Poderia utilizar somente um resistor no cátodo? A resposta é sim, contudo, a corrente seria dividida entre os segmentos e o display emitiria luz mais fracas dependendo do número.

![image](https://user-images.githubusercontent.com/95356877/173209811-6182aa15-8fbe-46b3-b418-6580a4eb3a72.png)

- Botões:
inputs: 6,5,4

![image](https://user-images.githubusercontent.com/95356877/173209825-c4efeedb-b664-499f-818b-68a28fb071b9.png)

##

É basicamente isso!
Quer fazer um Sugestão? Correção? Ou tem alguma dúvida?
Entre em contato comigo!

<a href="https://www.linkedin.com/in/anna-rocha-5a3126227" target="_blank"><img src="https://img.shields.io/badge/-LinkedIn-%230077B5?style=for-the-badge&logo=linkedin&logoColor=white" target="_blank"></a>
  <a href = "mailto:annaleletr@gmail.com"><img src="https://img.shields.io/badge/-Gmail-%23333?style=for-the-badge&logo=gmail&logoColor=white" target="_blank"></a>
  
  Discord:
  
     ANNA#8936

<div align="center">

![ThatsAll](https://user-images.githubusercontent.com/95356877/173209889-586eb497-e062-44ab-9760-727512afbb30.gif)
  
 </div>
  

