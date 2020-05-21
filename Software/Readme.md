## 概述

代码采用cubemx生成







## 矩阵双模键盘

| Fun  | Pin  |
| ---- | ---- |
| C1   | PA1  |
| C2   | PA2  |
| C3   | PA3  |
| R1   | PA4  |
| R2   | PA5  |
| R3   | PA6  |
| R4   | PA7  |
| TXD/D-   | PA9/PA11  |
| RXD/D+   | PA10/PA12  |



### 串口模式

- FPC排线引出
- 蓝牙MESH引出

### USB模式





`main.h`

```c
/* USER CODE BEGIN Includes */
#define USART_KEY 0			//0 USB模式  1串口模式
/* USER CODE END Includes */
```





### Tip

因为修改了非用户代码，所以把 *.ioc文件删除了

