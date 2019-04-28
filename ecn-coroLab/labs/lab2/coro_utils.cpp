#include "tpl_os.h"
#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "mcp23s17.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#define PROGMEM
#define FONT_WIDTH 7
#define FONT_HEIGHT 14
#include "tft/Adafruit-GFX-Library/fontconvert/veraMono6.h"
#define FONT_NAME VeraMono6pt7b

#include "mcp23s17.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


    void setupIOExtender()
    {
        ioExt.begin();
        //portA => leds.
        for(int i=0; i<8;i++)
            ioExt.pinMode(mcp23s17::PORTA,i,mcp23s17::OUTPUT);
        //portB => push buttons and switches
        for(int i=0; i<8;i++)
            ioExt.pinMode(mcp23s17::PORTB,i,mcp23s17::INPUT_PULLUP);
        ioExt.attachInterrupt(mcp23s17::PORTB,4);
        ioExt.attachInterrupt(mcp23s17::PORTB,5);
        ioExt.attachInterrupt(mcp23s17::PORTB,6);
        ioExt.attachInterrupt(mcp23s17::PORTB,7);
    }

    static Adafruit_ST7735 tft = Adafruit_ST7735();

    void eraseDisplay ()
    {
        tft.fillScreen(ST7735_BLACK);
        tft.setCursor(0, FONT_HEIGHT);
    }

    void setupDisplay()
    {
        tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
        tft.setFont(&FONT_NAME);
        tft.setTextColor(ST7735_GREEN);
        eraseDisplay();
    }

    void println_string(const char* str)
    {
        tft.println(str);
    }

    void println_uint(uint32_t ui)
    {
        tft.println(ui);
    }

    void println_int(int32_t i)
    {
        tft.println(i);
    }

    void setupTimer()
    {
        // Timer TIM6 INIT
        RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
        asm("nop");
        // mandatory reset
        RCC->APB1RSTR |= RCC_APB1RSTR_TIM6RST;
        RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;
        asm("nop");
        TIM6->PSC = 64 - 1; /* tick@1us */
        TIM6->CR1 |= TIM_CR1_CEN;
        TIM6->EGR |= TIM_EGR_UG; /* take into account PSC update */
    }

    void reset_timer()
    {
        TIM6->CNT = 0;
    }

    uint32_t get_timer_value()
    {
       return TIM6->CNT;
    }
#ifdef __cplusplus
}
#endif /* __cplusplus */
