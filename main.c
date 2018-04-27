#define F_CPU (16000000UL)
#define SPEED 100

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "lcd0.h"
#include "uart.h"


void portinic();
void Timer2_init();
void led_out(unsigned char led);
void rgb_on();
void rgb_off();
unsigned char btn_in();
void ss_out();

void _dly_7s (short int d); 	
void matrix();
void x_inc();
void x_dec();
void y_inc();
void y_dec();
void next_pos(unsigned char k);


unsigned char kp=0, cnt=0, t=0, ch=0x00, btn=0, ss[4], keyr=0, col=0, keyin=10, rlse_cntr=0, last_value=0;
//kp: keypressed happened, kp tárolja mely bill lett leütve
unsigned char snake[64], y[64], x[64], l=14, last=0, first=0, nxt_y=0, nxt_x=0, c=0;


int main()
{
	portinic();
	lcd_init();
	
	Uartinit();
	Timer2_init();
	
	CreateCGram();
	
	
	
	c=l;
	first = l-1;
	while(c--)
	{
	snake[c]=c;
		
        y[c]=0;
        x[c]=c;		
	lcd_gotoyx(y[c],x[c]);
	lcd_data(0x00);
	lcd_cmd(0x0C);//cursor off
	
	}
	
	nxt_y = y[first];
	nxt_x = x[first];
	
	ss[3] = nxt_y/10;
        ss[2] = nxt_y%10;
        ss[1] = nxt_x/10;
        ss[0] = nxt_x%10;
	
	UartSendByte(12);
	UartSendString("Snake is Ready!");
	        
        sei();
        
                

//MAIN LOOP
while(1){

        

        matrix();
        
        if((t==1) && (kp==2 || kp==8 || kp==4 || kp==6)){
       
        t=0;
       
        lcd_gotoyx(y[last],x[last]);
        lcd_data(0x01);
        lcd_cmd(0x0C);
     
        next_pos(kp); 
        
        first=last;
        
        y[first]=nxt_y;
        x[first]=nxt_x;
        
        if(last<l-1) last=snake[last+1];
        else last=0;
        
        lcd_gotoyx(y[first],x[first]);
        lcd_data(0x00);
        lcd_cmd(0x0C);
          
        
                 
        ss[3] = nxt_y/10;
        ss[2] = nxt_y%10;
        ss[1] = nxt_x/10;
        ss[0] = nxt_x%10; 
        ss_out();
                 
        
        c++;
        
        }//if
                       
                
        
               
}//while MAIN

}//main





  /////////////////////////////////////////
 //	FV. DEFFINITIONS		//
/////////////////////////////////////////


void portinic()
{
	DDRA=0xFF;
	DDRB=0xF0;
	DDRC=0xF8;
	DDRD=0xF0;
	DDRE=0xC0;
	DDRG=0x00;
}

//////////
void Timer2_init() {
        TIMSK|=(1<<TOIE2);
        TCCR2|=(1<<CS22);
}

void led_out(unsigned char led)
{
	PORTD=led;
	PORTB=(led<<4);
}

//////

unsigned char btn_in()
{
	return PING;
}

//////

void ss_out()
{
	unsigned char digit=0,j=0;
	
	
		while(digit<4)
		{
		PORTA=(0x80+(digit<<4)+ss[j]); //PORTA=(ENGbit+digitbitek+kiirnadóérték(0-9))
		digit++;
		j++;
		//if (digit==4){digit=0; j=0;}
		_delay_ms(1);
		}
	
	
}

///////



void _dly_7s (short int d)
{
	
	while(d--)
	ss_out();
		
}


///////




void matrix ()
{

        keyr=0x08;
        
        
	while(keyr!=0x80) {
		keyin=10;
		//led_out(rlse_cntr);	
		PORTC = keyr;
		
		_dly_7s(1);
		
		col = PINC;
		col &= 7;
		switch (col) {
			case 0x06: {
				switch (keyr) {
					case 0x08: { keyin=1; break;}
					case 0x10: { keyin=4; break;}
					case 0x20: { keyin=7; break;}
					case 0x40: { break;}
					} //sw keyr
				 break;} // case col
			case 0x05: {
				
				switch (keyr) {
					case 0x08: { keyin=2; break;}
					case 0x10: { keyin=5; break;}
					case 0x20: { keyin=8; break;}
					case 0x40: { keyin=0; break;}
					} //sw keyr
				 break;} // case col
			case 0x03: {
				
				switch (keyr) {
					case 0x08: { keyin=3; break;}
					case 0x10: { keyin=6; break;}
					case 0x20: { keyin=9; break;}
					case 0x40: {  break;}
					} //sw keyr
				 break;} // case col
		}//switch col

		keyr<<=1;
		
			
		
		if (keyin==last_value && rlse_cntr<5) {
			 rlse_cntr=0; continue;
			}

		if (keyin==10  && rlse_cntr<5) {
			 rlse_cntr++; continue;
			}
		
		if ((keyin!=10 && keyin==last_value && rlse_cntr>=5) || (keyin!=10 && keyin!=last_value)) {
			 rlse_cntr=0; 
			 last_value=keyin;
			 UartSendByte(keyin+48);
			 kp=keyin;
			 continue;
			}

		
			
		
		
	}//while keyr
	
        if (keyr==0x80) keyr=0x08;

}



void x_inc() {

        if(nxt_x<15) nxt_x++;
        else nxt_x=0;

}

void x_dec()
{
        if(nxt_x>0) nxt_x--;
        else nxt_x=15;
}

void y_inc()
{
        if(nxt_y<3) nxt_y++;
        else nxt_y=0;
}


void y_dec()
{
        if(nxt_y>0) nxt_y--;
        else nxt_y=3;
}

next_pos(unsigned char k)
{
        switch (k) {
          case 2: { y_dec(); break; }
          case 8: { y_inc(); break; }
          case 4: { x_dec(); break; }
          case 6: { x_inc(); break; }
          }//sw
          
}


ISR(USART0_RX_vect)
{
        
        unsigned char ch=UDR0;
        led_out(ch);
        
	
}


ISR(TIMER2_OVF_vect)
{
	TCNT2=0;
	cnt++;	

        if (cnt==SPEED) {
        
        t=1;
        cnt=0;

	}
	
}




