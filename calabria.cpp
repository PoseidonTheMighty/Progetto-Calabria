#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
using namespace std;
// nella funzione di lotta mi da sempre brigante ecc non dichiarati
// mettere la funzione lotta negli accenti

// Character struct
struct tizio {
  char symbol;
} pp;

const int HEIGHT = 25;
const int WIDTH = 25;

const char CORNER_TOP_LEFT = char(191); // Character used for top-left corner +
const char CORNER_BOTTOM_LEFT =
    char(192); // Character used for bottom-left corner +
const char CORNER_BOTTOM_RIGHT =
    char(217); // Character used for bottom-right corner +
const char HORIZONTAL_LINE_BOTTOM =
    char(196);                        // Character used for horizontal lines
const char VERTICAL_LINE = char(179); // vertical lines
const char CORNER = char(218);        //+
const char ENEMY = char(94);
const char CHECKPOINT = char(175);
const char MERCANTI = char(206);
const char BOSS = char(173);
const char HOUSE = char(220);
const int H = 36;
const int W = 27;
const char BACKSLASH = char(92);

const int DMOLO = 20, VMOLO = 15;
const int CBEND = 20, VBEND = 15;
const char blocco = 220;
const char mercante = 206;

struct pg {
  string nome;   // nome del protagonista scelto dal user
  string classe; // la calsse scelta al inizio del gioco dal user
  int life;      // la vita attuale del user
  int lifeMax;   // la vita massima del user
  int armatura;  // la difesa del user
  float aim;     // la precisione del personagio - multiplicatore
  float dex;     // la destrza del personagio - multiplicatore
  float forza;   // la forza del personagio - multiplicator    // le monete del user
} player;
struct nemici {
  string nome;
  int life;
  int attacco;
  int vel;
  int loot;
};
struct weapon {
  string nome; // nome del arma
  char tipo;  // tipologia arma - D scala in dex - F scala in forza - A scala in
              // aim
  int damage; // il danno base del arma
  int vel;    // la velocita del arma
  int valore; // il valore a cui puo essere acquistata o venduta larma
} arma_p;
struct ogetti {
  int money;
  int num_benda;   // per cura
  int num_molotov; // per danno
  //  bool key_cancello = false;
} inventory;

// mercante 1
weapon Ascia_Andranghetista;
weapon Arco_In_Eternit;
weapon Spada_Calabra;
// mercante 2
weapon Pipi_Patate;
weapon Fionda_fitusa;
weapon Mannaia;
// mercante 3
weapon Scarpa_cemento;
weapon Cunnu_Babbu;
weapon Nduja_ardente;
// mercante 4
weapon Mazza_Omertosa;
weapon Scoppieto;
weapon Striscia_Cutrese;

// boss
nemici Ndrina_Grande_Aracri;
nemici Antonio_Dragone;
nemici Rocco_Morabito;
nemici Luigi_Mancuso;
// nemici base
nemici mastro;
nemici puntaiolo;
nemici piccioto;
nemici Mammasantissima;
nemici Bartolo;

int Sell_Multipli(int oggetto);
bool money(int prezzo);
int Mercante(weapon arma3, weapon arma4, weapon arma5);
int Sell();
bool probabilita();
int attacco_personaggio();
int DannoP(int attaco);
void Seta_Arma(weapon imposta); // setta larma del player con una nuova
bool cont_intervallo(
    bool mes, int v, int minV,
    int maxV); // verifica che un vaore rientri in un intervallo
char ver_sn(char sn, char a,
            char b); // chiede un cin finche il char non e previsto dal softwer
char minuscolo(char caratere);  // trasforma tutti i carateri in minuscolo
void chose_pg();                // scelta iniziale della classe
void comercio(int ID_mercante); // funzione per vendita e acquisti
void StampaVita();              // stampa la vita del player
void StampaVitaNemici(int le, string nome); // stampa la vita dei nemici
void SET_ALL(); // setta tutte le carateristiche delle variabili strutturate
bool lotta(nemici nemico); // avvia i combatimenti e li gestisce
void MegaCout(char arr[], double DA,
              int T);          // stampa la roba lentamente in modo figo
void gotoxy(short x, short h); // setta le cordinate di stampa cout
void caratt_pg();              // stampa linventario
void clean();                  // pulisce la mappa senza tocare linventario
void caricamento();            // stampa caricamento perche fa figo
int calabria();
int reggio(int IDm, nemici boss, bool morte);
void BostStats(int x);
void morte(int m, int b);

// KEY queste key  servono al programmatore per gestire l'accesso alle zone di mappe in modo da far seguire al utente  un percorso che poi a sua volta dopo la scoperta potra girare alla scoperta di nuovi nemici e avventure infatti nella storia l'utente non si rende conto di aver usato una chiave 
bool KEY1 = false;
bool KEY2 = false;
bool KEY3 = false;

bool boss1 = true;
bool boss2 = true;
bool boss3 = true;
bool boss4 = true;

bool D1 = true;
bool D2 = true;
bool D3 = true;
bool D4 = true;
bool D5 = false;

bool Ester1=true;
bool Ester2=true;

// cout // i numeri affianco stanno per i caratteri che contiene la frase serve per far avvenire l'effetto di scrittura in mega cout 
char msg0[69] =
    "Ti diamo il Benvenuto a questa nuova avvenutura: Ndrangheta The Game";
char msg1[590] =
    "Sei un apposionato dell'esplorazione di posti sconosciuti,\n "
    "decidi di andare in Marocco, per incontrare i famosi Hashashin \n ma "
    "durante il viaggio vai in contro a una forte tempesta che ti fa "
    "naufragare in un luogo sconosciuto,\n ti dirigi in una taverna in cerca di "
    "informazioni e scopri di essere sbarcato nel famoso paese delle scimmie, "
    "La CALABRIA!!!\n per l'immensa felicitá decidi di divertiti un po' ma "
    "finisci per nbriacarti troppo e in una rissa ammazzi un membro della "
    "mafia locale, ora ti stanno cercando l'unico modo per salvarti e "
    "cercarli, trovarli e uciderli";
char msg2[150] = "Per muoverti puoi utilizzare i tasti w,a,s,d, per iniziare "
                 "la tua avventura inizia ad andare verso Reggio Calabria "
                 "dirigendoti verso il Checkpoint 1";
char msg3[232] = "mentre esplori reggio calabria ti imbatti in un gruppo "
                 "terroni pronti ad uciderti, \n per fortuna hai la meglio e "
                 "constringi uno di loro a dirti dove si trovi il boss \n ti "
                 "dirigi in via delle rose dove ti aspetta uno scontro epico";
char msg4[90] = "sconfitto Grande aracri arrivano i suoi uomini costringendoti "
                "a scapare verso cosenza";
char msg5[305] =
    "Hai seminato gli uomini di Grande aracri e sei arrivato a cosenza \n "
    "voresti andare in un pub ma dopo lultima volta non ti sembra un ottima "
    "idea....\n mentre passegi per la citta senti narare da un bardo del "
    "crocifisso di antonio dragone \n che ti dara le abilita necesarie a "
    "proseguire nel tuo viaggio";
char msg6[285] =
    "il tuo sterminio sta iniziando a dare nel ochio, mentre andavi a "
    "rifornirti al mercato lesatore del pizzo ti recapita un messagio da parte "
    "di Rocco Morabito \n ti invita nella sua villa a crotone per discutere di "
    "un alleanza e degli ultimi avenimenti \n cosa potrebbe mai andare storto";
