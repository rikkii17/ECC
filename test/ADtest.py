from gpiozero import MCP3208
from time import sleep

# ラズパイ5のBCMピン番号を指定
# クロック=23, MOSI=19, MISO=21, CS=24
# ※gpiozeroのMCP3208クラスは標準SPIピンを想定することが多いけど、
# 任意のピンでソフトSPIっぽく動かすなら以下のように指定できるよ。

# デバイスの初期化（channel 0を使用）
# もし標準のハードウェアSPIを使うなら、もっとシンプルに書けるよ。
pot = MCP3208(channel=0, clock_pin=23, mosi_pin=19, miso_pin=21, select_pin=24)

try:
    while True:
        # valueは0.0から1.0で返ってくるから、12ビット(4095)に変換
        voltage = pot.value * 4095
        print(f"ADC Value: {voltage:.0f}")
        sleep(0.2)

except KeyboardInterrupt:
    pass