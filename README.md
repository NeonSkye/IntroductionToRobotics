# Introduction to Robotics (2023 - 2024)

## Repo Description

Acesta este repo-ul pentru temele si proiectele de laborator pentru materia Introducere in Robotica, Facultatea de Matematica si Informatica, Anul 3, Universitatea Bucuresti. Fiecare tema inclusa include detalii despre implementarea acesteia, codul in sine, videouri si imagini. 
  
## Homeworks
### LED RGB Controlat prin 3 Potentiometre 
Pentru prima tema de laborator am avut de realizat un circuit prin care trebuia controlat un LED RGB prin intermediul a 3 Potentiometre. 

Pentu realizarea acestui scop am folosit o placa de baza Arduino UNO, prin intermediul careia este posibila controlarea a mai multor input-uri si output-uri,  si permite programarea acestora.
Astfel, am citit valorile potentiometrelor prin pinii analog input ale placii Arduino si am transmis valorile catre pinii digitali in mod output.

Pentru a transmite valorile fara erori, am folosit functia map()[^1] care mapeaza valorile de la o scara de numere la alta. Valorile rezultate au fost transmise prin pin-urile de output digitale catre cei 3 anozi ai LED-ului RGB. 

[^1]: Deoarece potentiometrul transmite valori intre 0-1023 si LED-ul primeste valori intre 0-255 este necesara functia map().

Circuit:
![Circuit_LedRGB](https://github.com/NeonSkye/IntroductionToRobotics/assets/92863316/86430edf-ceab-4fd0-810c-a7102a784734)

Demonstratie Video: 
https://www.youtube.com/watch?v=NCqM70rUhiY

### Tema 2
(TBA)
