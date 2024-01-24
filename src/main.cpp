#include <M5StickCPlus2.h>

M5GFX display;
M5Canvas backgroundCanvas;
M5Canvas clockCanvas;
M5Canvas menuCanvas;

#define MENU_ITEMS 3

char menuItems[MENU_ITEMS][10] = {"App1", "App2", "App3"};

bool showMenu = false;
bool redrawBackground = false;

size_t previousSeconds = -1;
size_t selected = 0;
char timeString[20];

#define BG_COLOR BLACK
#define CLOCK_BG_COLOR BLACK
#define CLOCK_COLOR ORANGE
#define MENU_BG_COLOR BLACK
#define MENU_ITEM_COLOR WHITE
#define MENU_ITEM_SELECTED_COLOR YELLOW

void drawMenuSprite();
void drawClockSprite(m5::rtc_time_t time);

void setup() {
    M5.begin();
    display.begin();
    display.setRotation(1);
    display.setBrightness(50);

    clockCanvas.setTextSize(4);
    clockCanvas.setTextDatum(MC_DATUM);
    clockCanvas.setTextColor(CLOCK_COLOR);
    clockCanvas.createSprite(display.width(), clockCanvas.fontHeight());

    menuCanvas.setTextSize(3);
    menuCanvas.createSprite(display.width(), display.height());
    drawMenuSprite();
}

void loop() {
    M5.update();

    if (M5.BtnB.wasClicked()) {
        redrawBackground = true;
        showMenu = !showMenu;
    }

    // draw into sprites
    if (showMenu) {
        if (M5.BtnA.wasClicked()) {
            selected = (selected + 1) % MENU_ITEMS;
            drawMenuSprite();
        }
    } else {
        auto time = M5.Rtc.getTime();
        if (time.seconds != previousSeconds) {
            drawClockSprite(time);
        }
    }

    // composing display from sprites
    display.startWrite();
    if (redrawBackground) {
        display.clear(BLACK);
        redrawBackground = false;
    }
    if (showMenu) {
        menuCanvas.pushSprite(&display, 0, 0);
    } else {
        clockCanvas.pushSprite(&display, 0, display.height() / 3);
    }
    display.endWrite();

    delay(200);
}

void drawClockSprite(m5::rtc_time_t time) {
    clockCanvas.fillSprite(CLOCK_BG_COLOR);
    sprintf(timeString, "%02d:%02d:%02d", time.hours, time.minutes,
            time.seconds);
    clockCanvas.drawString(timeString, clockCanvas.width() / 2,
                           clockCanvas.height() / 2);
}

void drawMenuSprite() {
    menuCanvas.fillSprite(BLACK);
    menuCanvas.setCursor(0, 0);
    for (size_t i = 0; i < MENU_ITEMS; ++i) {
        menuCanvas.setTextColor(i == selected ? YELLOW : WHITE);
        menuCanvas.println(menuItems[i]);
    }
}