char msg7[420] =
    "alle porte della citta dal fumo dei bidoni in fiamme compare un losco "
    "figuro, si tratta di Rocco Morabito \n Rocco:'viste le tue gesta si puo "
    "dire che la tua forza e strabiliante, ma lo stesso non lo si puo dire per "
    "il tuo intelletto' \n si trattava di una trappola chi lavrebbe mai detto, "
    "non resta altro che combatere";
char msg8[184] =
    "Rocco: 'sarai pure riuscito a sconfigere me ma non puoi far nulla contro "
    "Mancuso, hai i giorni contati Figghi’e bottan' \n bhe meglio uciderlo te "
    "prima che sia lui a farlo non pensi";
char msg9[270] =
    "Appena arrivato noti subito la differenza di civilizzazione che se pur "
    "molto bassa, rispetto alle altre citta e comunque di spicato livello , "
    "cio e dovuto alla possizione piu a nord della citta \n tuttavia intravedi "
    "subito il tuo obbietivo\n il famigerato Luigi Mancuso";
char msg10[227] =
    "Mancuso: 'bhe complimenti, sei riuscito a uciderci tutti...ma non pensare "
    "che tu abbia salva la vita\n il vero nemico non siamo noi e la calabria "
    "stessa \nnon importa cosa farai un giorno questa terra ti mortera al "
    "altro mondo'";
char msg11[142] =
    "Passano gli anni e dopo esserti stabilito in calabria contro ogni logica "
    "un bel giorno devi andare a cutro in provincia di crotone per affari";
char msg12[100] = "non sei mai stato a cutro in tutti questi anni,ma ne hai "
                  "sentio parlare molto spesso";
char msg13[50] = "sempre male ma ne hai comunque sentito parlare";
char msg14[140] =
    "Mentre eri intento a prenderti un passegio alla viletta tra i fumatori di "
    "opio e le famigliole, vieni caricato di violenza su una carroza";
char msg15[160] = "Si presenta a te un losco figuro con la sua banda, si "
                  "presenta solo con il nome di D'angello \n D'angello:'hai "
                  "ucciso mio zio, il Grande aracri la pagherai'";
char msg16[101] = "vieni portato allo stecato dove vieni costretto a scavarti "
                  "la fossa, alla fine Mancuso aveva ragione";
// MAIN 
int main() {

  srand(time(NULL));

  SET_ALL();
  MegaCout(msg0, 69, 100);
  clean();
  chose_pg();
  system("cls");
  MegaCout(msg1, 590, 30);
  MegaCout(msg2, 150, 100);
  calabria();
  system("cls");
  MegaCout(msg4, 90, 100);
  system("cls");
  calabria();
  system("cls");
  MegaCout(msg6, 285, 30);
  system("cls");
  calabria();
  system("cls");
  MegaCout(msg8, 184, 50);
  system("cls");
  calabria();
  system("cls");
  MegaCout(msg10, 227, 30);
  system("cls");
  MegaCout(msg11, 142, 50);
  system("cls");
  D5 = true;
  calabria();
  system("cls");
  MegaCout(msg12, 100, 70);
  MegaCout(msg13, 50, 35);
  MegaCout(msg14, 140, 70);
  MegaCout(msg15, 160, 70);
  MegaCout(msg16, 101, 30);
  system("cls");
  Sleep(3500);
  cout << "FINE" << endl;

  return 0;
}
// in questa funzione dichiariamo varie variabili di tipo nemici (struct) e ognuno di essi ha caratteristiche precise in base all proprio utilizzo nel gioco 
void SET_ALL() {
  // NEMICI
  // boss
  Ndrina_Grande_Aracri.nome = "Ndrina Grande Aracri";
  Ndrina_Grande_Aracri.life = 160;
  Ndrina_Grande_Aracri.attacco = 35;
  Ndrina_Grande_Aracri.vel = 2;
  Ndrina_Grande_Aracri.loot = 60;

  Antonio_Dragone.nome = "Antonio Dragone";
  Antonio_Dragone.life = 210;
  Antonio_Dragone.attacco = 15;
  Antonio_Dragone.vel = 4;
  Antonio_Dragone.loot = 100;

  Rocco_Morabito.nome = "Rocco Morabito";
  Rocco_Morabito.life = 230;
  Rocco_Morabito.attacco = 65;
  Rocco_Morabito.vel = 1;
  Rocco_Morabito.loot = 120;

  Luigi_Mancuso.nome = "Luigi Mancuso";
  Luigi_Mancuso.life = 190;
  Luigi_Mancuso.attacco = 40;
  Luigi_Mancuso.vel = 3;
  Luigi_Mancuso.loot = 1000;
  // base

  mastro.nome = "Mastro";
  mastro.life = 100;
  mastro.attacco = 35;
  mastro.vel = 2;
  mastro.loot = 30;

  puntaiolo.nome = "Puntaiolo";
  puntaiolo.life = 70;
  puntaiolo.attacco = 15;
  puntaiolo.vel = 1;
  puntaiolo.loot = 20;

  piccioto.nome = "Piccioto";
  piccioto.life = 90;
  piccioto.attacco = 20;
  piccioto.vel = 1;
  piccioto.loot = 10;

  Mammasantissima.nome = "Mamma Santissima";
  Mammasantissima.life = 110;
  Mammasantissima.attacco = 50;
  Mammasantissima.vel = 1;
  Mammasantissima.loot = 60;

  Bartolo.nome = "Luigi Mancuso";
  Bartolo.life = 90;
  Bartolo.attacco = 40;
  Bartolo.vel = 1;
  Bartolo.loot = 25;

  // ARMI
  //  armi forza F
  //  Ascia_Andranghetista
  // andiamo a inizializzare le armi che troveremo dal mercante e non durante il gioco e queste armi sono del tipo weapon (struct);
  Ascia_Andranghetista.nome = "Ascia Ndranghetista";
  Ascia_Andranghetista.tipo = 'F';
  Ascia_Andranghetista.damage = 70;
  Ascia_Andranghetista.vel = 3;
  Ascia_Andranghetista.valore = 70;

  // Pipi_Patate
  Pipi_Patate.nome = "Pipi e Patate";
  Pipi_Patate.tipo = 'F';
  Pipi_Patate.damage = 95;
  Pipi_Patate.vel = 3;
  Pipi_Patate.valore = 100;

  // Scarpa_cemento
  Scarpa_cemento.nome = "Scarpa di cemento";
  Scarpa_cemento.tipo = 'F';
  Scarpa_cemento.damage = 130;
  Scarpa_cemento.vel = 3;
  Scarpa_cemento.valore = 110;

  // Mazza_Omertosa
  Mazza_Omertosa.nome = "Mazza Omertosa";
  Mazza_Omertosa.tipo = 'F';
  Mazza_Omertosa.damage = 135;
  Mazza_Omertosa.vel = 4;
  Mazza_Omertosa.valore = 120;

  // armi dex D
  // Spada calabra
  Spada_Calabra.nome = "Spada Calabra";
  Spada_Calabra.tipo = 'D';
  Spada_Calabra.damage = 20;
  Spada_Calabra.vel = 4;
  Spada_Calabra.valore = 50;
  // Mannaia
  Mannaia.nome = "Mannaia";
  Mannaia.tipo = 'D';
  Mannaia.damage = 55;
  Mannaia.vel = 6;
  Mannaia.valore = 90;
  // Nduja_ardente
  Nduja_ardente.nome = "Nduja Ardente";
  Nduja_ardente.tipo = 'D';
  Nduja_ardente.damage = 55;
  Nduja_ardente.vel = 7;
  Nduja_ardente.valore = 80;
  // Striscia_Cutrese
  Striscia_Cutrese.nome = "Striscia Cutrese";
  Striscia_Cutrese.tipo = 'D';
  Striscia_Cutrese.damage = 70;
  Striscia_Cutrese.vel = 7 ;
  Striscia_Cutrese.valore = 90;

  // armi aim A
  // arco in eternit
  Arco_In_Eternit.nome = "Arco In Eternit ";
  Arco_In_Eternit.tipo = 'A';
  Arco_In_Eternit.damage = 90;
  Arco_In_Eternit.vel = 2;
  Arco_In_Eternit.valore = 50;

  // Fionda_fitusa
  Fionda_fitusa.nome = "Fionda Fitusa ";
  Fionda_fitusa.tipo = 'A';
  Fionda_fitusa.damage = 80;
  Fionda_fitusa.vel = 4;
  Fionda_fitusa.valore = 50;

  // Cunnu_Babbu
  Cunnu_Babbu.nome = "CUNNO BABBU";
  Cunnu_Babbu.tipo = 'A';
  Cunnu_Babbu.damage = 90;
  Cunnu_Babbu.vel = 3;
  Cunnu_Babbu.valore = 50;

  // Scoppieto
  Scoppieto.nome = "Scoppieto";
  Scoppieto.tipo = 'A';
  Scoppieto.damage = 150;
  Scoppieto.vel = 1;
  Scoppieto.valore = 50;

} // funzione per setare tutte le struct del gioco

