// 燈珠配置
int colorTempHigh     = 5600;
int colorTempMiddle   = 2900;
int colorTempLow      = 1700;
int colorTempSuperlow = 1450;

// 假設LED有一起始電壓, 並且各色燈珠亮度對電壓為線性, 且敏感度不同
// 起始電壓、實驗量測
float initVolHigh     = 0;
float initVolMiddle   = 0;
float initVolLow      = 0;
float initVolSuperlow = 0;

// 亮度對電壓斜率、實驗擬合
float lightCoeffHigh     = 1.5;
float lightCoeffMiddle   = 1.5;
float lightCoeffLow      = 1.5;
float lightCoeffSuperlow = 1.7;


// 從色溫、亮度計算pin腳數值
void get_pin_val_from_lightcolor(int fourPin[], int colorTemp, int illuminance) {
  float color_ratio;
  float vRatio_higher;  // 色溫求得 兩燈珠之間較高色溫的燈珠電壓, 假設低色溫電壓為3時

  // 色溫高於高色溫燈珠
  if (colorTemp >= colorTempHigh) {
    fourPin[0] = 255 * illuminance / 100;
    fourPin[1] = 0;
    fourPin[2] = 0;
    fourPin[3] = 0;
  }

  // 色溫介於高色溫燈珠 and 中色溫燈珠
  else if (colorTemp >= colorTempMiddle) {
    color_ratio = (colorTemp - colorTempMiddle) / (colorTempHigh - colorTemp);
    vRatio_higher = color_ratio * (lightCoeffMiddle / lightCoeffHigh) * (3.0f - initVolMiddle);
    
    fourPin[0] = 255 * (vRatio_higher * illuminance / max(vRatio_higher, 3.0f) + initVolHigh) / 100;
    fourPin[1] = 255 * (          3.0 * illuminance / max(vRatio_higher, 3.0f) + initVolMiddle) / 100;
    fourPin[2] = 0;
    fourPin[3] = 0;
  }

  // 色溫介於中色溫燈珠 and 低色溫燈珠
  else if (colorTemp >= colorTempLow) {
    color_ratio = (colorTemp - colorTempLow) / (colorTempMiddle - colorTemp);
    vRatio_higher = color_ratio * (lightCoeffLow / lightCoeffMiddle) * (3.0f - initVolLow);
    
    fourPin[0] = 0;
    fourPin[1] = 255 * (vRatio_higher * illuminance / max(vRatio_higher, 3.0f) + initVolMiddle)  / 100;
    fourPin[2] = 255 * (          3.0 * illuminance / max(vRatio_higher, 3.0f) + initVolLow) / 100;
    fourPin[3] = 0;
  }

  // 色溫介於低色溫燈珠 and 超低色溫燈珠(含)
  else if (colorTemp >= colorTempSuperlow) {
    color_ratio = (colorTemp - colorTempSuperlow) / (colorTempLow - colorTemp);
    vRatio_higher = color_ratio * (lightCoeffSuperlow / lightCoeffLow) * (3.0f - initVolSuperlow);
    
    fourPin[0] = 0;
    fourPin[1] = 0;
    fourPin[2] = 255 * (vRatio_higher * illuminance / max(vRatio_higher, 3.0f) + initVolLow)  / 100;
    fourPin[3] = 255 * (          3.0 * illuminance / max(vRatio_higher, 3.0f) + initVolSuperlow)  / 100;
  }

  // Serial.print("燈珠電壓比: ");   delete
  // Serial.println(color_ratio);
  // Serial.println(vRatio_higher);
}



void write_four_pin(int high, int middle, int low, int superlow) {
  analogWrite(ledPin_yellow, high);
  analogWrite(ledPin_green, middle);
  analogWrite(ledPin_red, low);
  analogWrite(ledPin_other, superlow);
}