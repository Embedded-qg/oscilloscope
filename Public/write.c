#include "system.h"
#include "SysTick.h"
#include "bsp_usart1.h"
#include "tftlcd.h"
#include "write.h"




/*****************************************
	坐标系绘制
*****************************************/
void Write_Chart(int flag)
{


	
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"QG Oscilloscope");
//  LCD_ShowString(10,26,tftlcd_data.width,tftlcd_data.height,16,"-------------------------------------------------");
	LCD_ShowString(345,50,tftlcd_data.width,tftlcd_data.height,16,"P_Vol:");
	LCD_ShowString(345,90,tftlcd_data.width,tftlcd_data.height,16,"LP_Vol:");
	LCD_ShowString(345,130,tftlcd_data.width,tftlcd_data.height,16,"PP_Vol:");
	LCD_ShowString(340,170,tftlcd_data.width,tftlcd_data.height,16,"Freq:");
	//鬼画符
	LCD_DrawXuLine_Color(20,52,320,52,BLUE);
	LCD_DrawXuLine_Color(20,107,320,107,BLUE);
	LCD_DrawXuLine_Color(20,162,320,162,BLUE);
	LCD_DrawXuLine_Color(20,217,320,217,BLUE);
	//水平虚线
	LCD_DrawXuLine_Color(70,35,70,235,BLUE);
	LCD_DrawXuLine_Color(120,35,120,235,BLUE);
	LCD_DrawXuLine_Color(170,35,170,235,BLUE);
	LCD_DrawXuLine_Color(220,35,220,235,BLUE);
	LCD_DrawXuLine_Color(270,35,270,235,BLUE);
	//垂直虚线
	LCD_DrawLine_Color(20,35,20,235,BLACK);
	LCD_DrawLine_Color(20,235,320,235,BLACK);
	LCD_DrawLine_Color(320,35,320,235,BLACK);
	LCD_DrawLine_Color(20,35,320,35,BLACK);
	//矩形线框
	switch(flag)  //不同精度的表格绘制
	{
		case 0:
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"5ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"10ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"15ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"20ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"25ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"30ms");
		}break;
		case 1:	
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"10ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"20ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"30ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"40ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"50ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"60ms");
		}break;
		case 2:	
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"20ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"40ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"60ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"80ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"100ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"120ms");
		}break;
		case 3:	
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"40ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"80ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"120ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"160ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"200ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"240ms");
		}break;
		case 4:	
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"80ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"160ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"240ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"320ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"400ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"480ms");
		}break;
		case 5:	
		{
			LCD_ShowString(24,218,tftlcd_data.width,tftlcd_data.height,16,"0ms");
			LCD_ShowString(74,218,tftlcd_data.width,tftlcd_data.height,16,"160ms");
			LCD_ShowString(124,218,tftlcd_data.width,tftlcd_data.height,16,"320ms");
			LCD_ShowString(174,218,tftlcd_data.width,tftlcd_data.height,16,"480ms");
			LCD_ShowString(224,218,tftlcd_data.width,tftlcd_data.height,16,"640ms");
			LCD_ShowString(274,218,tftlcd_data.width,tftlcd_data.height,16,"800ms");
			LCD_ShowString(324,218,tftlcd_data.width,tftlcd_data.height,16,"960ms");
		}break;
	}
	//水平单位

	LCD_ShowString(300,200,tftlcd_data.width,tftlcd_data.height,16,"0V");
	LCD_ShowString(285,145,tftlcd_data.width,tftlcd_data.height,16,"1.1V");
	LCD_ShowString(285,90,tftlcd_data.width,tftlcd_data.height,16,"2.2V");
	LCD_ShowString(285,37,tftlcd_data.width,tftlcd_data.height,16,"3.3V");
	//垂直单位
}