// funzioni lotta
// questa funzione vera usata nei combattimenti e indica la probabilità che il tuo colpo e quello del nemico vengano messi a segno 
bool probabilita() {
  int prob = 1 + (rand() % 100);
  if (prob < 60) {
    return true;
  } else {
    return false;
  }
}
// attacco personaggio e uan funzione che crea e somma le varie variabili che vanno ad incidere nell' attacco del personaggio e questi sono il tipo di arma , e aim dex e forza in base alla scelta del personaggio iniziale 
int attacco_personaggio() {
  if (arma_p.tipo == 'F') {
    return (player.forza * arma_p.damage);
  }

  else if (arma_p.tipo == 'D') {
    return player.dex * arma_p.damage;
  }

  else if (arma_p.tipo == 'A') {
    return player.aim * arma_p.damage;
  }

  return 0;
}
//
int DannoP(int attaco) {
  int D = attaco - ((attaco / 100) * player.armatura);
  return D;
}
// serve per combattere contro i nemici caricamento serve per creare in modo grafico un caricamento
bool lotta(nemici nemico) {
  caricamento();

  int N_ogg;
  int DC_ogg;
  bool controllo;
  char vbn = ' ';

  int Att_P = attacco_personaggio();
  // carratt_pg e una funzione che ci permette la stampa delle caratteristiche del personaggio a lato dello schermo grazie alla funzione gotoxy che permette il posizionamento dei cout secondo delle cordinate la prima cordinata sta per le colonne la seconda per le righe 
  caratt_pg();
// hai la scelta e possibilita di usare o bende o molotov 
  do {
    if (inventory.num_molotov > 0 || inventory.num_benda > 0) {
      cout << "Vuoui usrae una molotov/benda/nulla??  (m/b/n)  " << endl;
      //vbn sta per : 
      do {
        cin >> vbn;
        vbn = minuscolo(vbn);
        if (vbn != 'n' && vbn != 'n' && vbn != 'b') {
          controllo = true;
          cout << " il caratere inserito non e coretto, reinseriscilo" << endl;
        } else {
          controllo = false;
        }
      } while (controllo == true);
    } else if (inventory.num_molotov > 0) {// chiedi se l'utente vuole usare la molotov oppure no con vbn 
      cout << "Vuoui usrae una molotov/nulla??  (n/m)  " << endl;
      //controlla i caratteri che inserisci si basa sulla tabella ascii e mette in piccolo le scritte in modo da togliersi il problema di dover controllare la variabile char con i caratteri scritti in grande 
      vbn = ver_sn(vbn, 'n', 'm');
    } else if (inventory.num_benda > 0) {
      cout << "Vuoui usrae una benda/nulla?? (b/n)  " << endl;
      vbn = ver_sn(vbn, 'b', 'n');
    }
// nel caso vbn diverso da no controlli qual'e la scelta che hai inserito che sara per forza o bende o molotov 
    if (vbn != 'n') {
      // in questo switch io chiedo quante bende vuole usare e calcolo la cura nel caso delle bende se l'utente ne vuole usare qualcuna e danno nel caso delle molotov ovviamente proporzionate al nunero di oggetti che si vogliono usare 
      switch (vbn) {

      case 'b':

        cout << " quante bende vuoi usare? " << endl;
        do {
          cin >> N_ogg;
        } while (N_ogg > inventory.num_benda);

        DC_ogg = N_ogg * DMOLO;
        nemico.life -= DC_ogg;
        inventory.num_molotov -= N_ogg;

        break;
      case 'm':// ho messo m perché prima c'era n ma non era corretto credo 

        cout << " quante molotov vuoi usare ? " << endl;
        do {
          cin >> N_ogg;
        } while (N_ogg > inventory.num_molotov);

        DC_ogg = N_ogg * CBEND;
        player.life += DC_ogg;
        inventory.num_benda -= N_ogg;

        break;
      }
    }

    // attaco giocatore in questa parte di codice uso un for che fa ciclare e percio " somma l'attacco " in base alla velocità dell' arma che fa parte della struct nemici inoltre c'è pure la probabilità del 60 % che ogni colpo vada a segno , poi si va a scalare la vita del nemico e viceversa e inoltre viene stampato il valore della vita sia del personaggio che del nemico 
    
    for (int i = 0; i < arma_p.vel; i++) {
      int x = probabilita();
      if (x == true) {
        cout << "hai colpito " << nemico.nome << "infligendogli " << Att_P
             << endl;
        nemico.life -= Att_P;
      } else if (x == false) {
        cout << "hai mancato " << nemico.nome << endl;
      } else {
        cout << nemico.nome << " ti ha schivato" << endl;
      }
      // ha la funzione di delay 
      Sleep(1500);
    }
    StampaVita();
    cout << endl;

    // attaco nemico
    for (int i = 0; i < nemico.vel; i++) {
      int x = probabilita();
      if (x == true) {
        cout << nemico.nome << " ti ha colpito, inflingendoti "
             << nemico.attacco << endl;
        player.life -= DannoP(nemico.attacco);

      } else if (x == false) {
        cout << "Hai schivato " << nemico.nome << endl;
      } else {
        cout << nemico.nome << " ti ha mancato" << endl;
      }
      Sleep(1500);
    }
    StampaVitaNemici(nemico.life, nemico.nome);
    cout << endl;
// con questo do while ciclo la battaglia fino alla morte di uno dei due 
  } while (nemico.life > 0 && player.life > 0);
// dopo il do while faccio questi controlli per stampare chi dei due ha vinto 
  if (nemico.life < 1 && player.life > 0) {
    caratt_pg();
    cout << "Hai ottenuto " << nemico.loot << endl;
    inventory.money += nemico.loot;
    return true;
  } else if (nemico.life > 0 && player.life < 1) {
    cout << "Sei stato sconfito da" << nemico.nome << endl;
    return false;
  } else {
    cout << "avete paregiato" << endl;
    return false;
  }
  system("cls");
}
//------------------------------------
void Seta_Arma(weapon imposta) {
  arma_p = imposta;
  cout << " la tua nuova arma " << arma_p.nome << endl
       << " di tipo " << arma_p.tipo << endl;
  cout << " danno =  " << arma_p.damage << " velocita " << arma_p.vel << endl;
} // fuznione che asegna al user un arma x usata nella funzione del mercante perché scambia le armi e percio i valori si essa 

