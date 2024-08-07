# Sistema de Control de Acceso con Arduino

Este proyecto implementa un sistema de control de acceso utilizando un Arduino Uno, un teclado numérico, una pantalla LCD I2C, un módulo RTC DS1307, un servo, un buzzer, y LEDs indicadores. El sistema verifica una contraseña ingresada y controla una barrera (servo) en función de la validación de la contraseña (estatica, definida en una variable dentro del programa).

## Descripción

El sistema permite el acceso al verificar una contraseña ingresada a través de un teclado numérico. Si la contraseña es correcta, se enciende el led verde, la barrera se abre y muestra un mensaje por el LCD indicando "Acceso permitido + fecha actual", la fecha proporcionada por un modulo RTC DS1307, luego de 2 segundos cierra la barrera y apaga el led verde. Si la contraseña es incorrecta, se muestra un mensaje de acceso denegado con la fecha y hora del intento y se enciende el led rojo. Después de tres intentos fallidos consecutivos, se activa una alerta con un buzzer y un mensaje en el LCD.

## Hardware Necesario

- Arduino Uno
- Teclado numérico (4x4)
- Pantalla LCD I2C (16x2)
- Módulo RTC DS1307
- Servo motor
- Buzzer
- LEDs (rojo y verde)
- Resistencias (220Ω para los LEDs)
- Protoboard y cables de conexión

## Conexiones

- **Teclado Numérico**: Conectado a los pines digitales 2-9 del Arduino.
- **LCD I2C**: Conectado a los pines SDA (A4) y SCL (A5).
- **RTC DS1307**: Conectado a los pines SDA (A4) y SCL (A5).
- **Servo**: Conectado al pin digital 11.
- **Buzzer**: Conectado al pin digital 13.
- **LEDs**: Rojo en el pin digital 10, verde en el pin digital 12.

## Código

El codigo se encuentra en el archivo main.ino

## Librerias necesarias

- **LiquidCrystal I2C**
- **DS1307RTC**
- **Keypad**
- **RTClib**
- **Servo**

## Notas del autor

#### Podes cambiar la contraseña en:

String password = "12345"; 

Utilizando los siguientes caracteres permitidos dentro de las " "

1, 2, 3, 4, 5, 6, 7, 8, 9, 0, A, B, C, D, * 

Recorda que el # lo estamos utilizando como caracter de corte en el primer if luego de ingresar la contraseña por eso no puede ser un valor permitido en nuestra contraseña :)

#### Podes cambiar el texto que se muestra en el LCD en todos los comandos que digan lcd.print como por ejemplo:

lcd.print("Ingrese clave:")

Recorda que el LCD tiene una cantidad limitada de 16 caracteres en la parte superior indicado en el lcd.setCursor(0, 0) y otros 16 caracteres en la parte inferior lcd.setCursor(0, 1). Por consecuencia el print debera ser como maximo de ese largo o no se mostrara el mensaje completo (como nos pasa con la hora)

Gracias por leer! 

Katherine 🌼
