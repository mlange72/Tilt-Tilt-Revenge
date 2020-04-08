#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>           //  also need to include this library...
TMRpcm track;
int numOfSongs = 2; //modify this when adding more tracks
int timing = 0; //to fill timing array
char song[15]; //holds song selection for menu
char buf; //a character buffer slot
char target[15]; //for using files
char test[14]; //for data file
File file; //to open files
int CODE = 0; //SERIAL codes to/from MEGA
int select = 0; //song number


void setup() {
Serial.begin(9600); //open Serial 
SD.begin(4); //enable SD card
track.setVolume(2); //set volume of the in game audio [VOLUME CONTROL]
track.loop(1); //track can loop for menu preview
track.speakerPin = 9; //audio  PCM pin
}


//Get song for playing //
void getSong(int num) {
  track.disable(); //stop prev track
  delay(10);
  file.seek(0); //start at begninning of file

  for (int i = 0; i < 15; i++) //refresh song name
              song[i] = '\0';           
  while (file.available() && (file.parseInt() != num)) { //skip to song line
  }
  file.read();
      int i = 0;
      buf = file.read();
      while (buf != '|') { //get file name
      song[i] = buf;
        i++;
        buf = file.read();
      }
      song[i] = '\0';
      i=0;
      buf = file.read();
    //Serial.print(song);
    delay(10);
}


//Load the song data for the game //
void loadSong() {
   track.disable(); //song must be disabled to properly fill arrays
   char data[9];
   sprintf(data,"%dD.txt", select); //load tracker file
   delay(200);
   Serial.print(20); // CODE 20 - Fill Note Array
   file = SD.open(data, FILE_READ);
   file.seek(0);
   delay(20);
   file.read();
   while (buf != 'N') { //Fill Note Array 
        buf = file.read();
        delay(10);
        Serial.print(buf);
   }
   Serial.println(22); // CODE 22 - Fill Timing Array
   delay(50);
   file.read(); //skip to numbers
   file.read();
    
   while (timing != -99) { //Fill Timing Array 
        delay(20);     
        timing = file.parseInt();    
        Serial.println((short)timing);
   }
  //Serial.println("done");
}


// Main Menu Controls //
int MainMenu() {
  select = 0; //song number
  getSong(select);
  snprintf( target, sizeof( target ), "%dP.wav", select);
      track.play(target); //play the song preview
      //loadSong();
      delay(10);
      
   while (true) { 
     if (Serial.available() > 0) {
        delay(10);
     CODE = Serial.parseInt();
      delay(10);
          if (CODE == 2) {    //next song
            track.play("down.wav");
            delay(200);
            track.disable();
             select++;
            if (select >= numOfSongs) //reset at end
                select = 0;
          }
         else if (CODE == 3) { //previous song
          track.play("up.wav");
          delay(200);
          track.disable();
           select--;
           if (select < 0) //reset at end
             select = numOfSongs-1;
         }
          else if (CODE == 4) { //load song
            track.play("select.wav");
            delay(500);
            file.close();
            loadSong();
            CODE = 0;
          }

          else if (CODE == 0) { //for testing
            track.disable();
          }
      delay(10);
      getSong(select);
      buf = 'P';
      snprintf( target, sizeof( target ), "%dP.wav", select);
      delay(10);
      track.play(target);
      delay(10);
    }
  }
}


void loop() {
  sprintf(test, "%s.txt", "songid");
  file = SD.open(test, FILE_READ); //check if we can find the songid file
  if (!file) {
    Serial.print("Missing SongID file. Fix this and then reset.\n");
    delay(50);
    exit(0);
  }
  MainMenu();
  delay(10);
  exit(0);

}
