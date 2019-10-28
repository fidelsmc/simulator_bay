//timers
unsigned long Ta; //tiempo actual del sistema

bool TimerSW1 = 0;  //Activar temporizador 1
unsigned long Ti1 = 0; //tiempo inicial del timer 1
int Tcom1=0; //comando para timer 1, 0=nada, 1=cerrar, 2=abrir

bool TimerSW2 = 0;  
unsigned long Ti2 = 0; 
int Tcom2=0; 

bool TimerSW3 = 0;  
unsigned long Ti3 = 0; 
int Tcom3=0; 

bool TimerSW4 = 0;  
unsigned long Ti4 = 0; 
int Tcom4=0; 

// Variables Aux
int m;
int ttransito = 3; //ms

// Variables del CB1
bool CB1_O_ST = 1;   // (DO22) CB1 Abierto 
bool CB1_C_ST = 0;   // (DO23) CB1 Cerrado
bool CB1_R_ST = 1;   // (DO24) CB1 Remoto
bool CB1_DP_ST = 0;  // (DO25) CB1 Discrepancia de polos
bool CB1_SF6_A = 0;  // (DO26) Alarma SF6
bool CB1_RE_DES = 0; // (DO27) Resorte descargado
bool CB1_CMD_O = 0;  // (DI02) Comando Abrir
bool CB1_CMD_C = 1;  // (DI03) Comando Cerrar

//Variables SW1
bool SW1_O_ST = 1;   // (DO28) Abierto 
bool SW1_C_ST = 0;   // (DO29) Cerrado
bool SW1_R_ST = 1;   // (DO30) Remoto
bool SW1_CMD_O = 0;  // (DI04) Comando Abrir
bool SW1_CMD_C = 1;  // Comando Cerrar

//Variables SW2
bool SW2_O_ST = 1; //  Abierto 
bool SW2_C_ST = 0; //  Cerrado
bool SW2_R_ST = 1; //  Remoto
bool SW2_CMD_O = 0; // Comando Abrir
bool SW2_CMD_C = 1; // Comando Cerrar

//Variables SW3
bool SW3_O_ST = 1; //  Abierto 
bool SW3_C_ST = 0; //  Cerrado
bool SW3_R_ST = 1; //  Remoto
bool SW3_CMD_O = 0; // Comando Abrir
bool SW3_CMD_C = 1; // Comando Cerrar

//Variables SW4
bool SW4_O_ST = 1; //  Abierto 
bool SW4_C_ST = 0; //  Cerrado
bool SW4_R_ST = 1; //  Remoto
bool SW4_CMD_O = 0; // Comando Abrir
bool SW4_CMD_C = 1; // Comando Cerrar

//Colores de lineas
String C_B  = "\033[39m"; //Borra formato de color
String C_A  = "\033[33m"; //Amarillo
String C_R  = "\033[31m"; //Rojo
String C_V  = "\033[32m"; //Verde
String C_AZ = "\033[36m"; //Azul

//mensajes
String M_C_O = " Com. Apertura ->";
String M_C_C = " Com. Cierre ->";
String M_S_O = " ya se encuentra abierto";
String M_S_C = " ya se encuentra cerrado";
String M_SW_T = "En transito...";

//Pines Salidas
int CB1_O_ST_DO = 22;
int CB1_C_ST_DO = 23;
int CB1_R_DO = 24;
int CB1_DP_DO = 25;
int CB1_SF6_AL_DO = 26;  
int CB1_RE_DES_DO = 27;

int SW1_O_ST_DO = 28;   
int SW1_C_ST_DO = 29;   
int SW1_R_ST_DO = 30;   

int SW2_O_ST_DO = 31;   
int SW2_C_ST_DO = 32;   
int SW2_R_ST_DO = 33;   

int SW3_O_ST_DO = 34;   
int SW3_C_ST_DO = 35;   
int SW3_R_ST_DO = 36;   

int SW4_O_ST_DO = 37;   
int SW4_C_ST_DO = 38;   
int SW4_R_ST_DO = 39;   
       

//Pines Entradas
int CB1_CMD_O_DI=2;
int CB1_CMD_C_DI=3;

int SW1_CMD_O_DI = 4;  
int SW1_CMD_C_DI = 5;

int SW2_CMD_O_DI = 6;  
int SW2_CMD_C_DI = 7;

int SW3_CMD_O_DI = 8;  
int SW3_CMD_C_DI = 9; 

int SW4_CMD_O_DI = 10;  
int SW4_CMD_C_DI = 11;  

