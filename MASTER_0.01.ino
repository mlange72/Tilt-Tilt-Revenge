
short timing[502];
char note[502];
char aNote;
short aTiming;
int CODE = 0;
int i = 0;
void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);

}

void setupSong() {
  Serial.print("Setting up song");
  Serial1.print(4);
  while(true) {
    if (Serial1.available() > 0) {
    //(10);
    CODE = Serial1.parseInt();
      
      if (CODE == 20) {
        Serial.print("\nLoading Notes...");
            i=0;
            while (aNote != 'N') {

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

       if (CODE == 22) {
        Serial.print("\nLoading Timings...");
            i=0;
            while (aTiming != -99) {

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








void MainMenu() {
  while(true) {
    
    if (Serial.available() > 0) {
    delay(10);
    CODE = Serial.parseInt();
      if (CODE == 25) {
        setupSong();
        Serial.print("\nTrack has ");
        Serial.print(i);
        Serial.print(" notes.\n\nReady to Rock!");     
      }
  }



    
  } 
}









void loop() {
  MainMenu();
}
