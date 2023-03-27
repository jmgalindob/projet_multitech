//-------------------------------------------------
//-------------- DESCRIPTION-----------------------
//-------------------------------------------------

////////////////////////////////////////////////////
/// Titre: Parking automatique
////////////////////////////////////////////////////
/// Carte: Arduino MEGA
////////////////////////////////////////////////////
//  Date/version: 03/2023
//  Description: Gestion des entrées/sorties d'un parking automatique
///////////////////////////////////////////////////

//-------------------------------------------------
//--------- DIRECTIVES PREPROCESSSEUR--------------
//-------------------------------------------------

//////////////////////////////////////////////////////////////

// Inclusion de bibliothèques
#include <Arduino.h>
#include <Servo.h>

// Définition des broches...
//Sorties
#define ElevatorUpPin 0 //Ascenseur montée
#define ElevatorDownPin 1 //Ascenseur descente
#define EnableBridgePin 2 //Activation du pont
#define RotatePlatformPin 5 //Rotation de la plateforme
#define TranslatePlatformPin 6 //Translation de la plateforme
#define EntryBarrierPin 7 //Barrière d'entrée
#define ExitBarrierPin 8 //Barrière de sortie
#define AvailableSpotsScreenPin 9 //Ecran d'affichage des places disponibles
#define CarHolders1Pin 40 //Maintien de roue 1
#define CarHolders2Pin 41 //Maintien de roue 2
#define CarHolders3Pin 42 //Maintien de roue 3
#define CarHolders4Pin 43 //Maintien de roue 4
#define TicketsDispenserPin 44 //Distributeur de tickets

//Entrées
#define PowerButton 2 //Bouton d'alimentation
#define EmergencyStopButton 3 //Bouton d'arrêt d'urgence
#define EntryDesk 10 //Bouton d'entrée
#define EntryBarrierSensor 4 //Capteur de barrière d'entrée
#define UserIsOutButton 11 //Bouton de sortie de la plateforme
#define ExitDesk 12 //Bouton de sortie
#define CarSensorPlatform 13   //Capteur de voiture sur la plateforme
#define Floor0Sensor 36 //Capteur de fin de course du rez-de-chaussée
#define Floor1Sensor 38 //Capteur de fin de course du 1er étage
#define Floor2Sensor 39 //Capteur de fin de course du 2ème étage
#define CarHolders1Sensor 36 //Capteur de contact du maintien de roue 1
#define CarHolders1EndSensor 37 //Capteur de fin de course du maintien de roue 1
#define CarSensorSpot1 14 //Capteur de voiture sur la place 1
#define CarSensorSpot2 15 //Capteur de voiture sur la place 2
#define CarSensorSpot3 16 //Capteur de voiture sur la place 3
#define CarSensorSpot4 17 //Capteur de voiture sur la place 4
#define CarSensorSpot5 18 //Capteur de voiture sur la place 5
#define CarSensorSpot6 19 //Capteur de voiture sur la place 6
#define CarSensorSpot7 20 //Capteur de voiture sur la place 7
#define CarSensorSpot8 21 //Capteur de voiture sur la place 8
#define CarSensorSpot9 22 //Capteur de voiture sur la place 9
#define CarSensorSpot10 23 //Capteur de voiture sur la place 10
#define CarSensorSpot11 24 //Capteur de voiture sur la place 11
#define CarSensorSpot12 25 //Capteur de voiture sur la place 12
#define CarSensorSpot13 26 //Capteur de voiture sur la place 13
#define CarSensorSpot14 27 //Capteur de voiture sur la place 14
#define CarSensorSpot15 28 //Capteur de voiture sur la place 15
#define CarSensorSpot16 29 //Capteur de voiture sur la place 16
#define CarSensorSpot17 30 //Capteur de voiture sur la place 17
#define CarSensorSpot18 31 //Capteur de voiture sur la place 18
#define CarSensorSpot19 32 //Capteur de voiture sur la place 19
#define CarSensorSpot20 33 //Capteur de voiture sur la place 20
#define FireSensor 34 //Capteur de feu
#define IntrusionSensor 35 //Capteur d'intrusion
    
//-------------------------------------------------
//--------- DECLARATIONS --------------------------
//-------------------------------------------------

	// Déclaration des variables
