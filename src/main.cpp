/**
 * @file display.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5StickCPlus2 Display Test
 * @version 0.1
 * @date 2023-12-09
 *
 *
 * @Hardwares: M5StickCPlus2
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5StickCPlus2: https://github.com/m5stack/M5StickCPlus2
 */

#include "M5StickCPlus2.h"

void setup() {

    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(1);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.setTextDatum(middle_center);
    StickCP2.Display.setFont(&fonts::DejaVu12);
    StickCP2.Display.setTextSize(1);

    StickCP2.Lcd.setBrightness(50);
}

void loop(void) {
    StickCP2.Speaker.end();
    auto imu_update = StickCP2.Imu.update();
    if (imu_update) {
        auto data = StickCP2.Imu.getImuData();

        StickCP2.Speaker.tone(data.gyro.y * 100);

        auto time = StickCP2.Rtc.getTime();

        StickCP2.Display.setCursor(0, 40);
        StickCP2.Display.clear();
        StickCP2.Display.printf("%f", data.gyro.y);
    }
    delay(100);
}