// chose_pg e la funzione che ci permette di selezionare con quale personaggio iniziare il gioco 
void chose_pg() {
  int classe;
  const int NMCLASSE = 3;
  cout << endl;
  gotoxy(0, 1);
  cout << "\t  _____________________________________________________ \n";
  gotoxy(0, 2);
  cout << "\t |                    |                |               |\n";
  gotoxy(0, 3);
  cout << "\t |  CAVALLIERE        |  ARCERE        |  MASTINO      |\n";
  gotoxy(0, 4);
  cout << "\t |____________________|________________|_______________|\n";
  gotoxy(0, 5);
  cout << "\t |                    |                |               |\n";
  gotoxy(0, 6);
  cout << "\t |  vitamax : 100     |  vitamax : 80  | vitamax : 120 |\n";
  gotoxy(0, 7);
  cout << "\t |  aim : 0,6         |  aim : 2       | aim : 0,3     |\n";
  gotoxy(0, 8);
  cout << "\t |  forza : 0,6       |  forza : 0,3   | forza : 1,4   |\n";
  gotoxy(0, 9);
  cout << "\t |  dex : 1,4         |  dex : 0,6     | dex : 0,6     |\n";
  gotoxy(0, 10);
  cout << "\t |  armatura: 20      |  armatura: 10  | armatura: 30  |\n";
  gotoxy(0, 11);
  cout << "\t |____________________|________________|_______________|\n";
  gotoxy(0, 12);
  cout << "\t |                    |                |               |\n";
  gotoxy(0, 13);
  cout << "\t |  ARMA BASE         |  ARMA BASE     |  ARMA BASE    |\n";
  gotoxy(0, 14);
  cout << "\t |____________________|________________|_______________|\n";
  gotoxy(0, 15);
  cout << "\t |                    |                |               |\n";
  gotoxy(0, 16);
  cout << "\t |  danno : 60        |  danno : 50    |  danno : 30   |\n";
  gotoxy(0, 17);
  cout << "\t |  tipo : D          |  tipo : A      |  tipo : F     |\n";
  gotoxy(0, 18);
  cout << "\t |  velocita : 3      |  velocita : 2  |  velocita : 1 |\n";
  gotoxy(0, 19);
  cout << "\t |____________________|________________|_______________|\n";
  gotoxy(0, 20);
  cout << " LA CLASSE 1 = CAVALIERE ,LA CLASSE 2 = ARCIERE,LA CLASSE 3 = "
          "MASTINO "
       << endl;
  gotoxy(0, 21);
  cout << "\t SCEGLI : ";
  do {
    cin >> classe;
  } while (!cont_intervallo(true, classe, 1, NMCLASSE));
  switch (classe) {
  case 1:
    player.lifeMax = 140;
    player.classe = "Cavalliere";
    player.aim = 0.6;
    player.life = 140;
    player.forza = 0.6;
    player.dex = 2;
    player.armatura = 20;
    arma_p.nome = "BASE";
    arma_p.damage = 60;
    arma_p.tipo = 'D';
    arma_p.vel = 4;
    break;
  case 2:
    player.lifeMax = 120;
    player.classe = "Arcere";
    player.life = 120;
    player.aim = 2.2;
    player.forza = 0.3;
    player.dex = 0.6;
    player.armatura = 10;
    arma_p.nome = "BASE";
    arma_p.damage = 50;
    arma_p.tipo = 'A';
    arma_p.vel = 2;
    break;
  case 3:
    player.lifeMax = 170;
    player.classe = "Mastino";
    player.life = 170;
    player.aim = 0.3;
    player.forza = 1.8;
    player.dex = 0.6;
    player.armatura = 30;
    arma_p.nome = "BASE";
    arma_p.damage = 40;
    arma_p.tipo = 'F';
    arma_p.vel = 1;
    break;
  }
  cout << "\t QUAL'E IL TUO NOME ? :  ";
  cin >> player.nome;
  caratt_pg();
} // funzione iniziale scelta classe

// funzioni vendita

int Sell() {

  int NV_max;
  int NV;
  char risposta = ' ';
  if (inventory.num_benda == 0 && inventory.num_molotov == 0) {
    cout << "\t NON PUOI VENDERE NULLA PERCHE NON HAI NULLA NELL'INVENTARIO \n "
         << endl;
    return 0;
  }
  cout << "cosa vuoi vendere? (m/b) " << endl;
  risposta = ver_sn(risposta, 'm', 'b');
  switch (risposta) {
  case 'm':
    NV_max = inventory.num_molotov;
    break;
  case 'b':
    NV_max = inventory.num_benda;
    break;
  }

  cout << "quanti oggetti vuoi vendere?" << endl;
  do {
    cin >> NV;
  } while (cont_intervallo(true, NV, 0, NV_max));
  ;
  switch (risposta) {

  case 'm':
    inventory.money = inventory.money - (VMOLO * NV);
    inventory.num_molotov = inventory.num_molotov - NV;
    break;

  case 'b':
    inventory.num_benda -= NV;
    inventory.money += NV * VBEND;
    break;
  }

  cout << "vuoi vendere ancora? (s/n)" << endl;
  risposta = ver_sn(risposta, 's', 'n');
  if (risposta == 's') {
    Sell();
  }
  return 0;
} // funzione per la venmdita da parte del player
int Mercante(weapon arma3, weapon arma4, weapon arma5) {
  bool controllo;
  int risposta;
  int acquisto;

  gotoxy(0, 0);

  cout << "Benvenuto nella bottega degli Antichi Sapori Esploratore \n, ho "
          "sentito dire che un certo uomo Bizantino e perseguitato dalla mafia "
          "locale,\n dalla descrizione mi sembri tu, il che vuol dire che ti "
          "serviranno delle armi adatte per proteggerti,\n e stranamente io ne "
          "sono in possesso e sono anche disposto a vendertele!! "
       << endl;

  cout << "per uscire dal menu inserisci 0" << endl;
  cout << "---------------------------OGETTI-----------------------------"
       << endl;
  cout << "   NOME                         VALORE  " << endl;
  cout << "1) MOLOTOV                 |" << VMOLO << "| DANNO CONSUMABILE ("
       << DMOLO << ")" << endl;
  cout << "2) BENDA                   |" << CBEND << "| CURA CONSUMABILE ("
       << CBEND << ")" << endl;
  cout << "----------------------------ARMI------------------------------";
  cout << endl << endl;
  cout << "3) " << arma3.nome << " | " << arma3.valore << " |  DEX  DANNO("
       << arma3.damage << ") "
       << "VElOCITA(" << arma3.vel << ")" << endl;
  cout << "4) " << arma4.nome << " | " << arma4.valore << " |  DEX  DANNO("
       << arma4.damage << ") "
       << "VElOCITA(" << arma4.vel << ")" << endl;
  cout << "5) " << arma5.nome << " | " << arma5.valore << " |  DEX  DANNO("
       << arma5.damage << ") "
       << "VElOCITA(" << arma5.vel << ")" << endl;
  cout << "---------------------------------------------------------------"
       << endl;
  do {

    cout << "\t COSA VUOI ACQUISTARE? \n " << endl;
    do {
      cin >> acquisto;
    } while (!cont_intervallo(true, acquisto, 0, 5));

    switch (acquisto) {
    case 0:
      return 0;
      break;
    case 1:
    case 2:
      Sell_Multipli(acquisto);
      break;
    case 3:
      if (money(arma3.valore) == true) {
        Seta_Arma(arma3);
      }
      break;
    case 4:
      if (money(arma4.valore) == true) {
        Seta_Arma(arma4);
      }
      break;
    case 5:
      if (money(arma5.valore) == true) {
        Seta_Arma(arma5);
      }
      break;
    }
    cout << "vuoi procedere con altri acquisti?  (s/n)  " << endl;
    risposta = ver_sn(risposta, 's', 'n');
    if (risposta == 's') {
      controllo = true;
    } else {
      controllo = false;
    }
  } while (controllo);
  return 0;
}
bool money(int prezzo) { // funzione che verifica cel l'user abbia abbastanza
                         // soldi per acquistare dal mercante
  if (inventory.money >= prezzo) {
    cout << "\t SOLDI SUFICENTI  " << endl;
    inventory.money = inventory.money - prezzo;
    return true;
  } else {
    cout << "\t Non hai abbastanza soldi mi dispiace \n " << endl;
    return false;
  }
} // funzione per calcolo soldi player
int Sell_Multipli(int oggetto) {
  int N_oggetti;
  int costo;
  cout << "QUANTE NE VUOI COMPRARE?" << endl;
  cin >> N_oggetti;
  switch (oggetto) {
  case 1:
    costo = VMOLO * N_oggetti;
    if (money(costo) == true) {
      inventory.num_molotov += N_oggetti;
    }
    break;
  case 2:
    costo = VBEND * N_oggetti;
    if (money(costo) == false) {
      inventory.num_benda += N_oggetti;
    }
    break;
  }
  return 0;
} // funzione per vendere oggetti multipli
void comercio(int ID_mercante) {
  // prototipazioni per il comercio
  char risposta = ' ';
  int SaveID = ID_mercante;
  // bool controllo;

  bool money(int prezzo);
  int Sell_Multipli(int oggetto);
  int Mercante(weapon arma3, weapon arma4, weapon arma5);
  Sell();
  caratt_pg();
  cout << "Vuoi vendere o acquistare oggetti? (a/v) " << endl;
  risposta = ver_sn(risposta, 'a', 'v');
  if (risposta == 'v') {
    ID_mercante = 0;
  }
  if (risposta == 'a') {
    ID_mercante = SaveID;
  }
  switch (ID_mercante) {
  case 0:
    Sell();
    break;
  case 1:
    Mercante(Ascia_Andranghetista, Spada_Calabra, Arco_In_Eternit);
    break;
  case 2:
    Mercante(Pipi_Patate, Mannaia, Fionda_fitusa);
    break;
  case 3:
    Mercante(Scarpa_cemento, Nduja_ardente, Cunnu_Babbu);
    break;
  case 4:
    Mercante(Mazza_Omertosa, Striscia_Cutrese, Scoppieto);
    break;
  }

  cout << "vuoi uscire dal mercato o riprendere col comercio? (u/r) " << endl;
  risposta = ver_sn(risposta, 'u', 'r');
  if (risposta == 'u') {
    comercio(SaveID);
  } else if (risposta == 'r') {
    system("cls");
    calabria();

  }
  system("cls");
  caratt_pg();
} // funzione per vendita e acquisti

