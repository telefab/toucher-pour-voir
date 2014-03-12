#define HEIGHT 5
#define WIDTH 5

int currentMessage = -1 ;
int currentPort = 0;

// The serial message format is:
// 1 byte : always 1 (fanion)
// 1 byte : the pin number
// 1 byte : the intensity 0-255 excluding 1

void setup () {
  Serial.begin (9600);
  // Set the pin as output
  for (int i =2 ; i <= 13; i++) {
    pinMode ( i ,OUTPUT );
  }
  for (int i = 44 ; i <= 46; i++) {
    pinMode ( i ,OUTPUT );
  }
}

void loop () {
  if (Serial.available() > 0 ) {
    byte entry = Serial.read();
	// Fanion detected
    if ( entry == 1) {
      currentMessage = 0;
    }
    else {
	  // Waiting for pin number byte
      if (currentMessage == 0) {
        if ( (entry >=2 && entry <=13) || (entry >=44 && entry <=46) ){
         currentPort = entry;
         currentMessage++;
         }
        else {
          currentPort=-1;
        }
         
      }
	  // Waiting for intensity byte
      else 
        if (currentMessage == 1) {
         analogWrite (currentPort, entry);
         currentMessage=-1;
        } 
      }
  }
} 
     
          
        
        
      
    
      
   
         
  

