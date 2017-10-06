#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyTones.h>
Arduboy2 arduboy;
Sprites sprites;
byte enemyWalkingFrame;
int xSpeed = 1;
int enemyX = 0;
int enemyY = 10;
int bulletY = 1;
int bulletX = 58;
byte ySpeed = 1;
float score = 0;
int randomSpeed = 0;
int bulletSpeed = 3;
int framesLeft = 0;
int fps = 60;
int playTime =  60;
int buletWaitFrames = 120;
int framesPlayed = 0;
int timePlayed = 0;
int timeLeft = playTime;
bool showPoints = false;
bool gameStarted = false;
bool fromPause = false;
int lastHit = 0;
bool collidet = false;
int highscore = 0;
int scoreMultiplyer = 16.29;
int frames = 0;
int combo = 0;
int comboScore = 0;
bool inCombo = false;
int showTutorial = 1;
bool tutorialButtonReleased = false;
Point bullet;
Rect enemy;
PROGMEM const unsigned char bullets_is_mask[] = {
  // width, height
  16, 8,
  // frame 0
  0x04, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 1
  0x08, 0x00, 0x08, 0x14, 0x00, 0x00, 0x08, 0x00, 0x22, 0x00,
  0x08, 0x00, 0x00, 0x14, 0x00, 0x41,
  // frame 2
  0x04, 0x02, 0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 3
  0x06, 0x06, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 4
  0x08, 0x16, 0x11, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 5
  0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 6
  0x04, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 7
  0x41, 0x00, 0x14, 0x00, 0x00, 0x08, 0x00, 0x22, 0x00, 0x08,
  0x00, 0x00, 0x14, 0x08, 0x00, 0x08,
  // frame 8
  0x06, 0x04, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 9
  0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 10
  0x0C, 0x12, 0x11, 0x16, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // frame 11
  0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

PROGMEM const unsigned char enemyBig_plus_mask[] = {
  // width, height
  12, 16,
  // frame 0
  0xC0, 0xC0, 0xA0, 0xE0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0,
  0x90, 0xF0, 0x50, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x20, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0xEA, 0xFF, 0xD5, 0xFF,
  0xAA, 0xFF, 0xD5, 0xFF, 0x82, 0xFF, 0x41, 0x7F, 0x33, 0x3F,
  0x61, 0x7F, 0xB4, 0xFF, 0xA4, 0xFF, 0x7F, 0x7F,
  // frame 1
  0xC0, 0xC0, 0x60, 0xE0, 0x90, 0xF0, 0x50, 0xF0, 0x90, 0xF0,
  0x50, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x20, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0xD5, 0xFF, 0xAA, 0xFF,
  0xD5, 0xFF, 0x82, 0xFF, 0x41, 0x7F, 0x33, 0x3F, 0x21, 0x3F,
  0x34, 0x3F, 0x64, 0x7F, 0xB1, 0xFF, 0xFF, 0xFF,
  // frame 2
  0xC0, 0xC0, 0xA0, 0xE0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0,
  0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x20, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0xEA, 0xFF, 0xD5, 0xFF,
  0x82, 0xFF, 0x41, 0x7F, 0x33, 0x3F, 0x21, 0x3F, 0x34, 0x3F,
  0x24, 0x3F, 0x71, 0x7F, 0x83, 0xFF, 0x7F, 0x7F,
  // frame 3
  0xC0, 0xC0, 0x60, 0xE0, 0x90, 0xF0, 0x50, 0xF0, 0x90, 0xF0,
  0x50, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x20, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0xD5, 0xFF, 0xAA, 0xFF,
  0xD5, 0xFF, 0x82, 0xFF, 0x41, 0x7F, 0x33, 0x3F, 0x21, 0x3F,
  0x34, 0x3F, 0x64, 0x7F, 0xB1, 0xFF, 0xFF, 0xFF,
  // frame 4
  0xC0, 0xC0, 0x20, 0xE0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0,
  0xA0, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0xA4, 0xFF, 0xB4, 0xFF,
  0x61, 0x7F, 0x33, 0x3F, 0x41, 0x7F, 0x82, 0xFF, 0xD5, 0xFF,
  0xAA, 0xFF, 0xD5, 0xFF, 0xEA, 0xFF, 0x7F, 0x7F,
  // frame 5
  0xC0, 0xC0, 0x20, 0xE0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x10, 0xF0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0, 0x90, 0xF0,
  0x60, 0xE0, 0xC0, 0xC0, 0xFF, 0xFF, 0xB1, 0xFF, 0x64, 0x7F,
  0x34, 0x3F, 0x21, 0x3F, 0x33, 0x3F, 0x41, 0x7F, 0x82, 0xFF,
  0xD5, 0xFF, 0xAA, 0xFF, 0xD5, 0xFF, 0x7F, 0x7F,
  // frame 6
  0xC0, 0xC0, 0x20, 0xE0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x10, 0xF0, 0x10, 0xF0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0,
  0xA0, 0xE0, 0xC0, 0xC0, 0x7F, 0x7F, 0x83, 0xFF, 0x71, 0x7F,
  0x24, 0x3F, 0x34, 0x3F, 0x21, 0x3F, 0x33, 0x3F, 0x41, 0x7F,
  0x82, 0xFF, 0xD5, 0xFF, 0xEA, 0xFF, 0x7F, 0x7F,
  // frame 7
  0xC0, 0xC0, 0x20, 0xE0, 0x10, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x10, 0xF0, 0x50, 0xF0, 0x90, 0xF0, 0x50, 0xF0, 0x90, 0xF0,
  0x60, 0xE0, 0xC0, 0xC0, 0xFF, 0xFF, 0xB1, 0xFF, 0x64, 0x7F,
  0x34, 0x3F, 0x21, 0x3F, 0x33, 0x3F, 0x41, 0x7F, 0x82, 0xFF,
  0xD5, 0xFF, 0xAA, 0xFF, 0xD5, 0xFF, 0x7F, 0x7F,
};

void drawEnemy() {
  for (byte i = 0; i < 1; i++) {
    sprites.drawPlusMask(enemyX, enemyY - 4, enemyBig_plus_mask, enemyWalkingFrame + (xSpeed));
    sprites.drawSelfMasked(bulletX, bulletY, bullets_is_mask, 10);
  }
}

void listPoints() {
  if (arduboy.pressed(UP_BUTTON) && !(arduboy.pressed(UP_BUTTON) && arduboy.pressed(RIGHT_BUTTON) && arduboy.pressed(DOWN_BUTTON))) {
    showPoints = false;
    score = 0;
    timePlayed = 0;
    fromPause = true;
  } else {
    if (inCombo && combo > 1) {
      score = score + combo * .3;
      combo = 0;
    }
    arduboy.setCursor(15, 5);
    arduboy.print("You  hav reached");
    arduboy.setCursor(15, 15);
    arduboy.print(String(score) + " Points");
    arduboy.setCursor(15, 25);
    if (score >= highscore) {
      highscore = score;
      arduboy.print("NEW HIGH: " + String(score));
      if (frames % fps == 0) {
        arduboy.setRGBled(0, 255, 0);
      } else if (frames % fps == fps / 2) {
        arduboy.setRGBled(0, 255, 0);
      }
      arduboy.setRGBled(0, 0, 0);
    } else {
      arduboy.print("High: " + String(highscore));
    }
    arduboy.setCursor(15, 45);
    arduboy.print("Press UP to play");
    arduboy.setCursor(15, 55);
    arduboy.print("again!");
  }
}

void startScreen() {
  if (arduboy.pressed(A_BUTTON)) {
    gameStarted = true;
    fromPause = true;
  } else {
    arduboy.setCursor(15, 5);
    arduboy.print("Just a Game");
    arduboy.setCursor(15, 25);
    arduboy.print("Made by");
    arduboy.setCursor(15, 35);
    arduboy.print("Moritz Fromm");
    arduboy.setCursor(15, 45);
    arduboy.print("bit.ly/mfGame");
    arduboy.setCursor(15, 55);
    arduboy.print("A to play");
  }
}

void update() {
  if (arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(UP_BUTTON)) {
    gameStarted = false;
    showTutorial = 1;
    showPoints = false;
    score = 0;
    timePlayed = 0;
    fromPause = true;
  } else if (arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.pressed(LEFT_BUTTON)) {
    xSpeed = 1;
    enemyX = 35;
    enemyY = 10;
    bulletY = 1;
    bulletX = 58;
    ySpeed = 1;
    framesLeft = 0;
    framesPlayed = 0;
    timePlayed = 0;
    timeLeft = playTime;
    if (inCombo && combo > 1) {
      score = score + combo * .3;
      combo = 0;
    }
    score = score * scoreMultiplyer;
    showPoints = true;
  } else {
    if (arduboy.everyXFrames(fps))timePlayed++;
    framesPlayed++;
    if (framesLeft > 0) framesLeft--;
    if (arduboy.pressed(A_BUTTON) and not (bulletY < 64) and (framesLeft <= 0)) {
      bulletY = 63;
      framesLeft = buletWaitFrames;
    }
    randomSpeed = random(0, 3);
    if (enemyX >= 115) xSpeed = randomSpeed;
    if (enemyX <= 1) xSpeed = -randomSpeed;
    if (bulletY < -3) {
      bulletY = 64;
      arduboy.setRGBled(255, 0, 0);
      lastHit = framesPlayed;
      inCombo = false;
    }
    if (bulletY < 64) bulletY = bulletY - bulletSpeed;
    //bulletY = bulletY * 0.9;
    enemyX = enemyX - (xSpeed);
    timeLeft = playTime - timePlayed;
    if (timeLeft <= 0) {
      if (combo > 1) {
        score = score + combo * .3;
        combo = 0;
      }
      score = score * scoreMultiplyer;
      showPoints = true;
    }
    enemy.x = enemyX;
    enemy.y = enemyY;
    enemy.width = 15;
    enemy.height = 15;
    bullet.x = bulletX;
    bullet.y = bulletY;
    if (arduboy.collide(bullet, enemy)) {
      combo++;
      inCombo = true;
      arduboy.setRGBled(0, 255, 0);
      score++;
      lastHit = framesPlayed;
      bulletY = 64;
      framesLeft = buletWaitFrames / 4;
      collidet = true;
    } else if ((framesPlayed - lastHit) > 60) {
      arduboy.setRGBled(0, 0, 0);
      lastHit = 0;
    }
    drawEnemy();
    if (!inCombo && combo > 1) {
      score = score + combo * .3;
      combo = 0;
    }
    if (inCombo) {
      Serial.print(combo);
      Serial.write(",");
    } else  {
      Serial.print(0);
      Serial.write(",");
    }
    Serial.print(combo);
    Serial.write(",");
    Serial.print(combo * .3);
    Serial.write(",");
    Serial.print(0);
    Serial.write(",");
    Serial.write("\n");
  }
  arduboy.setCursor(115, 55);
  arduboy.print(framesLeft);
  arduboy.setCursor(75, 0);
  arduboy.print("High: " + String(highscore));
  arduboy.setCursor(0, 0);
  arduboy.print(String(round(score * scoreMultiplyer)));
  arduboy.setCursor(0, 50);
  arduboy.print(String(timeLeft) + " Sec. left");
}

void tutorial1() {
  if (arduboy.pressed(UP_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 2;
    }
    tutorialButtonReleased = false;
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 1;
      gameStarted = false;
    }
    tutorialButtonReleased = false;
  } else {
    tutorialButtonReleased = true;
    arduboy.setCursor(20, 0);
    arduboy.print("TUTORIAL (1/2):");
    arduboy.setCursor(5, 10);
    arduboy.print("You have to hit");
    arduboy.setCursor(5, 20);
    arduboy.print("the enemy. When");
    arduboy.setCursor(5, 30);
    arduboy.print("you hit, you can");
    arduboy.setCursor(5, 40);
    arduboy.print("shot after a half Second...");
    arduboy.setCursor(5, 50);
    arduboy.print("UP to continue");
  }
}

