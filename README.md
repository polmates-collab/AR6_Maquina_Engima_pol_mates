# AR6_Maquina_Engima_pol_mates

Simulador básico de ENIGMA
Proyecto en C++ que simula una versión sencilla de la máquina ENIGMA con 3 rotores. Permite cifrar, descifrar mensajes y editar los rotores desde un menú en consola.

Archivos

main.cpp: menú principal
rotor.h / rotor.cpp: gestión de rotores
enigma.h / enigma.cpp: cifrado y descifrado
Rotor1.txt, Rotor2.txt, Rotor3.txt: configuración de los rotores

Uso

Elegir una opción del menú
Escribir la ventana inicial (ej: ABC)
Introducir el mensaje

El programa limpia el texto y genera los resultados.

Archivos generados

Missatge.txt: mensaje limpio
Xifrat.txt: mensaje cifrado (en grupos de 5)
desxifrat.txt: mensaje descifrado

Notas

Cada rotor debe tener 26 letras mayúsculas sin repetir
El notch hace avanzar el siguiente rotor
El cifrado se puede revertir usando la misma configuración
