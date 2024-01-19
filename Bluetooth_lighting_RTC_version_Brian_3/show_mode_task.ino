void showmodeTaskFunction(void *pvParameters) {
  while (1) {
    if (!shouldExitBluetoothTask){
      // 在這裡處理你的副任務邏輯
      // Serial.println("循環開始");
      // print_current_time();

      for (int i = 0; i < sizeof(cmode) / sizeof(cmode[0]); i++){
        write_four_pin(cmode[i][0], cmode[i][1], cmode[i][2], cmode[i][3]);  
        delay(delay_per_minute); // 可以调整循环的延迟时间

        // 立即性停止show mode
        if (shouldExitBluetoothTask) {
          break;
        }
      }

      // Serial.println("循環結束");
      // print_current_time();
    }
    else {
      delay(200);
    }
    
  }
}