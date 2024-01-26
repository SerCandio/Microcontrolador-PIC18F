# Ejemplo de PORT I/O
En este ejemplo se explicara rapidamente acerca de los bits de configuracion en MPLABX, que sera comprobado mediante un blink de un LED cada 1s

<h2 dir="auto" tabindex="-1">Nota:</h2>El uC PIC debe tener conectado entre sus pines <B>RA6</B> y <B>RA7</B> un oscilador de cristal de 16MHz, a 
fin de poder establecer una frecuencia de osiclacion de 48MHz (nos permitira hacer uso del puerto USB incorporado en la PCB: <B>Mini PIC TRAINER</B>)
tal como se muestra a continuacion(ver datasheet pagina 29, Figura 3-1):

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/95431540-8f03-4091-b3fc-2b3281ce65f0)

<h2 dir="auto" tabindex="-1">Pasos:</h2>
<B>1.</B> En el proyecto de PORT_IO.X , nos vamos a <B><I>Window / Tarjet Memoery Views / Configuration bits</I></B> y se muestra la pestaña:

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/d9e58e1b-33d3-4c89-b5e4-54b4862bbca2)

<B>2.</B> Modificamos los bits de configuracion como se muestra : 

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/0661d048-6324-456e-8ed2-a9ae61546356)

<B>3.</B> Clic en <B><I>"Generate Source Code to Output"</I></B> 

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/654b7ead-fb18-4200-b27d-5de0da961a65)

<B>4.</B> El codigo generado lo encuentra en : <B><A HREF="https://github.com/SerCandio/Microcontrolador-PIC18F/blob/main/LIBRERIAS%20PIC18/ConfBits_RealBoardPLL.c">LIBRERIAS PIC18/ConfBits_RealBoardPLL.c</A></B>

<h2 dir="auto" tabindex="-1">OBS:</h2>Los archivos <B>"ConfBits_RealBoardPLL.c"</B> y <B>"ConfBits_RealBoardPLL.h"</B> ya se encuentran incluidos en el proyecto <B><A HREF="https://github.com/SerCandio/Microcontrolador-PIC18F/tree/main/PORT_IO.X">PORT_IO.X</A></B>

<B>5.</B> Abra la simulacion en Proteus PORT_IO.X/Simulation Proteus <B><A HREF="https://github.com/SerCandio/Microcontrolador-PIC18F/tree/main/PORT_IO.X/Simulation%20Proteus">PORT_IO.X/Simulation Proteus</A></B> y cargue el ejecutable <B>"PORT_IO.X.production.hex"</B> :

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/c3b442df-cf15-489a-97fe-4c99cc0327e2)

<B>6.</B> Al dar en <B>Run Simulation</B> observara que el LED va a parpadear y el osciloscopio virtual mostrara:
![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/83749c86-1f81-4d15-a6fe-3add1bdb1a82)

<h2 dir="auto" tabindex="-1">Conclusion:</h2>
Lo anterior se comprueba que el FOSC esta corriendo a 48MHz, dando una base de tiempo de delay de instruccion para poder producir un retardo de 1 segundo


