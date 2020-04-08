
short timing[502]; //timing array
char note[502]; //note array
char aNote; //single note
short aTiming; //single timing
int CODE = 0; // SEERIAL CODE From both modules
int i = 0; //array size


void setup() {
 Serial.begin(9600); //MAIN
 Serial1.begin(9600); //AUDIO
}


// Setup the song before playing //
void setupSong() {
  Serial.print("Setting up song");
  Serial1.print(4);
  while(true) {
    if (Serial1.available() > 0) {
    //(10);
    CODE = Serial1.parseInt(); //sent from AUDIO
      
      if (CODE == 20) { // CODE 20 - Fill Note Array
        Serial.print("\nLoading Notes...");
            i=0;
            while (aNote != 'N') { //Fill Note Array

              if (Serial1.available() > 0) {
              delay(5);
              aNote = Serial1.read();
              note[i] = aNote;
              //Serial.print(note[i]);
              i++; 
              }
            }
          //Serial.println((int)i);
       } 

       if (CODE == 22) { // CODE 22 - Fill Timing Array
        Serial.print("\nLoading Timings...");
            i=0;
            while (aTiming != -99) { //Fill Timing Array
              if (Serial1.available() > 0) {
              delay(10);
              aTiming = Serial1.parseInt();
              timing[i] = aTiming;
              //Serial.println(timing[i]);
              i++; 
              }
            }
         return;   
       }
    }
  }
}


//Main Menu Joystick Control
void MainMenu() {
  while(true) {   
    if (Serial.available() > 0) { //Change this to a joystick input
    delay(10);
    CODE = Serial.parseInt();
      if (CODE == 25) { //this as well
        setupSong();
        Serial.print("\nTrack has ");
        Serial.print(i-1);
        Serial.print(" notes.\n\nReady to Rock!");     
        //playSong();
      }
    }
  } 
}


void loop() {
  MainMenu();
}
