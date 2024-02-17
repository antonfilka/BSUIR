#include <msp430.h> 

char compareLedMode = 0;  // 0 - отключен, 1 - сравнение между PAD3 и PAD1
volatile int i;

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
    for(i=0;i<2500;i++);

    if(!(P1IN & BIT7))     {
        P1IFG &= ~BIT7;

        if(!compareLedMode)             {
                P1OUT &= ~BIT1;
                P1OUT &= ~BIT3;

                //Disable interrupt
               CBINT &= ~CBIE;
               CBINT &= ~CBIIE;
               //Disable comparator
               CBCTL1 &= ~CBON;

               //enable ADC
               ADC12CTL0 |= ADC12ON;
               //enable ADC convertion and start calc
               ADC12CTL0 |= ADC12ENC | ADC12SC;
               // enable channel 1 interrupts
               ADC12IE |= ADC12IE1;
               //clear
               ADC12IFG &= ~ADC12IFG1;
            }
        else {
            P1OUT &= ~BIT0;
            P8OUT &= ~BIT2;

            //disable interrupts
            ADC12IE &= ~ADC12IE1;
            //disable ADC
            ADC12CTL0 &= ~ADC12ON;
            //disable ADC convertion and reset start calc bit
            ADC12CTL0 &= ~(ADC12ENC | ADC12SC);

            //Enable comparator
            CBCTL1 |= CBON;
            //Enable interrupt (main & inverted)
            CBINT |= CBIE;
            CBINT |= CBIIE;
            //clear
            CBINT &= ~CBIFG;
            CBINT &= ~CBIIFG;
        }

        compareLedMode ^= BIT0;
    }
}

/**
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//led_init();
	P1DIR |= BIT0 | BIT1 | BIT3; // настройка светодиодов на выход
    P8DIR |= BIT2;

    P1OUT &= ~BIT0;
    P1OUT &= ~BIT1;
    P1OUT &= ~BIT3;
    P8OUT &= ~BIT2;

	// S1 init
	P1DIR &= ~BIT7;
    P1REN |= BIT7;  // разрешение подтягивающего резистора
    P1OUT |= BIT7;  // настройка подтягивающего резистора
    P1IES |= BIT7;  // прерывание по спаду (нажатие кнопки)
    P1IFG &= ~BIT7; // обнуление флага прерывания кнопки
    P1IE |= BIT7;   // разрешение прерывания

	// ADC init
	//enable potentiometer
    ////set potentiometer output as analog input
    P6SEL |= BIT5;
    ////set potentiometer input (max value) to "1"
    P8DIR |= BIT0;
    P8OUT |= BIT0;

    //select start scanning from 0
    ADC12CTL1 &= ~(ADC12CSTARTADD0 | ADC12CSTARTADD1 | ADC12CSTARTADD2 | ADC12CSTARTADD3);
    ADC12CTL1 &= ~(ADC12SHS0 | ADC12SHS1);	//Source select = ADC12SC    
    ADC12CTL1 |= ADC12SSEL0 | ADC12SSEL1;	//adc clock select (SMCLK)    
    ADC12CTL1 |= ADC12SHP;	//Pulse mode enable    
    ADC12CTL1 |= ADC12CONSEQ0 | ADC12CONSEQ1;	//repeated multichannel mode select    
    ADC12CTL0 |= ADC12MSC;	//enable auto sampling (but need first SHI rising edge)    
    ADC12CTL2 &= ~(BIT5 | BIT4);	//set adc resolution for 8 bits    
    ADC12CTL2 &= ~ADC12SR;	//set sample rate buffer to 50ksps    
    ADC12MCTL0 |= ADC12INCH_5;	// channel 0 config (select potentiometer as source)
    // channel 1 config (select temp as source)
    //set channel 1 as last for adc
    ADC12MCTL1 |= ADC12EOS;    
    ADC12MCTL1 |= ADC12INCH_9;	//select channel source

	// Comp init

    CBCTL0 |= CBIMEN + CBIMSEL_2;	// разрешение входного канала V- и выбор входного канала pad3
    CBCTL0 |= CBIPEN + CBIPSEL_0;	// разрешение входного канала V+ и выбор входного канала pad1

    CBCTL1 |= CBFDLY_3;		// задержка фильтра 3,4 мкс
    CBCTL1 |= CBF;			// включаем выходной фильтр
    CBCTL1 &= ~CBIES;		// прерывания по фронту
    //Set comparator power mode to ultra low power
    CBCTL1 |= BIT9;
    CBCTL1 &= ~BIT8;
    //set other pads as input pullup
    P6DIR &= ~(BIT0 | BIT2 | BIT4);
    P6OUT |= BIT0 | BIT2 | BIT4;

    CBCTL1 |= CBON;			// включение компаратора
    CBINT |= CBIE;			// разрешаем прерывания компаратора
    CBINT |= CBIIE;			// разрешаем инверсные прерывания компаратора

    CBINT &= ~CBIFG;		// сбрасываем флаг прерывания компаратора
    CBINT &= ~CBIIFG;		// сбрасываем флаг инверсного прерывания компаратора


	__bis_SR_register(GIE + LPM0_bits);
	//while(1);
	__no_operation();

	return;
}

#pragma vector=COMP_B_VECTOR 
__interrupt void comparator_interrupt() {

   if(CBCTL1 & CBOUT) { // если на выходе компаратора 1, то + > -
       P1OUT |= BIT1;	// зажигаем pad1 
       P1OUT &= ~BIT3;
   }
   else {
       P1OUT &= ~BIT1;  // в противном случае
       P1OUT |= BIT3;	// зажигаем pad3
   }

   CBINT &= ~CBIFG;  // сбрасываем флаг прерывания
   CBINT &= ~CBIIFG; // сбрасываем флаг инверсного прерывания
}

#pragma vector=ADC12_VECTOR
__interrupt void adc_interrupt() {

    short val_UREF = ADC12MEM1;		// читаем значение Vref
    short val_potent = ADC12MEM0;	// читаем значение с потенциометра

    if(val_UREF > val_potent) {		// если Vref больше
        P1OUT |= BIT0;				// зажигаем led1
        P8OUT &= ~BIT2;
    }
    else {							// в противном случае
        P1OUT &= ~BIT0;				// зажигаем led2
        P8OUT |= BIT2;
    }

    ADC12IFG &= ~ADC12IFG1;			// сбрасываем флаг прерывания
}