void tutorial2() {
  if (arduboy.pressed(UP_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 3;
    }
    tutorialButtonReleased = false;
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 1;
    }
    tutorialButtonReleased = false;
  } else {
    tutorialButtonReleased = true;
    arduboy.setCursor(20, 0);
    arduboy.print("TUTORIAL (2/3):");
    arduboy.setCursor(1, 10);
    arduboy.print("...if not, you");
    arduboy.setCursor(1, 20);
    arduboy.print("you have to wait");
    arduboy.setCursor(1, 30);
    arduboy.print("2 Seconds. A combo");
    arduboy.setCursor(1, 40);
    arduboy.print("gives you a bonus");
    arduboy.setCursor(1, 50);
    arduboy.print("UP to continue");
  }
}


void tutorial3() {
  if (arduboy.pressed(UP_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 0;
    }
    tutorialButtonReleased = false;
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    if (tutorialButtonReleased) {
      showTutorial = 2;
    }
    tutorialButtonReleased = false;
  } else {
    tutorialButtonReleased = true;
    arduboy.setCursor(20, 0);
    arduboy.print("TUTORIAL (3/3):");
    arduboy.setCursor(5, 10);
    arduboy.print("Press A to fire");
    arduboy.setCursor(5, 40);
    arduboy.print("Press UP to");
    arduboy.setCursor(5, 50);
    arduboy.print("start the game");
  }
}

void setup() {
  // Initialize arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(fps);
  arduboy.clear();
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame()))return;
  if (arduboy.everyXFrames(3)) {
  }
  frames++;
  if (arduboy.everyXFrames(3))enemyWalkingFrame++;
  if (enemyWalkingFrame > 5) enemyWalkingFrame = 2;
  arduboy.clear();
  arduboy.pollButtons();
  if (!gameStarted) {
    startScreen();
  } else if (showTutorial == 1) {
    tutorial1();
  } else if (showTutorial == 2) {
    tutorial2();
  } else if (showTutorial == 3) {
    tutorial3();
  } else if (showPoints) {
    listPoints();
  } else {
    update();
  }
  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  arduboy.display();
}