int ETAT=0;
bool EntryBarrierPosition=false; //Position de la barrière d'entrée true=ouverte false=fermée
bool ExitBarrierPosition=false; //Position de la barrière de sortie true=ouverte false=fermée
int CarSensorSpotPins [20]={CarSensorSpot1,CarSensorSpot2,CarSensorSpot3,CarSensorSpot4,CarSensorSpot5,CarSensorSpot6,CarSensorSpot7,CarSensorSpot8,CarSensorSpot9,CarSensorSpot10,CarSensorSpot11,CarSensorSpot12,CarSensorSpot13,CarSensorSpot14,CarSensorSpot15,CarSensorSpot16,CarSensorSpot17,CarSensorSpot18,CarSensorSpot19,CarSensorSpot20};
int CarHoldersPins[4]={CarHolders1Pin,CarHolders2Pin,CarHolders3Pin,CarHolders4Pin}; //Tableau des pins des maintiens de roue
bool TakenSpots[20]={false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}; //Tableau des places de parking occupées
int TakenSpotsTimer[20][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}//{Heure arrivée, heure départ}
char TakenSpotsImmat[20][7]={,,,,,,,,,,,,,,,,,}; //Tableau des immatriculations des voitures sur les places de parking
bool CarHoldersPosition[4]={false,false,false,false}; //Position des maintiens de roue false=repliés true=déployés
bool TicketAvailable=true; 
const int SpotsPositions[20][2]={{1,0},{1,36},{1,72},{1,108},{1,144},{1,180},{1,216},{1,252},{1,288},{1,324},{2,0},{2,36},{2,72},{2,108},{2,144},{2,180},{2,216},{2,252},{2,288},{2,324}}; //Tableau des positions des places de parking
int Power=80; //Puissance de l'ascenseur
// Instantation d'objet
Servo RotatePlatform;
Servo TranslatePlatform;
Servo EntryBarrier;
Servo ExitBarrier;
Servo CarHolders[4];

// Déclaration des fonctions
void ShowAvailableSpots ();
void EmergencyStop ();
void EntryBarrierOpen ();
void CarHoldersDeploy ();
void PlatformInit();
void BarrierOpen ();



void setup() 
     {      
        //Configuration 
  pinMode(ElevatorDownPin, OUTPUT);
  pinMode(ElevatorUpPin, OUTPUT);
  pinMode(EnableBridgePin, OUTPUT);
  pinMode(CarHolders1Pin, OUTPUT);
  pinMode(CarHolders2Pin, OUTPUT);
  pinMode(CarHolders3Pin, OUTPUT);
  pinMode(CarHolders4Pin, OUTPUT);
  pinMode(RotatePlatformPin, OUTPUT);
  pinMode(TranslatePlatformPin, OUTPUT);
  pinMode(EntryBarrierPin, OUTPUT);
  pinMode(ExitBarrierPin, OUTPUT);
  pinMode(AvailableSpotsScreenPin, OUTPUT);
  pinMode(TicketsDispenserPin, OUTPUT);
  pinMode(EmergencyStopButton, INPUT);
  pinMode(EntryBarrierSensor, INPUT);
  pinMode(CarHolders1Sensor, INPUT);
  pinMode(CarHolders1EndSensor, INPUT);
  pinMode(PowerButton, INPUT);
  pinMode(EntryDesk, INPUT);
  pinMode(UserIsOutButton, INPUT);
  pinMode(ExitDesk, INPUT);
  pinMode(CarSensorPlatform, INPUT);
  pinMode(FireSensor, INPUT);
  pinMode(IntrusionSensor, INPUT);
  pinMode(Floor1Sensor, INPUT);
  pinMode(Floor2Sensor, INPUT);
  


  for (int i = 1; i < 20; i++){ //Boucle pour les capteurs de voiture sur les places
      pinMode(CarSensorSpotPins[i], INPUT);
  }

      //Initialisation 
  Serial.begin(9600);
  RotatePlatform.attach(RotatePlatformPin);
  EntryBarrier.attach(EntryBarrierPin);
  ExitBarrier.attach(ExitBarrierPin);
  TranslatePlatform.attach(TranslatePlatformPin);
  for (int i=0; i<4; i++){
    CarHolders[i].attach(CarHoldersPins[i]);
  }
  attachInterrupt(digitalPinToInterrupt(EmergencyStopButton), EmergencyStop, FALLING);
}                                                                                                                               
//-------------------------------------------------
//------------- PROCEDURE ET FONCTIONS -----------
//-------------------------------------------------

