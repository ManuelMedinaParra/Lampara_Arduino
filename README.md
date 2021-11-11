# Lampara_Arduino
Proyecto de Arduino para el curso de DronLab de la Universidad de Extremadura

Este programa se planteo con la idea de realizar, mediante un microcontrolador,
que en este caso es un arduino, un dispositivo para secar una pieza 3D, de una 
inpresora de resina.

El dispositivo consta de un modulo de potencia en el cual se han soldado un controlador
de 12v a 5v, ya que las luces termicas necesitan 12v y el arduino funciona a 5v, ademas de contener un rele, el cual se excita a traves de un transistor controlado por una salida de arduino.

El programa se inicializa dando al boton de subir tiempo, para seleccionar cuanto tiempo 
de secado se requiere, el cual se va mostrando en una pantalla lcd,ademas de contar un led,
que nos indica cuando estan la luces encendidas.

Aunque parezca que el proyecto parece facil, nada mas alejado de la realidad, ya que el codigo mezcla funciones del reloj de cuarzo, para calcular el tiempo, sino tambien el control de la lcd y el codigo detras de la selección de tiempos, la parada y la finalización.
El verdadero quebradero de cabeza, ha sido sin duda la parte de montaje y elcción de los dispositivos electronicos, ya que debido a problemas de voltajes, se ha tenido que hacer modificaciones y dedicarle tiempo para que todo funcionase como deberia.

El progaram esta muy bien estructurado, al igual que las conexiones de todos los dispositivos 