//---------------------------------------
// questa funzione stampa la vita in cuori in base alla vita della persona 
void StampaVita() {
  const char cuore = 3;
  const int cuori = 10;
  int NC;
  if (player.life <= cuori) {
    NC = cuori;
  } else {
    NC = player.life / cuori;
  }

  for (int i = 0; i < NC; i++) {
    cout << cuore;
  }

  // cout << " | " << player.life << "/" << player.lifeMax;
};

void StampaVitaNemici(int life, string nome) {
  const char cuore = 3;
  const int cuori = 10;
  int NC;

  if (life <= cuori) {
    NC = cuori;
  } else {
    NC = life / cuori;
  }
  cout << nome << " ha |";
  for (int i = 0; i < NC; i++) {
    cout << cuore;
  }
}
//qui faccio dei cout con la dissolvenza graze all uso di un for che stampa il valore di una variabile char e con lo sleep creo l'effetto dissolvenza 
void MegaCout(char arr[], double DA, int T) {

  for (int i = 0; i < DA; i++) {
    cout << arr[i];
    Sleep(T);
  }
  cout << endl;
  system("pause");
}
// controlla che il valore inserito rispetta i limiti prestabiliti attraverso una variabile booleana che e falsa se il valore inserito e maggiore o minore della soglia prestavilita 
bool cont_intervallo(bool mes, int v, int minV, int maxV) {
  if (v >= minV && v <= maxV) {
    return true;
  } else if (v < minV) {
    if (mes == true) {
      cout << "\t IL VALORE INSERITO E SOTTO LA SOGLIA MINIMA " << endl;
    }
    return false;
  } else if (v > maxV) {
    if (mes == true) {
      cout << "\t IL VALORE INSERITO E SOPRA LA SOGLIA MASSIMA" << endl;
    }
    return false;
  }

  return 0;
}
// controllo dei char sn lo metto in minuscolo con la funzione minuscolo e uso una variabile booleana per gestire i char ( se variabile boleana e sempre falsa , i valori inseriti sono accettati ) , a e b sono altri char che il programmatore nel momento della chiamata della funzione va a cambiare in base alle due possibili risposte interessate 
char ver_sn(char sn, char a, char b) {
  bool controllo = false;
  do {
    cin >> sn;
    sn = minuscolo(sn);
    if (sn == a) {
      return sn;
    } else if (sn == b) {
      return sn;
    } else {
      cout << "il caratere inserito non e contemplato" << endl << "Ritenta:";
      controllo = true;
    }
  } while (controllo);
  return 0;
} // funzione per determinare linserimento di 2 caratteri
char minuscolo(char caratere) {
  if (caratere >= 65 && caratere <= 65) {
    caratere += 32;
  }
  return caratere;
} // funzione per trasformare maiuscole in minuscole

// in questa funzione aumenti le abilità e capacità del personaggio con uno switch case i bost sono uguali ma con frasi diverse 
void BostStats(int x) {
  switch (x) {
  case 1:

    cout << "Hai trovato una pezzo nella tasca di " << Ndrina_Grande_Aracri.nome
         << "\n decidi che un tiro non fa male a nessuno e guadagni un boost "
            "alle statistiche"
         << endl;

    system("pause");
    player.lifeMax += 20;
    player.life = player.lifeMax;
    player.lifeMax += player.aim += 0.33;
    player.forza += 0.33;
    player.dex += 0.33;
    player.armatura += 10;

    break;
  case 2:

    cout << "Hai trovato un crocifisso al collo di " << Antonio_Dragone.nome
         << "\n la tua fede in cristo nosto signiore e forte e lo e ancor di "
            "piu il tuo boost alle statistiche"
         << endl;
    system("pause");
    player.lifeMax += 20;
    player.life = player.lifeMax;
    player.lifeMax += player.aim += 0.33;
    player.forza += 0.33;
    player.dex += 0.33;
    player.armatura += 10;

    break;
  case 3:

    cout << "Hai trovato un cinquello nella tasca di " << Rocco_Morabito.nome
         << "\n non ha nulla di speciale ma sei cosi contento che guadagni un "
            "boost alle statistiche"
         << endl;
    system("pause");
    player.lifeMax += 20;
    player.life = player.lifeMax;
    player.lifeMax += player.aim += 0.33;
    player.forza += 0.33;
    player.dex += 0.33;
    player.armatura += 10;

    break;
  case 4:

    cout << "Rubi le scarpe di cemento a " << Rocco_Morabito.nome
         << "\n il loro potere si infonde in te e guadagni un boost alle "
            "statistiche"
         << endl;
    system("pause");
    player.lifeMax += 20;
    player.life = player.lifeMax;
    player.lifeMax += player.aim += 0.33;
    player.forza += 0.33;
    player.dex += 0.33;
    player.armatura += 10;

    break;
  }
}

