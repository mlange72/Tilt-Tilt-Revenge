#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>           //  also need to include this library...
TMRpcm track;
char trkFile[13];
char wavFormat[6] = ".wav\0";
char dataFormat[4] = {'.', 't', 'x', 't'};
int numOfSongs = 2; //modify this when adding more tracks
int timing = 0;
char song[15]; //holds song selection for menu
char songCall[6];
char buf;
char loadData[500];
char target[15];
char test[14];

File file;
int CODE = 0;
int select = 0;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
SD.begin(4);
track.setVolume(1);
track.loop(1);
track.speakerPin = 9;
}


void getSong(int num) {
  track.disable();
  //Serial.print(num);
  delay(10);
  file.seek(0);

  for (int i = 0; i < 15; i++)
              song[i] = '\0';
   for (int i = 0; i < 6; i++)
              songCall[i] = '\0';            

  while (file.available() && (file.parseInt() != num)) {
  }
  file.read();
      int i = 0;
      buf = file.read();
      while (buf != '|') {
      song[i] = buf;
        i++;
        buf = file.read();
      }
      song[i] = '\0';
      i=0;


      buf = file.read();
      
    //Serial.print(song);
    delay(10);
    
    //Serial.print(songCall);
    delay(10);
}








void loadSong() {
   track.disable();
    char data[9];
     //if (CODE == 4) {
      sprintf(data,"%dD.txt", select);
      delay(200);
      Serial.print(20);
      
      file = SD.open(data, FILE_READ);
       file.seek(0);
      delay(20);
      file.read();
      while (buf != 'N') { 
        buf = file.read();
        delay(10);
        Serial.print(buf);
      }
      Serial.println(22);
      delay(50);
      file.read();
      file.read();
    
      while (timing != -99) { 
        delay(20);     
        timing = file.parseInt();    
        Serial.println((short)timing);
      }
  Serial.println("done");
}









int MainMenu() {
  select = 0;
  getSong(select);
  snprintf( target, sizeof( target ), "%dP.wav", select);
      track.play(target);
      //loadSong();
      delay(10);
      
   while (CODE != 4) {
    if (Serial.available() > 0) {
        delay(10);
     CODE = Serial.parseInt();
      //Serial.println(CODE);
      delay(10);
          if (CODE == 2) {    //next song
             select++;
            if (select >= numOfSongs)
                select = 0;
          }
         else if (CODE == 3) { //previous song
           select--;
           if (select < 0)
             select = numOfSongs-1;
         }
          else if (CODE == 4) { //load song
            file.close();
            loadSong();
            CODE = 0;
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