//  Code des procédures et fonctions
void EmergencyStop(){
  ETAT=0;
}
void CarHoldersDeploy(int CarHoldersNumber, bool Position){ //CarHoldersNumber=Numéro du maintien de roue Position=true=déployé false=replié
  if (Position==true&&CarHoldersPosition[CarHoldersNumber]==false){
    CarHolders[CarHoldersNumber].write(90);  
    CarHoldersPosition[CarHoldersNumber]=true;
  }
  else if (Position==false&&CarHoldersPosition[CarHoldersNumber]==true){
    CarHolders[CarHoldersNumber].write(0);
    CarHoldersPosition[CarHoldersNumber]=false;
  }
}

void BarrierOpen(String(Barrier), bool Position){  //Barrier=E pour la barrière d'entrée S pour la barrière de sortie Position=true=ouverte false=fermée
  if (Barrier=="E"){
    if (Position==true&&EntryBarrierPosition==false){
      EntryBarrier.write(90);
      EntryBarrierPosition=true;
    }
    else if (Position==false&&EntryBarrierPosition==true){
      EntryBarrier.write(0);
      EntryBarrierPosition=false;
    }
  }
  else if (Barrier=="S"){
    if (Position==true&&ExitBarrierPosition==false){
      ExitBarrier.write(90);
      ExitBarrierPosition=true;
    }
    else if (Position==false&&ExitBarrierPosition==true){
      ExitBarrier.write(0);
      ExitBarrierPosition=false;
    }
  } 
}

void ShowAvailableSpots (){
  int FreeSpots=0;
  for (int i=0; i<20; i++){
    if (TakenSpots[i]==false){
      FreeSpots++;
    }
    Serial.println("Places libres: " + FreeSpots);
    ///////////////////////////A FAIRE//////////////////////////// Afficher FreeSpots sur l'écran
  }
}

void PlatformInit(){

Serial.println("Déplacement plateforme en position initiale");
TranslatePlatform.write(0);
RotatePlatform.write(0);
while(digitalRead(Floor0Sensor)==HIGH){
    digitalWrite(EnableBridgePin, HIGH);
    analogWrite(ElevatorUpPin, 0);
    analogWrite(ElevatorDownPin, Power);
  }
}

void MoveTo(int Floor,int Angle){
  analogWrite(ElevatorDownPin,0); //On s'assure qu'il ne tournera pas dans l'autre sens
  analogWrite(ElevatorUpPin,Power); //On monte l'ascenseur
  RotatePlatform.write(Angle); //On tourne la plateforme

  if(Floor==1&&digitalRead(Floor1Sensor)==LOW){ //Si la place est au premier étage
    digitalWrite(EnableBridgePin, LOW); //On désactive le pont
    TranslatePlatform.write(90); //On déplace la plateforme vers la place
    delay(1000); //On attend 1 seconde
    int PlaceNumber=i+1; //On détermine le numéro de la place
    if(digitalRead("CarSensorSpot"+PlaceNumber)==LOW){ //Si la voiture est bien placée
      TakenSpots[i]=true; //On met à jour le tableau des places de parking
      ShowAvailableSpots(); //On affiche le nombre de places disponibles
      PlatformInit(); //On remet la plateforme en position initiale
    }
   }
  if(Floor==2&&digitalRead(Floor2Sensor)==LOW){ //Si la place est au deuxième étage
    digitalWrite(EnableBridgePin, LOW); //On désactive le pont
    TranslatePlatform.write(90); //On déplace la plateforme vers la place
    delay(1000); //On attend 1 seconde
    int PlaceNumber=i+1;
    if(digitalRead("CarSensorSpot"+PlaceNumber)==LOW){ //Si la voiture est bien placée
      ShowAvailableSpots(); //On affiche le nombre de places disponibles
      PlatformInit(); //On remet la plateforme en position initiale
    }
  }
}
//-------------------------------------------------
//------------- BOUCLE INFINIE --------------------
//-------------------------------------------------