// fillo
void gotoxy(short x, short h) {
  COORD pos = {x, h};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// stampa inventario a lato grazie all'utilizzo della funzione gotoxy 
void caratt_pg() {
  // inventario

  const int z = 15;

  gotoxy(90, z);
  printf("INVENTARIO");
  gotoxy(90, z + 1);
  printf("molotov : ");
  gotoxy(100, z + 1);
  cout << inventory.num_molotov;
  gotoxy(90, z + 2);
  printf("bende : ");
  gotoxy(98, z + 2);
  cout << inventory.num_benda;
  gotoxy(90, z + 3);
  printf("monete : ");
  gotoxy(99, z + 3);
  cout << inventory.money;

  for (int i = 78; i < 112; i++) {
    gotoxy(i, z - 2);
    printf("-");
  }
  for (int i = z - 2; i < 24; i++) {
    gotoxy(77, i);
    printf("-");
  }
  for (int i = z - 2; i < 14; i++) {
    gotoxy(112, i);
    printf("-");
  }
  //
  gotoxy(80, z + 7);
  printf("PERSONAGGIO");
  gotoxy(80, z + 6);
  gotoxy(80, z + 8);
  StampaVita();

  gotoxy(91, z + 8);
  printf(" ");

  gotoxy(93, z + 8);
  printf(" ");

  // armatura
  gotoxy(80, z + 9);
  printf("armatura : ");
  gotoxy(91, 18);
  cout << player.armatura;
  // aim
  gotoxy(80, z + 10);
  printf("aim : ");
  gotoxy(86, z + 10);
  cout << player.aim;
  // dex
  gotoxy(80, z + 11);
  printf("dex : ");
  gotoxy(86, z + 11);
  cout << player.dex;
  // forza
  gotoxy(80, z + 12);
  printf("forza : ");
  gotoxy(88, z + 12);
  cout << player.forza;
  for (int i = 78; i < 99; i++) {
    gotoxy(i, z + 5);
    printf("-"); // parte sinistra basso riga
  }
  for (int i = 77; i < 94; i++) {
    gotoxy(i, z + 14);
    printf("-");
  }
  for (int i = z + 5; i < 29; i++) {
    gotoxy(77, i);
    printf("-"); // parte sinistra colonna 1 parte bassa
  }
  for (int i = z + 5; i < 30; i++) {
    gotoxy(94, i);
    printf("-");
  }
  // faccio arma
  gotoxy(98, z + 7);
  printf("ARMA");
  //
  gotoxy(98, z + 8);
  printf("danno : ");
  gotoxy(106, z + 8);
  cout << arma_p.damage;
  //
  gotoxy(98, z + 9);
  printf("tipo : ");
  gotoxy(105, z + 9);
  cout << arma_p.tipo;
  //
  gotoxy(98, z + 10);
  printf("velocita : ");
  gotoxy(109, z + 10);
  cout << arma_p.vel;

  for (int i = 95; i < 112; i++) {
    gotoxy(i, z + 5);
    printf("-");
  }
  for (int i = 95; i < 112; i++) {
    gotoxy(i, z + 14);
    printf("-");
  }
  for (int i = z + 5; i < 30; i++) {
    gotoxy(95, i);
    printf("-");
  }
  for (int i = z + 5; i < 30; i++) {
    gotoxy(112, i);
    printf("-");
  }

  gotoxy(92, z - 7);
  printf("LEGENDA");
  gotoxy(80, z - 5);
  printf("! = nemico");
  gotoxy(80, z - 4);
  printf("<< = checkpoint");
  gotoxy(85, z - 3);
  printf("? = punto da scoprire");
  gotoxy(97, z - 5);
  cout << blocco;
  gotoxy(98, z - 5);
  printf(" = blocco");
  gotoxy(97, z - 4);
  cout << mercante;
  gotoxy(98, z - 4);
  printf(" = mercante");

  for (int i = 78; i < 112; i++) {
    gotoxy(i, z - 8);
    printf("-");
  }
  for (int i = z - 8; i < 13; i++) {
    gotoxy(77, i);
    printf("-");
  }
  for (int i = z - 8; i < 21; i++) {
    gotoxy(112, i);
    printf("-");
  }
}
void clean() {
  int n = 50;
  int n2 = 76;
  char matrice[27][76];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n2; j++) {
      gotoxy(j, i);
      cout << " ";
      // Sleep(10);
    }
    cout << endl;
  }
}

void caricamento() {
  int r = 30;
  int c = 10;

  for (int i = 0; i < 5; i++) {
    gotoxy(r, c);
    cout << " @ ";
    Sleep(500);
    r = r + 2;
  }
  system("cls");
}

//  fatto

