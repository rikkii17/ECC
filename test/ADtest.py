from gpiozero import MCP3208
from time import sleep

# ピン設定 (BCM番号)
# クロック=23, MOSI=19, MISO=21, CS=24
# ※内部的にSoftware SPIとして動作するよ
adc = MCP3208(
    channel=0, 
    clock_pin=23, 
    mosi_pin=19, 
    miso_pin=21, 
    select_pin=24
)

print("読み取りを開始するよ... (Ctrl+Cで停止)")

try:
    while True:
        # valueは0.0(0V) 〜 1.0(VREF)の範囲で返ってくる
        # 12ビット(0-4095)の数値に変換して表示
        raw_value = int(adc.value * 4095)
        
        # 電圧（3.3V基準の場合）も計算してみよう
        voltage = adc.value * 3.3
        
        print(f"値: {raw_value:4} | 電圧: {voltage:.2f}V")
        sleep(0.5)

except KeyboardInterrupt:
    print("\n終了するよ。")