void setup() {
  
  //Salidas
  pinMode(CB1_O_ST_DO,OUTPUT);
  pinMode(CB1_C_ST_DO,OUTPUT);
  pinMode(CB1_R_DO,OUTPUT);
  pinMode(CB1_DP_DO,OUTPUT);
  pinMode(CB1_SF6_AL_DO,OUTPUT);
  pinMode(CB1_RE_DES_DO,OUTPUT);

  pinMode(SW1_O_ST_DO,OUTPUT);
  pinMode(SW1_C_ST_DO,OUTPUT);
  pinMode(SW1_R_ST_DO,OUTPUT);

  pinMode(SW2_O_ST_DO,OUTPUT);
  pinMode(SW2_C_ST_DO,OUTPUT);
  pinMode(SW2_R_ST_DO,OUTPUT);

  pinMode(SW3_O_ST_DO,OUTPUT);
  pinMode(SW3_C_ST_DO,OUTPUT);
  pinMode(SW3_R_ST_DO,OUTPUT);

  pinMode(SW4_O_ST_DO,OUTPUT);
  pinMode(SW4_C_ST_DO,OUTPUT);
  pinMode(SW4_R_ST_DO,OUTPUT);


  //Entradas
  pinMode(CB1_CMD_O_DI,INPUT);
  pinMode(CB1_CMD_C_DI,INPUT); 
  
  pinMode(SW1_CMD_O_DI,INPUT);
  pinMode(SW1_CMD_C_DI,INPUT);

  pinMode(SW2_CMD_O_DI,INPUT);
  pinMode(SW2_CMD_C_DI,INPUT);

  pinMode(SW3_CMD_O_DI,INPUT);
  pinMode(SW1_CMD_C_DI,INPUT);

  pinMode(SW4_CMD_O_DI,INPUT);
  pinMode(SW1_CMD_C_DI,INPUT);


  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  menu0();
}

void loop() {
    
    entradas();

    Ta = millis()/1000;

    // temporizadores
    Tempo1();
    Tempo2();
    Tempo3();
    Tempo4();

    int sel=Serial.read();
    //************  menu 0
    if (sel == 105 && m==0) {
      panoNormal();
      }
    if (sel == 111 && m==0) {
      menu1();
      }
 
    // ************   Menu 1
    if (sel == 49 && m==1) { //Cierra CB1
      controlCB1(false,true,false);
      }
    if (sel == 50 && m==1) { //Abre CB1
      controlCB1(true,false,false);
      }
    if (sel == 51 && m==1) { //Cierra SW1
      controlSW1(false,true,false);
      }
    if (sel == 52 && m==1) { //Abre SW1
      controlSW1(true,false,false);
      }
    if (sel == 53 && m==1) { //Cierra SW2
      controlSW2(false,true,false);
      }
    if (sel == 54 && m==1) { //Abre SW2
      controlSW2(true,false,false);
      }   
    if (sel == 55 && m==1) { //Cierra SW3
      controlSW3(false,true,false);
      }
    if (sel == 56 && m==1) { //Abre SW3
      controlSW3(true,false,false);
      }
    if (sel == 57 && m==1) { //Cierra SW4
      controlSW4(false,true,false);
      }
    if (sel == 48 && m==1) { //Abre SW4
      controlSW4(true,false,false);
      }
    if (sel == 109 && m==1) { //Va al menu 0
    menu0();
      }
    
    // General  
    if (sel == 115) {
      estadopano();
      }
    /*if (int(sel) != -1) {// Muestra el caracter en la cola serial
      Serial.println(int(sel));  
      }*/
 
    salidas();
}

void menu0() {
    m=0;
    Serial.print(C_B);
    Serial.write(12); //limpia pantalla, sirve con PuTTY
    estadopano();
    Serial.println(C_V + "\n(i)niciar\t(o)perar\t(s)tatus" + C_B); 
    
}

void menu1() {
    m=1;
    Serial.print(C_B);
    Serial.write(12);
    estadopano();
    Serial.println(C_V + "\nC/O:\t1/2 CB1\t\t3/4 SW1\t\t5/6 SW2\t\t7/8 SW3\t\t9/0 SW4"+C_B);
}