int calabria() {
  int sto;
  gotoxy(1, 1);
  pp.symbol = '@';
  char map[H][W];

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      map[y][x] = ' ';
    }
  }

  // horizontal lines
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      map[7][8] = HORIZONTAL_LINE_BOTTOM;
      map[5][14] = HORIZONTAL_LINE_BOTTOM;
      map[5][15] = HORIZONTAL_LINE_BOTTOM;
      map[10][17] = HORIZONTAL_LINE_BOTTOM;
      map[19][19] = HORIZONTAL_LINE_BOTTOM;
      map[19][20] = HORIZONTAL_LINE_BOTTOM;
      map[19][21] = HORIZONTAL_LINE_BOTTOM;
      map[27][14] = HORIZONTAL_LINE_BOTTOM;
      map[27][15] = HORIZONTAL_LINE_BOTTOM;
      map[33][8] = HORIZONTAL_LINE_BOTTOM;
      map[33][9] = HORIZONTAL_LINE_BOTTOM;
      map[33][10] = HORIZONTAL_LINE_BOTTOM;
      map[33][11] = HORIZONTAL_LINE_BOTTOM;
      map[33][12] = HORIZONTAL_LINE_BOTTOM;
      map[8][10] = HORIZONTAL_LINE_BOTTOM;
      map[8][11] = HORIZONTAL_LINE_BOTTOM;
      map[22][10] = HORIZONTAL_LINE_BOTTOM;
    }
  }

  // vertical lines

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {

      map[20][11] = VERTICAL_LINE;
      map[21][11] = VERTICAL_LINE;
      map[7][12] = VERTICAL_LINE;
      map[11][18] = VERTICAL_LINE;

      if (x == 16) {
        if (y >= 6 && y <= 9)
          map[y][x] = VERTICAL_LINE;

        if (y >= 22 && y <= 26)
          map[y][x] = VERTICAL_LINE;
      }

      if (x == 21) {
        if (y >= 15 && y <= 17)
          map[y][x] = VERTICAL_LINE;
      }

      if (x == 13) {
        if (y >= 27 && y <= 32)
          map[y][x] = VERTICAL_LINE;
      }

      if (x == 7) {
        if (y >= 31 && y <= 32)
          map[y][x] = VERTICAL_LINE;

        if (y >= 8 && y <= 9)
          map[y][x] = VERTICAL_LINE;
      }

      if (x == 9) {
        if (y >= 26 && y <= 28)
          map[y][x] = VERTICAL_LINE;
      }

      if (x == 8) {
        if (y >= 23 && y <= 24)
          map[y][x] = VERTICAL_LINE;
      }
    }
  }

  // corner top left

  map[7][9] = CORNER_TOP_LEFT;
  map[5][16] = CORNER_TOP_LEFT;
  map[10][18] = CORNER_TOP_LEFT;
  map[14][21] = CORNER_TOP_LEFT;
  map[13][20] = CORNER_TOP_LEFT;
  map[18][22] = CORNER_TOP_LEFT;
  map[12][19] = CORNER_TOP_LEFT;
  map[25][9] = CORNER_TOP_LEFT;

  // corner +

  map[7][7] = CORNER;
  map[6][12] = CORNER;
  map[5][13] = CORNER;
  map[27][13] = CORNER;
  map[30][7] = CORNER;
  map[23][8] = CORNER;
  map[22][9] = CORNER;
  map[29][8] = CORNER;

  // corner bottom left +

  map[10][16] = CORNER_BOTTOM_LEFT;
  map[33][7] = CORNER_BOTTOM_LEFT;
  map[18][21] = CORNER_BOTTOM_LEFT;
  map[8][9] = CORNER_BOTTOM_LEFT;
  map[25][8] = CORNER_BOTTOM_LEFT;
  map[12][18] = CORNER_BOTTOM_LEFT;
  map[13][19] = CORNER_BOTTOM_LEFT;
  map[14][20] = CORNER_BOTTOM_LEFT;

  // BACKSLASH

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      map[7][8] = HORIZONTAL_LINE_BOTTOM;
      map[4][14] = HORIZONTAL_LINE_BOTTOM;
      map[10][17] = HORIZONTAL_LINE_BOTTOM;
      map[19][19] = HORIZONTAL_LINE_BOTTOM;
      map[19][20] = HORIZONTAL_LINE_BOTTOM;
      map[19][21] = HORIZONTAL_LINE_BOTTOM;
      map[27][14] = HORIZONTAL_LINE_BOTTOM;
      map[33][8] = HORIZONTAL_LINE_BOTTOM;
      map[33][9] = HORIZONTAL_LINE_BOTTOM;
      map[33][10] = HORIZONTAL_LINE_BOTTOM;
      map[33][11] = HORIZONTAL_LINE_BOTTOM;
    }
  }

  // vertical lines

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {

      if (x == 7) {
        if (y >= 10 && y <= 11)
          map[y][x] = BACKSLASH;
      }

      if (x == 8) {
        if (y >= 12 && y <= 13)
          map[y][x] = BACKSLASH;
      }

      if (x == 9) {
        if (y >= 14 && y <= 15)
          map[y][x] = BACKSLASH;
      }

      if (x == 10) {
        if (y >= 16 && y <= 17)
          map[y][x] = BACKSLASH;
      }

      if (x == 11) {
        if (y >= 18 && y <= 19)
          map[y][x] = BACKSLASH;
      }

      map[20][18] = '/';
      map[20][17] = '/';
      map[21][16] = '/';
    }
  }

  // corner bottom right +

  map[19][22] = CORNER_BOTTOM_RIGHT;
  map[27][16] = CORNER_BOTTOM_RIGHT;
  map[33][13] = CORNER_BOTTOM_RIGHT;
  map[29][9] = CORNER_BOTTOM_RIGHT;
  map[30][8] = CORNER_BOTTOM_RIGHT;
  map[22][11] = CORNER_BOTTOM_RIGHT;
  map[23][9] = CORNER_BOTTOM_RIGHT;
  map[6][13] = CORNER_BOTTOM_RIGHT;
  map[8][12] = CORNER_BOTTOM_RIGHT;

  // checkpoint

  map[32][9] = CHECKPOINT; // REGGIO CALABRIA
  map[32][10] = '1';

  map[19][16] = CHECKPOINT; // CATANZARO
  map[19][17] = '2';

  map[15][19] = CHECKPOINT; // CROTONE
  map[15][20] = '3';

  map[12][12] = CHECKPOINT; // COSENZA
  map[12][13] = '4';

  map[6][14] = '?';
  map[23][10] = '?';

  char originalMap[H][W];
  std::memcpy(originalMap, map, sizeof(map));

  int x = 9;
  int y = 31;

  bool isRunning = true;
  while (isRunning) {
    // Restore the original map
    std::memcpy(map, originalMap, sizeof(map));

    if (map[y][x] == CORNER_BOTTOM_LEFT ||
        map[y][x] == HORIZONTAL_LINE_BOTTOM || map[y][x] == VERTICAL_LINE ||
        map[y][x] == CORNER_TOP_LEFT || map[y][x] == CORNER ||
        map[y][x] == BACKSLASH || map[y][x] == '/') {
      y = 31;
      x = 9;

      map[y][x] = pp.symbol;
      std::cout << "Movimento Proibito!!!" << std::endl;
    }

    if (y == 32 && x == 9) {
      if (D1 == true) {
        D1 = false;
        system("cls");
        MegaCout(msg3, 232, 50);
        // acesso reggio calabria
        system("cls");
      }
      sto = reggio(1, Ndrina_Grande_Aracri, boss1);
      if (sto == 1) {
        system("cls");
        return 0;
      }
    }

    if (KEY1 == TRUE) {
      if (y == 19 && x == 16) {
        if (D2 == true) {
          D2 = false;
          system("cls");
          MegaCout(msg5, 305, 30);
          system("cls");
        }
        sto = reggio(2, Antonio_Dragone, boss2);
        if (sto == 1) {
          return 0;
        } // accesso catanzaro
      }
    }

    if (KEY2 == TRUE) {
      if (y == 15 && x == 19) {
        if (D3 == true) {
          D3 = false;
          system("cls");
          MegaCout(msg7, 420, 30);
          system("cls");
        } else if (D5 == true) {
          return 0;
        }
        sto = reggio(3, Rocco_Morabito, boss3);
        if (sto == 1) {
          return 0;
        } // accesso crotone
      }
    }

    if (KEY3 == TRUE) {
      if (y == 12 && x == 12) {
        if (D4 == true) {
          D4 = false;
          system("cls");
          MegaCout(msg9, 270, 30);
          system("cls");
        }
        sto = reggio(4, Luigi_Mancuso, boss4);
        if (sto == 1) {
          return 0;
        } // accesso cosenza
      }
    }

    map[y][x] = pp.symbol;

    caratt_pg();

    // Print the updated map
    for (int y = 0; y < H; y++) {
      for (int x = 0; x < W; x++) {
        std::cout << map[y][x];
      }
      std::cout << std::endl;
    }

    // Check for user input
    char userInput =
        _getch(); // Use _getch() on Windows, or alternative on other platforms

    system("cls");

    // Process user input
    switch (userInput) {
    case 'w':
      if (y > 0)
        y--;
      break;
    case 's':
      if (y < H - 1)
        y++;
      break;
    case 'a':
      if (x > 0)
        x--;
      break;
    case 'd':
      if (x < W - 1)
        x++;
      break;
    case 'q':
      isRunning = false;
      break;
    default:
      break;
    }
  }
}

char mapr[HEIGHT][WIDTH];