void loop() 
{
  enum liste_etat{STOP,INIT,EXIT,ENTRY,CARPLACEMENT,MOVING,PAYEMENT,DELIVERY,FIRE,INTRUSION,ERROR};   //Liste des états
  switch(ETAT){ //On regarde dans quel état on est

    case STOP: 
    digitalWrite(EnableBridgePin;LOW); //On désactive le pont en H de l'ascenceur
    digitalWrite(AvailableSpotsScreenPin, LOW); //Ecran éteint
    if (digitalRead(PowerButton) == HIGH) {ETAT=INIT;} //Si le bouton d'alimentation est appuyé, on passe à l'état INIT
    break;


    case INIT:
    digitalWrite(EnableBridgePin;HIGH); //On active le pont en H de l'ascenceur
    digitalWrite(AvailableSpotsScreenPin, HIGH); //Ecran allumé
    BarrierOpen("S",false); //On ferme la barrière de sortie
    BarrierOpen("E",false); //On ferme la barrière d'entrée
    if(digitalRead(CarSensorPlatform)==LOW){ //S'il n'y a pas de voiture sur la plateforme
      for (int i=0;i<4;i++){  //Boucle pour les maintiens de roue 
          CarHoldersDeploy(i,false); //On replie les maintiens de roue
        }
      }
    TranslatePlatform.write(0); //On déplace la plateforme vers le centre
    RotatePlatform.write(0); //On tourne la plateforme vers l'entrée
    digitalWrite(ElevatorPin, LOW); //On descend l'ascenseur
    for (int i=0; i<20; i++){ //Boucle pour les capteurs de voiture sur les places
      if (digitalRead(CarSensorSpotPins[i])==LOW){ //Si un capteur de voiture est activé
        TakenSpots[i]=true; //On met à jour le tableau des places de parking
      }
    }
    ShowAvailableSpots(); //On affiche le nombre de places disponibles
    //Changement d'état
    if(digitalRead(EntryDesk)==HIGH){ETAT=ENTRY;} //Si le bouton de l'entrée est appuyé, on passe à l'état ENTRY
    if(digitalRead(ExitDesk)==HIGH){ETAT=PAYEMENT;} //Si le bouton de la sortie est appuyé, on passe à l'état PAYEMENT
    break;


    case EXIT:
    if
    break;

    case ENTRY:
    ///////////////////////////A FAIRE//////////////////////////////On scanne la plaque d'immatriculation
    if(TicketAvailable==true){
      digitalWrite(TicketsDispenserPin, HIGH); //On délivre un ticket
      TicketAvailable=false;
      delay(1000); //On attend 1 seconde
      digitalWrite(TicketsDispenserPin, LOW); //On éteint le distributeur de ticket
    }
    BarrierOpen("E",true);  //On ouvre la barrière d'entrée
    if(digitalRead(EntryBarrierSensor)==LOW){
      delay(2000); //On attend 2 secondes
      BarrierOpen("E",false); //On ferme la barrière d'entrée
      ETAT=CARPLACEMENT; //On passe à l'état CARPLACEMENT
    }
    break;

    case CARPLACEMENT:
    if (digitalRead(CarSensorPlatform)==LOW){
      CarHoldersDeploy(0,true);
      //L'utilisateur avance sa voiture jusqu'au capteur sur la barre 1
      if(digitalRead(CarHolders1Sensor)==LOW){  
        CarHoldersDeploy(2,true);
      //L'utilisateur continue d'avancer sa voiture jusqu'au capteur de fin de course sur la barre 1
        if(digitalRead(CarHolders1EndSensor)==LOW){
          CarHoldersDeploy(1,true); 
          CarHoldersDeploy(3,true); 
        }
      }
      static int CarHoldersDeployed=0;
      for (int i=0;i<4;i++){
        if(CarHoldersPosition[i]==true){ 
          CarHoldersDeployed++; //On compte le nombre de maintiens de roue déployés
        }
      if(CarHoldersDeployed==4&&digitalRead(UserIsOutButton)==LOW){ETAT=MOVING;} //Si les 4 maintiens sont ouverts et que le bouton "l'utilisateur est sorti" est appuyé, on passe à l'état MOVING
      }
    }
    break;

    case MOVING:
    for(int i=0;i<20;i++){
      if(TakenSpots[i]==false){    
        MoveTo(SpotsPosition[i][0],SpotsPosition[i][1]); //On se déplace vers la place
        TakenSpots[i]=true; //On met à jour le tableau des places de parking
        ETAT=INIT;
      }
    }
    break;

    case PAYEMENT:
    Serial.println("Scannez votre ticket");
    

    break;

    case DELIVERY:

    break;

    case FIRE:
    
    break;

    case INTRUSION:
    
    break;

    case ERROR:
  
    break;

  }    
}