void estadopano(){
    Serial.println("PAÑO");
    Serial.println("\rSW1\tSW2\tSW3\tSW4\tCB1");
    Serial.println(estado(SW1_O_ST,SW1_C_ST)+"\t"+estado(SW2_O_ST,SW2_C_ST)+"\t"+estado(SW3_O_ST,SW3_C_ST)+"\t"+estado(SW4_O_ST,SW4_C_ST)+"\t"+estado(CB1_O_ST,CB1_C_ST)+"\r" + C_B);
    Serial.println(estadoLR(SW1_R_ST)+"\t"+estadoLR(SW2_R_ST)+"\t"+estadoLR(SW3_R_ST)+"\t"+estadoLR(SW4_R_ST)+"\t"+estadoLR(CB1_R_ST) + "\r" + C_B);
}

String estado(bool ST_O,bool ST_C){
  if (ST_O == true && ST_C == false){
    return C_V + "OPE";
    }
    if (ST_O == false && ST_C == true){
    return C_R + "CLO";
    }  
    if (ST_O == false && ST_C == false){
    return C_A + "IND";
    }  
}

String estadoLR(bool ST_R){
  if (ST_R == true){
    return C_A + "REM";
    }
  else {
    return C_B + "LOC";  
    }
}

void panoNormal(){
  // Variables del CB1
  CB1_O_ST = 1; // CB1 Abierto 
  CB1_C_ST = 0; // CB1 Cerrado
  CB1_R_ST = 1; // CB1 Remoto
  CB1_DP_ST = 0; // CB1 Discrepancia de polos
  CB1_SF6_A = 0; // Alarma SF6
  CB1_RE_DES = 0; // Resorte descargado
  CB1_CMD_O = 0; // Comando Abrir
  CB1_CMD_C = 0; // Comando Cerrar

  //Variables SW1
  SW1_O_ST = 1; //  Abierto 
  SW1_C_ST = 0; //  Cerrado
  SW1_R_ST = 1; //  Remoto
  SW1_CMD_O = 0; // Comando Abrir
  SW1_CMD_C = 0; // Comando Cerrar

  //Variables SW2
  SW2_O_ST = 1; //  Abierto 
  SW2_C_ST = 0; //  Cerrado
  SW2_R_ST = 1; //  Remoto
  SW2_CMD_O = 0; // Comando Abrir
  SW2_CMD_C = 0; // Comando Cerrar

  //Variables SW3
  SW3_O_ST = 1; //  Abierto 
  SW3_C_ST = 0; //  Cerrado
  SW3_R_ST = 1; //  Remoto
  SW3_CMD_O = 0; // Comando Abrir
  SW3_CMD_C = 0; // Comando Cerrar

  //Variables SW4
  SW4_O_ST = 1; //  Abierto 
  SW4_C_ST = 0; //  Cerrado
  SW4_R_ST = 1; //  Remoto
  SW4_CMD_O = 0; // Comando Abrir
  SW4_CMD_C = 0; // Comando Cerrar

  Serial.println("\n\rPaño Normalizado...");

  menu0();
}

//Temporizadores
void Tempo1(){
  if (TimerSW1==1){
    if (Ta-Ti1>=ttransito){
      if (Tcom1 == 1){
        SW1_C_ST=1;
      }
      if (Tcom1 == 2){
        SW1_O_ST=1;
      }
      Tcom1=0;
      TimerSW1=0;
      menu1();
    }
  }
}

void Tempo2(){
  if (TimerSW2==1){
    if (Ta-Ti2>=ttransito){
      if (Tcom2 == 1){
        SW2_C_ST=1;
      }
      if (Tcom2 == 2){
        SW2_O_ST=1;
      }
      Tcom2=0;
      TimerSW2=0;
      menu1();
    }
  }
}

void Tempo3(){
  if (TimerSW3==1){
    if (Ta-Ti3>=ttransito){
      if (Tcom3 == 1){
        SW3_C_ST=1;
      }
      if (Tcom3 == 2){
        SW3_O_ST=1;
      }
      Tcom3=0;
      TimerSW3=0;
      menu1();
    }
  }
}

void Tempo4(){
  if (TimerSW4==1){
    if (Ta-Ti4>=ttransito){
      if (Tcom4 == 1){
        SW4_C_ST=1;
      }
      if (Tcom4 == 2){
        SW4_O_ST=1;
      }
      Tcom4=0;
      TimerSW4=0;
      menu1();
    }
  }
}