int reggio(int IDm, nemici boss, bool morte) {

  pp.symbol = '@';

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      mapr[y][x] = ' ';
    }
  }

  // horizontal lines
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (y == 12 || y == 14) {
        if (x >= 0 && x <= 10)
          mapr[y][x] = HORIZONTAL_LINE_BOTTOM;

        if (y == 12) {
          if (x >= 13 && x <= 21)
            mapr[y][x] = HORIZONTAL_LINE_BOTTOM;
        }

        if (y == 14) {
          if (x >= 13 && x <= 18)
            mapr[y][x] = HORIZONTAL_LINE_BOTTOM;
        }
      }

      if (y == 16) {
        if (x >= 23 && x <= 25)
          mapr[y][x] = HORIZONTAL_LINE_BOTTOM;
      }

      if (y == 18) {
        if (x >= 20 && x <= 25)
          mapr[y][x] = HORIZONTAL_LINE_BOTTOM;
      }
    }
  }

  // vertical lines

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {

      if (x == 10 || x == 13) {
        if (y >= 12 && y <= 15)
          mapr[y][x] = VERTICAL_LINE;
      }

      if (x == 19) {
        if (y >= 15 && y <= 17)
          mapr[y][x] = VERTICAL_LINE;
      }

      if (x == 22) {
        if (y >= 13 && y <= 15)
          mapr[y][x] = VERTICAL_LINE;
      }
    }
  }

  // corner bottom left
  mapr[18][19] = CORNER_BOTTOM_LEFT;
  mapr[16][22] = CORNER_BOTTOM_LEFT;

  // corner top left

  mapr[12][22] = CORNER_TOP_LEFT;
  mapr[14][19] = CORNER_TOP_LEFT;

  // boss

  int e = -1;
  while (e < 0) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;

    if (mapr[y][x] == ' ') {
      if ((y < 11 || y > 15) && (y < 16 || y > 18)) {
        if (x < 20 || y > 23) {
          mapr[y][x] = BOSS;
          e++;
        }
      }
    }
  }

  // nemici
  int c = 0;
  while (c <= 6) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;

    if (mapr[y][x] == ' ') {
      if ((y < 11 || y > 15) && (y < 16 || y > 18)) {
        if (x < 20 || y > 23) {
          mapr[y][x] = ENEMY;
          c++;
        }
      }
    }
  }

  // house

  int d = 0;
  while (d <= 20) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;

    if (mapr[y][x] == ' ') {
      if ((y < 11 || y > 15) && (y < 16 || y > 18)) {
        if (x < 20 || y > 23) {
          mapr[y][x] = HOUSE;
          d++;
        }
      }
    }
  }

  // mercanti
  int b = 0;
  while (b < 1) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;

    if (mapr[y][x] == ' ') {
      if ((y < 11 || y > 15) && (y < 16 || y > 18)) {
        if (x < 20 || y > 23) {
          mapr[y][x] = MERCANTI;
          b++;
        }
      }
    }
  }

  // check point
  int a = -1;
  while (a < 0) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;

    if (mapr[y][x] == ' ') {
      if ((y < 11 || y > 15) && (y < 16 || y > 18)) {
        if (x < 20 || y > 23) {
          mapr[y][x] = CHECKPOINT;
          a++;
        }
      }
    }
  }

  char originalMapr[HEIGHT][WIDTH];
  std::memcpy(originalMapr, mapr, sizeof(mapr));

  int x = 11;
  int y = 17;

  bool isRunning = true;
  while (isRunning) {
    // Restore the original map
    std::memcpy(mapr, originalMapr, sizeof(mapr));

    // Update the map with the character's position
    if (mapr[y][x] == HOUSE || mapr[y][x] == CORNER_BOTTOM_LEFT ||
        mapr[y][x] == HORIZONTAL_LINE_BOTTOM || mapr[y][x] == VERTICAL_LINE ||
        mapr[y][x] == CORNER_TOP_LEFT) {
      y = 17;
      x = 11;

      mapr[y][x] = pp.symbol;
      std::cout << "Movimento Proibito!!!" << std::endl;
    }

    if (mapr[y][x] == CHECKPOINT) {
      clean();
      calabria();
    }



    if(y == 6 && x == 14){
        if(Ester1 == true){
          Ester1 = false;
          cout<<"Vedi quello che sembra uno spaciatore \ndecidi di derubarlo guadagnado 25 monete"<<endl;
          inventory.money += 25;
        }
        else{
          cout<<"Che altro vuoi? mi hai gia derubato"<<endl;
        }
    }
    if(y == 23 && x == 10){
        if(Ester2 == true){
          Ester2 = false;
          cout<<"ce un bidone della spazatura in fiamme \nnon ci fai molto caso, non e il primo che vedi in calabria\n pero hai trovato una benda"<<endl;
          inventory.num_benda++;
        }
        else{
          cout<<"adoro lodore di spazatura bruciata la mattino"<<endl;
        }


    }




    if (mapr[y][x] == MERCANTI) {
      clean();
      cout << " sei arrrivato dal mercante  " << endl;
      comercio(IDm);
    }

    if (morte == true) {
      if (mapr[y][x] == BOSS) {
        bool sucesso;
        int m = inventory.num_molotov;
        int b = inventory.num_benda;
        clean();
        cout << " combatti  " << endl;
        sucesso = lotta(boss);

        if (sucesso == true) {
          switch (IDm) {
          case 1:
            boss1 = false;
            KEY1 = true;
            BostStats(IDm);
            return 1;

            break;
          case 2:
            boss2 = false;
            KEY2 = true;
            BostStats(IDm);
            return 1;

            break;
          case 3:
            boss3 = false;
            KEY3 = true;
            BostStats(IDm);
            return 1;

            break;
          }
        } else {
          inventory.num_molotov = m;
          inventory.num_benda = b;
          cout << "sei morto verai riportato allo spawn" << endl;
          Sleep(1500);
          system("cls");
          inventory.money = inventory.money / 2;
          caratt_pg();
          caricamento();
          int y = 17;
          int x = 11;
          mapr[y][x] = pp.symbol;
        }
      }
    }

    if (mapr[y][x] == ENEMY) {
      int nem = rand() % 5;
      int m = inventory.num_molotov;
      int b = inventory.num_benda;
      bool v;
      switch (nem) {
      case 1:
        v = lotta(mastro);
        break;
      case 2:
        v = lotta(puntaiolo);
        break;
      case 3:
        v = lotta(piccioto);
        break;
      case 4:
        v = lotta(Mammasantissima);
        break;
      case 5:
        v = lotta(Bartolo);
        break;
      default:
        cout << "al tuo nemico e venuto un infarto" << endl;
        break;
      }
      if (v == true) {
        cout << "scontro terminato, Requiescat in Pace's" << endl;
      } else {
        inventory.num_molotov = m;
        inventory.num_benda = b;
        cout << "sei morto verai riportato allo spawn" << endl;
        Sleep(1500);
        system("cls");
        inventory.money = inventory.money / 2;
        caratt_pg();
        caricamento();
        int y = 17;
        int x = 11;
        mapr[y][x] = pp.symbol;
      }
    } // nemici randomici  pre fatti

    caratt_pg();

    mapr[y][x] = pp.symbol;

    // Print the updated map
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        std::cout << mapr[y][x];
      }
      std::cout << std::endl;
    }

    // Check for user input
    char userInput =
        _getch(); // Use _getch() on Windows, or alternative on other platforms

    system("cls");

    // Process user input
    switch (userInput) {
    case 'w':
      if (y > 0)
        y--;
      break;
    case 's':
      if (y < HEIGHT - 1)
        y++;
      break;
    case 'a':
      if (x > 0)
        x--;
      break;
    case 'd':
      if (x < WIDTH - 1)
        x++;
      break;
    case 'q':
      isRunning = false;
      break;
    default:
      break;
    }
  }
}
