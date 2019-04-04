#include "simpletools.h"                      
#include "servo.h"

#define C3 130.81
#define Db3 138.59
#define Eb3 155.56
#define F3  174.61
#define Gb3 185.00

#define Ab3 207.65
#define Bb3 233.08
#define C4 261.63
#define Db4 277.18
#define Eb4 311.13
#define F4 349.23
#define Gb4 369.99

#define Ab4 415.30
#define Bb4 466.16
#define C5 523.25
#define Db5 554.37
#define Eb5 622.26
#define F5 698.46
#define Gb5 739.99

#define Bb5 933.33



enum SadState{START, TURN, MOVE};

enum SadState sadState = START;

int irSense;
int soundSense; 
int leftServo = 12;
int rightServo = 13;
int irPin = 11;
void* song;
int buzzerPin = 6;
int delay = 10;
int whole = 750;

void sadSong(void);
void playL(double note, double length);
void play(double note);

int sad(void){
  freqout(10, 1, 38000);
  freqout(14, 1, 38000);
  irSense = input(irPin);

  switch(sadState){
    case START:
      if(irSense)
        sadState = TURN;
      break;
      
    case TURN:
        song = cog_run(sadSong, 128);
        servo_speed(leftServo, 50);
        servo_speed(rightServo, 50);
        pause(3000);
        sadState = MOVE;
      break;
      
    case MOVE:          
        servo_speed(leftServo, 50);
        servo_speed(rightServo, -50);
        pause(5000);
        cog_end(song);
        sadState = START;
      break;
        
    default:
      sadState = START;
      break;
  }    
  return 0;
}

void sadSong(void){

    play(Bb4);
    play(Db3);
    play(Bb3);
    play(Db3);
    play(Bb3);
    play(Db3);
    play(F4);
    play(Db3);
    play(Bb3);
    play(Db3);
    play(Bb3);
    play(Db3);

    play(Eb4);
    play(Eb3);
    play(C4);
    play(Eb3);
    play(C4);
    play(Eb3);
    play(Ab3);
    play(Eb3);
    play(C4);
    play(Eb3);
    playL(F4, whole/8);
    playL(Eb4, whole/8);
    playL(F4, whole/8);
    playL(Eb4, whole/8);

    play(Ab3);
    play(C3);
    play(Ab3);
    play(C3);
    play(Ab3);
    play(C3);
    play(Eb4);
    play(C3);
    play(Ab3);
    play(C3);
    play(Ab3);
    play(C3);

    play(Db4);
    play(F3);
    play(Bb3);
    play(C4);
    play(Db4);
    playL(Bb3, whole*2);
    play(Eb4);
    play(F4);

    play(Gb4);
    play(F4);
    play(Db4);
    play(Gb4);
    play(F4);
    play(Db4);
    play(Gb4);
    play(F4);
    play(Db4);
    play(Gb4);
    play(F4);
    play(Db4);

    play(Gb4);
    play(F4);
    play(Db4);
    play(Gb4);
    play(F4);
    play(Db4);
    playL(C4, whole);
    playL(Db4, whole);
    playL(Eb4, whole);

}

void playL(double note, double length){
    freqout(buzzerPin, note, length);
    pause(delay);
}

void play(double note){
    freqout(buzzerPin, note, whole/2);
    pause(delay);
}