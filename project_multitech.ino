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

#include <Servo.h>


// Définition des broches...

#define   

        
//-------------------------------------------------
//--------- DECLARATIONS --------------------------
//-------------------------------------------------

  // Déclaration des variables
int ETAT=0;

  // Déclaration des fonctions


    // Instantation d'objet
Servo Servoentree;
Servo Servosortie;

void setup() 
     {      
        //configuration 
  pinMode(A, OUTPUT);

  
        //initialisation
 Servoentree.attach(Entree);
 Servoentree.write(0);
 Servosortie.attach(Sortie);
 Servosortie.write(0);

}
//-------------------------------------------------
//------------- PROCEDURE ET FONCTIONS -----------
//-------------------------------------------------

//  Code des procédures et fonctions


//-------------------------------------------------
//------------- BOUCLE INFINIE --------------------
//-------------------------------------------------

void loop() 
{
  enum liste_etat{};
  switch(ETAT){
    case
    

       }    
   }
