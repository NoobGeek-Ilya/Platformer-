
#include <Arduboy2.h>
Arduboy2 arduboy;
#define GAME_TITLE  0
#define GAME_PLAY  1
#define GAME_OVER  2
#define GAME_HIGH  3
int gamestate = GAME_TITLE;
bool topColl;
bool bottomColl;
bool rightColl;
bool leftColl;
Rect player = {10, 10, 10, 10};

#define WORLD_WIDTH   16
#define WORLD_HEIGHT  8
int world[WORLD_HEIGHT][WORLD_WIDTH] = {
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
  { 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}
};

void drawworld() {
  arduboy.print(rightColl);
  for (int y = 0; y < WORLD_HEIGHT; y++) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        if(world[y][x] == 1){
         arduboy.drawRect(x * 8, y * 8, 8, 8);      
        }
    }
  }
}

void titlescreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("Title Screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_PLAY;
  }
}

void gameplay() {
  drawworld();
  MovePlayer();
  DrawPlayer();
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_OVER;
  }
}

void gameoverscreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("Game Over Screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_HIGH;
  }
}

void highscorescreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("High Score Screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_TITLE;
  }
}

void gameloop() {

  switch(gamestate) {
  
    case GAME_TITLE:
      titlescreen();
      break;

    case GAME_PLAY:
      gameplay();
      break;

    case GAME_OVER:
      gameoverscreen();
      break;

    case GAME_HIGH:
      highscorescreen();
      break;
      
  }
  
}

void DrawPlayer(){
  arduboy.fillRect(player.x, player.y, player.width, player.height);
}

void MovePlayer(){
  if(arduboy.pressed(RIGHT_BUTTON)){
      int newX = player.x + 1;
      int tileX = (newX + 8) / 8;
      int tileY = player.y / 8;
        if(world[tileY][tileX] == 0)
          player.x = newX;
  }
  
  if(arduboy.pressed(LEFT_BUTTON)){
      int newX = player.x - 1;
      int tileX = newX / 8;
      int tileY = player.y / 8;
        if(world[tileY][tileX] == 0)
            player.x = newX;
  }

  if(arduboy.pressed(UP_BUTTON)){
      int newY = player.y - 1;
      int tileY = newY / 8;
      int tileX = player.x / 8;
        if(world[tileY][tileX] == 0)
            player.y = newY;
  }
  
  if(arduboy.pressed(DOWN_BUTTON)){
      int newY = player.y + 1;
      int tileY = (newY + 8) / 8;
      int tileX = player.x / 8;
        if(world[tileY][tileX] == 0)
            player.y = newY;
  }
}

void setup() {

  arduboy.begin();
  arduboy.setFrameRate(45);
  arduboy.display();
  arduboy.initRandomSeed();  
  arduboy.clear();
  
}

void loop() {

  if(!(arduboy.nextFrame())) {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();
  gameloop();
  arduboy.display();
}
