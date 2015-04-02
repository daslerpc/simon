const int TRIANGLE_SWITCH = 2;
const int TRIANGLE_OUT = 3;

const int SQUARE_SWITCH = 4;
const int SQUARE_OUT = 5;

const int HEXAGON_SWITCH = 6;
const int HEXAGON_OUT = 7;

const int CIRCLE_SWITCH = 8;
const int CIRCLE_OUT = 9;

const int REED_OUT = 10;

int simon_level = 3;
int entered_buttons = 0;
int target_sequence[15];

void setup() {
  pinMode( CIRCLE_SWITCH, INPUT );
  pinMode( CIRCLE_OUT, OUTPUT );

  pinMode( TRIANGLE_SWITCH, INPUT );
  pinMode( TRIANGLE_OUT, OUTPUT );

  pinMode( HEXAGON_SWITCH, INPUT );
  pinMode( HEXAGON_OUT, OUTPUT );

  pinMode( SQUARE_SWITCH, INPUT );
  pinMode( SQUARE_OUT, OUTPUT );

  pinMode( REED_OUT, OUTPUT );

  Serial.begin(9600);
  delay(3000);

  restartGame();
}


void loop() {
  digitalWrite( CIRCLE_OUT, LOW );
  digitalWrite( TRIANGLE_OUT, LOW );
  digitalWrite( HEXAGON_OUT, LOW );
  digitalWrite( SQUARE_OUT, LOW );  

  for( int x=2; x <=8; x+=2) {

    if( digitalRead( x ) == HIGH) {
      if( target_sequence[entered_buttons] == x) {
        entered_buttons++;
        delay(200);
      }
      else {
        Serial.println("Button Mismatch: " + String(x));
        delay(200);
        lose();
      }
    }
  }

  if( entered_buttons == 15 )
    win();

  if( entered_buttons == simon_level )
    levelUp();
}

void playSequence() {

  Serial.println("Play Sequence");

  int pin = 0;
  for (int x=0; x< simon_level; x++) {
    pin = target_sequence[x] + 1;
    Serial.println("Pin " + String(pin));
    digitalWrite( pin, HIGH );
    delay( 250 );
    digitalWrite( pin, LOW );
    delay( 500 );
  }
}


void lose() {

  Serial.println("Lose");
  playLossSong();
  restartGame();
}

void win() {

  Serial.println("Win");
  playWinSong();
  restartGame();
}

void playWinSong() {
  for(int y=0; y<4; y++)
    for( int x=3; x<=9; x+=2) {
      digitalWrite( x, HIGH );
      delay(100);
      digitalWrite( x, LOW );
      delay(400);
    }
}

void playLossSong() {
  digitalWrite( REED_OUT, HIGH );
  delay(100);
  digitalWrite( REED_OUT, LOW );
  delay(900);
}

void levelUp() {
  Serial.println("Level up");
  delay(1000);
  simon_level++;
  setSequence();
}

void restartGame() {

  Serial.println("Restart Game");

  delay(1500);
  entered_buttons = 0;
  simon_level = 3;
  setSequence();
}

void setSequence() {

  Serial.println("Set Sequence");

  entered_buttons = 0;
  for( int x=0; x<simon_level; x++) {
    target_sequence[x] = (random(4) + 1)*2;
    Serial.print(String(target_sequence[x]) + " ");
  }
  playSequence();
}








