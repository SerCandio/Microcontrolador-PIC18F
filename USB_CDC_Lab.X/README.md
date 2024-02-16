# Ejemplo de USB_CDC
Aqui se muestra un ejemplo de la comunicacion USB CDC de Alta velocidad actuando la PC como Host.

<h2 dir="auto" tabindex="-1">Nota:</h2>
<p></p>Para que la comunicacion USB CDC de Alta Velocidad pueda funcionar , se debe haber configurado el System Clock a 48Mhz partiendo de un XTAL de 16MHz tal como se muestra en nuestro primer ejemplo <B><A HREF="https://github.com/SerCandio/Microcontrolador-PIC18F/tree/main/PORT_IO.X">PORT_IO.X</A></B> en la <B><I>Figura 1</I></B></p>

![image](https://github.com/SerCandio/Microcontrolador-PIC18F/assets/106831539/c5d7d830-df5f-460e-b8b5-d87bb23778b7)

<B><I>Figura 1.- Emulador de puerto COM PuTTy</I></B>

En necesario tambien que tenga el <B><A HREF="https://www.chiark.greenend.org.uk/~sgtatham/putty/">PuTTy</A></B> instaldo , que es un emulador de puerto serial, como se observa en la figura anterior

<h2 dir="auto" tabindex="-1">Pasos:</h2>
<B>1.-</B>Descarge y abra el proyecto USB_CDC_Lab.X en la version que tenga instalada de MPLAB con compilador XC8 instalado.  

(figura 2)

<B>2.-</B> Observe el proyecto. Note que se imprimira el mensaje <B><I>"Hello World , Millis= ####"</I></B> a traves del puerto USB en una de las tareas de RTOS (<B>Task 1</B>) cada 1000 ms como se ve en la figura 2

<B>3.-</B> Debe cargar el ejecutable : <B><A HREF="USB_CDC_Lab.X/dist/default/production">USB_CDC_Lab.X.production.hex</A></B>  mediante MPLAB IPE (usando PICKIT 3) como se muestra :

(figura 3)

<B>4.-</B> Conecte el puerto USB a la PC Host y luego presione RESET (ver <B><A HREF="https://github.com/SerCandio/Mini-PIC18F-TRAINER">Figura 3</A></B> de la placa Mini-PIC18F-TRAINER) o conecte y desconecte el puerto USB (si es que esta es su unica alimentacion VCC)

<B>5.-</B> Vaya al administrador de dispositivos e identifique su puerto COM como se muestra:

<B>6.-</B> Abra el emulador de puerto PuTTy e ingrese el puerto COM disponible del apartado anterior

<h2 dir="auto" tabindex="-1">PRUEBAS Y FUNCIONAMIENTO</h2>
En cuanto conectemos nuestra <B><A HREF="https://github.com/SerCandio/Mini-PIC18F-TRAINER">placa entrenadora</A></B> con el ejecutable <B><A HREF="https://github.com/SerCandio/Microcontrolador-PIC18F/blob/main/USB_CDC_Lab.X/dist/default/production/USB_CDC_Lab.X.production.hex">USB_CDC_Lab.X.production.hex</A></B> grabado en ella y el puerto USB Tipo B conectado a un puerto USB de la PC.

En el siguiente <B><A HREF="https://youtu.be/mNRTedm4bW8">video</A></B> incrustado podemos ver una prueba de funcionamiento de la placa entrenadora(orientado a MultiTasking RTOS):

[![VIDEO](https://img.youtube.com/vi/mNRTedm4bW8/0.jpg)](https://youtu.be/mNRTedm4bW8)

<h2 dir="auto" tabindex="-1">Conclusion:</h2>

<h2 dir="auto" tabindex="-1">Observacion:</h2>
La comunicacion USB-CDC no admite simulacion en Prtoeus (por el momento)

