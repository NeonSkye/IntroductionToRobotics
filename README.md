# Introduction to Robotics (2023 - 2024)

## Repo Description

Acesta este repo-ul pentru temele si proiectele de laborator pentru materia Introducere in Robotica, Facultatea de Matematica si Informatica, Anul 3, Universitatea Bucuresti. Fiecare tema inclusa include detalii despre implementarea acesteia, codul in sine, videouri si imagini. 
  
## Homeworks
### LED RGB Controlat prin 3 Potentiometre 
Pentru prima tema de laborator am avut de realizat un circuit prin care trebuia controlat un LED RGB prin intermediul a 3 Potentiometre. 

Pentu realizarea acestui scop am folosit o placa de baza Arduino UNO, prin intermediul careia este posibila controlarea a mai multor input-uri si output-uri,  si permite programarea acestora.
Astfel, am citit valorile potentiometrelor prin pinii analog input ale placii Arduino si am transmis valorile catre pinii digitali in mod output.

Pentru a transmite valorile fara erori, am folosit functia map()[^1] care mapeaza valorile de la o scara de numere la alta. Valorile rezultate au fost transmise prin pin-urile de output digitale catre cei 3 anozi ai LED-ului RGB. Folosind Pulse Width Modulation (PWM), unii pini digitali ai Arduino pot simula un semnal analog.

[^1]: De ce map()? Deoarece potentiometrul transmite valori intre 0-1023 si LED-ul primeste valori intre 0-255. Daca nu mapam, atunci LED-ul s-ar fi pornit si oprit de mai multe ori pana ajungea potentiometrul la maxim.

Circuit:
![Circuit_LedRGB](https://github.com/NeonSkye/IntroductionToRobotics/assets/92863316/86430edf-ceab-4fd0-810c-a7102a784734)

Demonstratie Video: 
https://www.youtube.com/watch?v=NCqM70rUhiY

### Elevator Wannabe
Pentru a doua tema de laborator am avut de realizat simularea unui lift prin intermediul a 4 LED-uri,  3 butoane si un buzzer.

3 LED-uri sunt necesare pentru a indica unde este liftul,  un LED este folosit pentru indicatorul de operare al liftului, iar buzzer-ul reda sunetul liftului (se inchid usile, liftul e in miscare, liftul a ajuns la destinatie). Am folosit un array care contine state-ul LED-urilor de etaj. Pentru a simula unde a fost chemat liftul, am folosit un floorTarget. De asemenea, pentru a decide ce LED-uri se aprind (in ce directie se misca liftul) am folosit doua functii if, care verifica daca etajul destinatie este mai mare sau mai mic ca etajul curent. Astfel, am reusit sa fac ca LED-urile intermediare sa se aprinda, indicand unde s-ar afla liftul.

Cat timp liftul este in miscare, LED-ul de stare palpaie, iar cand liftul se afla la un etaj, LED-ul de stare ramane aprins.

Pentru "soundtrack-ul" liftului, am 3 array-uri de note muzicale, note obtinute din header-ul "pitches.h". 

Butoanele liftului au debounce implementat in cod. 

Circuit:
![20231029_192857](https://github.com/NeonSkye/IntroductionToRobotics/assets/92863316/0b8211b7-6b87-48d6-b64d-bad13e051c8d)

Demonstratie Video:
https://www.youtube.com/watch?v=provyeFycSM

### Stopwatch Timer
Pentru a patra tema de laborator am avut de realizat un cronometru simplu, cu functionalitate de start/pause, reset, si lap. 

Am folosit un 7-segment 4 digit display pentru afisarea timpului, un shift register pentru scriere, si 3 butoane pentru a controla cronometrul. Pentru scrierea si afisarea timpului m-am folosit de mai multe functii in cod, precum writeReg si writeNumber. Am scris
encoding-ul in biti, pentru a-i transmite segmentelor individuale prin intermediul shift register-ului. Pentru functionalitatea de lap pur si simplu am un vector de 4 elemente in care salvez timpul in momentul apasarii butonului de lap. Atunci cand cronometrul este in starea initiala/dupa reset (adica este afisat 000.0), atunci apasarea butonului de lap va trece prin acest vector si va afisa timpii salvati. 

Apasarea butonului lap salveaza timpul doar daca cronometrul nu este in pauza. Apasarea butonului de reset reseteaza cronometrul doar daca acesta este in pauza.

Circuit: 
![20231112_193314](https://github.com/NeonSkye/IntroductionToRobotics/assets/92863316/0755aba4-46c2-487f-ba5a-f294536fd7d0)

Demonstratie Video:
https://www.youtube.com/watch?v=ymOH9y6Fu_A