void controlCB1(bool CMD_O,bool CMD_C,bool BF){
  if (CMD_O == true){
    Serial.println("\nCB1" + M_C_O);
    }
  if (CMD_C == true){
    Serial.println("\nCB1" + M_C_C);
    }
  if (CMD_C == true && CB1_C_ST == true){
    Serial.println(C_A + "CB1" + M_S_C + C_B);
    }
  if (CMD_O == true && CB1_O_ST == true){
    Serial.println(C_A + "CB1" + M_S_O + C_B);
    }
  if (CMD_C == true && CB1_O_ST == true){ //Cierra el Interruptor 
    CB1_O_ST =0;
    CB1_C_ST =1;
    menu1();
    }
  if (CMD_O == true && CB1_C_ST == true){ //Abre el Interruptor 
    CB1_O_ST =1;
    CB1_C_ST =0;
    menu1();
    }
}

void controlSW1(bool CMD_O,bool CMD_C,bool F){
  if (CMD_O == true){
    Serial.println("\nSW1" + M_C_O);
    }
  if (CMD_C == true){
    Serial.println("\nSW1" + M_C_C);
    }
  if (CMD_C == true && SW1_C_ST == true){
    Serial.println("SW1" + M_S_C);
    }
  if (CMD_O == true && SW1_O_ST == true){
    Serial.println("SW1" + M_S_O);
    }
  if (CMD_C == true && SW1_O_ST == true){ //Cierra el desconectador 
    SW1_O_ST =0;
    TimerSW1 = 1; //activa el timer
    Ti1=millis()/1000;
    Tcom1=1;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
  if (CMD_O == true && SW1_C_ST == true){ //Abre el desconectador 
    SW1_C_ST =0;
    TimerSW1 = 1; //activa el timer
    Ti1=millis()/1000;
    Tcom1=2;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
}

void controlSW2(bool CMD_O,bool CMD_C,bool F){
  if (CMD_O == true){
    Serial.println("\nSW2" + M_C_O);
    }
  if (CMD_C == true){
    Serial.println("\nSW2" + M_C_C);
    }
  if (CMD_C == true && SW2_C_ST == true){
    Serial.println("SW2" + M_S_C);
    }
  if (CMD_O == true && SW2_O_ST == true){
    Serial.println("SW2" + M_S_O);
    }
  if (CMD_C == true && SW2_O_ST == true){ //Cierra el desconectador 
    SW2_O_ST =0;
    TimerSW2 = 1; //activa el timer
    Ti2=millis()/1000;
    Tcom2=1;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
  if (CMD_O == true && SW2_C_ST == true){ //Abre el desconectador 
    SW2_C_ST =0;
    TimerSW2 = 1; //activa el timer
    Ti2=millis()/1000;
    Tcom2=2;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
}

void controlSW3(bool CMD_O,bool CMD_C,bool F){
  if (CMD_O == true){
    Serial.println("\nSW3" + M_C_O);
    }
  if (CMD_C == true){
    Serial.println("\nSW3" + M_C_C);
    }
  if (CMD_C == true && SW3_C_ST == true){
    Serial.println("SW3" + M_S_C);
    }
  if (CMD_O == true && SW3_O_ST == true){
    Serial.println("SW3" + M_S_O);
    }
  if (CMD_C == true && SW3_O_ST == true){ //Cierra el desconectador 
    SW3_O_ST =0;
    TimerSW3 = 1; //activa el timer
    Ti3=millis()/1000;
    Tcom3=1;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
  if (CMD_O == true && SW3_C_ST == true){ //Abre el desconectador 
    SW3_C_ST =0;
    TimerSW3 = 1; //activa el timer
    Ti3=millis()/1000;
    Tcom3=2;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
}


void controlSW4(bool CMD_O,bool CMD_C,bool F){
  if (CMD_O == true){
    Serial.println("\nSW4" + M_C_O);
    }
  if (CMD_C == true){
    Serial.println("\nSW4" + M_C_C);
    }
  if (CMD_C == true && SW4_C_ST == true){
    Serial.println("SW4" + M_S_C);
    }
  if (CMD_O == true && SW4_O_ST == true){
    Serial.println("SW4" + M_S_O);
    }
  if (CMD_C == true && SW4_O_ST == true){ //Cierra el desconectador 
    SW4_O_ST =0;
    TimerSW4 = 1; //activa el timer
    Ti4=millis()/1000;
    Tcom4=1;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
  if (CMD_O == true && SW4_C_ST == true){ //Abre el desconectador 
    SW4_C_ST =0;
    TimerSW4 = 1; //activa el timer
    Ti4=millis()/1000;
    Tcom4=2;
    Serial.println(C_AZ + M_SW_T + C_B); //En transito...
    }
}

void entradas(){
 /* int CBCO=digitalRead(CB1_CMD_O_DI);
  if (CBCO==HIGH){
    controlCB1(true,false,false);
    delay(80);
  }
  int CBCC=digitalRead(CB1_CMD_C_DI);
  if (CBCC==HIGH){
    controlCB1(false,true,false);
    delay(80);
  }
  int SW1CO=digitalRead(SW1_CMD_O_DI);
  if (SW1CO==HIGH){
    controlSW1(true,false,false);
    delay(80);
  }
  int SW1CC=digitalRead(SW1_CMD_C_DI);
  if (SW1CC==HIGH){
    controlSW1(false,true,false);
    delay(80);
  }
  int SW2CO=digitalRead(SW2_CMD_O_DI);
  if (SW2CO==HIGH){
    controlSW2(true,false,false);
    delay(80);
  }
  int SW2CC=digitalRead(SW2_CMD_C_DI);
  if (SW2CC==HIGH){
    controlSW2(false,true,false);
    delay(80);
  }
  int SW3CO=digitalRead(SW3_CMD_O_DI);
  if (SW3CO==HIGH){
    controlSW3(true,false,false);
    delay(80);
  }
  int SW3CC=digitalRead(SW3_CMD_C_DI);
  if (SW3CC==HIGH){
    controlSW3(false,true,false);
    delay(80);
  }
  int SW4CO=digitalRead(SW4_CMD_O_DI);
  if (SW4CO==HIGH){
    controlSW4(true,false,false);
    delay(80);
  }
  int SW4CC=digitalRead(SW4_CMD_C_DI);
  if (SW4CC==HIGH){
    controlSW4(false,true,false);
    delay(80);
  }*/
}

void salidas(){
  if (CB1_O_ST == 1){
    digitalWrite(CB1_O_ST_DO,HIGH);
  }
  else {
    digitalWrite(CB1_O_ST_DO,LOW);
  }
  if (CB1_C_ST == 1){
    digitalWrite(CB1_C_ST_DO,HIGH);
  }
  else {
    digitalWrite(CB1_C_ST_DO,LOW);
  }
  if (CB1_R_ST == 1){
    digitalWrite(CB1_R_DO,HIGH);
  }
  else {
    digitalWrite(CB1_R_DO,LOW);
  }
  if (CB1_DP_ST == 1){
    digitalWrite(CB1_DP_DO,HIGH);
  }
  else {
    digitalWrite(CB1_DP_DO,LOW);
  }
  if (CB1_SF6_A == 1){
    digitalWrite(CB1_SF6_AL_DO,HIGH);
  }
  else {
    digitalWrite(CB1_SF6_AL_DO,LOW);
  }
  if (CB1_RE_DES == 1){
    digitalWrite(CB1_RE_DES_DO,HIGH);
  }
  else {
    digitalWrite(CB1_RE_DES_DO,LOW);
  }
  if (SW1_O_ST == 1){
    digitalWrite(SW1_O_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW1_O_ST_DO,LOW);
  }
  if (SW1_C_ST == 1){
    digitalWrite(SW1_C_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW1_C_ST_DO,LOW);
  }
  if (SW1_R_ST == 1){
    digitalWrite(SW1_R_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW1_R_ST_DO,LOW);
  }
  if (SW2_O_ST == 1){
    digitalWrite(SW2_O_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW2_O_ST_DO,LOW);
  }
  if (SW2_C_ST == 1){
    digitalWrite(SW2_C_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW2_C_ST_DO,LOW);
  }
  if (SW2_R_ST == 1){
    digitalWrite(SW2_R_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW2_R_ST_DO,LOW);
  }
  if (SW3_O_ST == 1){
    digitalWrite(SW3_O_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW3_O_ST_DO,LOW);
  }
  if (SW3_C_ST == 1){
    digitalWrite(SW3_C_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW3_C_ST_DO,LOW);
  }
  if (SW3_R_ST == 1){
    digitalWrite(SW3_R_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW3_R_ST_DO,LOW);
  }
  if (SW4_O_ST == 1){
    digitalWrite(SW4_O_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW4_O_ST_DO,LOW);
  }
  if (SW4_C_ST == 1){
    digitalWrite(SW4_C_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW4_C_ST_DO,LOW);
  }
  if (SW4_R_ST == 1){
    digitalWrite(SW4_R_ST_DO,HIGH);
  }
  else {
    digitalWrite(SW4_R_ST_DO,LOW);
  }
}

