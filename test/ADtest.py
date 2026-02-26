from gpiozero import MCP3208
from time import sleep

# port=0, device=0 と指定することでハードウェアSPI(SPI0)を使用する
# これにより、GPIO 11, 10, 9, 8 が自動的に割り当てられる
adc = MCP3208(channel=0, port=0, device=0)

print("ハードウェアSPIで読み取りを開始するよ...")

try:
    while True:
        # 12ビット(0-4095)の数値として取得
        raw_value = int(adc.value * 4095)
        
        # 電圧計算
        voltage = adc.value * 3.3
        
        print(f"値: {raw_value:4} | 電圧: {voltage:.2f}V")
        sleep(0.5)

except KeyboardInterrupt:
    print("\n終了するよ。")