
#define WIDTH 5
#define HEIGHT 5

// The pin matrix, a negative index corresponds to a slave arduino pin
const int motorPin[WIDTH][HEIGHT] = {{2, 3, 4, 5, 6},{7, 8, 9, 10, 11},{12,-44,44,45,46},{-2,-3,-4,-5,-6},{-7,-8,-9,-10,-11}};

// The draw matrix, intensity is between 0 and 4
const unsigned char templatetest[WIDTH][HEIGHT] = {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}};
const unsigned char modelA[WIDTH][HEIGHT] = {{0, 0, 4, 0, 0},{0, 4, 4, 4, 0},{4, 4, 4, 4, 4},{4, 4, 4, 4, 4},{0, 4, 0, 4, 0}};


void setup() {
  Serial.begin(9600);
  // set all the pins in the pin matrix as output
  for (int i = 0 ; i < WIDTH ; i++) {
    for (int j = 0 ; j < HEIGHT ; j++) {
	  // Check if the pin is local, or on the slave android
      if (motorPin[i][j] > 0) {
		pinMode(motorPin[i][j], OUTPUT); 
      }
    }
  }
}

// Set the intensity of a motor (intensity 0-4)
void setMotor(int i, int j, int intensity) { 
  if ( motorPin[i][j] > 0) {
    analogWrite( motorPin[i][j], intensity); 
  }
  else { 
    Serial.write(1); //fanion
    Serial.write(- motorPin[i][j]);
    Serial.write(intensity);
  }
  
}

void loop() {
  //Resend periodically the data, we can imagine to change the intensity through the time
  for (int i = 0 ; i < WIDTH ; i++) {
    for (int j = 0 ; j < HEIGHT ; j++) {
      setMotor(i, j, modelA[i][j]*63 );
    }
  }
  delay(20);

}
