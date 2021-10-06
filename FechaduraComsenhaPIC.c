#include<16f628.h>
#use delay(clock=4000000)
#define use_portb_lcd TRUE
#include <lcd.c>
#fuses XT,NOWDT,PUT,BROWNOUT,NOMCLR,NOLVP

/*********************Variaveis globais***************************/
int k = 0;
long long num = 0, senha = 12345;
/*********************Prototipos de funcao***********************/
int keyboard();
void code();
/****************************************************************/


void main()
{
   lcd_init();
   lcd_putc("   Fechadura \n   Eletronica");
   delay_ms(2000);
   lcd_putc("\fSenhaDeLiberacao\n     *****");
   output_bit(PIN_b3,0);
while(true)
{
 k = keyboard();
 code();
}
}
void code()
{
   if(k < 10)
   {
      num = num * 10 + k;
      lcd_putc("\fSenhaDeLiberacao\n     *****");
      lcd_gotoxy(6,0);
         if(num <= 99999)
         {
            printf(lcd_putc,"%lu",num);
         }
      delay_ms(200);
   }
   if(k==10 || (k==12 && senha != num) || num >99999)
   {
      num =0;
      output_bit(PIN_b3,0);
      lcd_putc("\fSenhaDeLiberacao\n     *****");
      delay_ms(200);
   }
   if(k==12 && senha == num)
   {
      for(int i=0;i<4;i++)
      {
         lcd_putc("\f");
         delay_ms(400);
         lcd_putc("ACESS.....");
         delay_ms(400);
      }
      lcd_putc("\fPressione *\nPara Sair");
    output_bit(PIN_b3,1);
   }
  if(k==12 && senha != num)
  {
   for(int i=0;i<4;i++)
      {
         lcd_putc("\f");
         delay_ms(400);
         lcd_putc("Senha Incorreta\n   Pressione *");
         delay_ms(400);
      }
  }
   delay_ms(80);
}
int keyboard()
{
   int ret = 13;
   int pOut[4] = {PIN_a1,PIN_a2,PIN_a3,PIN_a4};
   int pIn[3] = {PIN_a0,PIN_a7,PIN_a6};
      for(int i=0;i<4;i++)
      {
         output_bit(pOut[i],0);
            for(int j=0;j<3;j++)
            {
               if(!input(pIn[j]))
               {
                  ret = i * 3 + j + 1;
               }
            }
          output_bit(pOut[i],1);
          
      }
   return(ret != 11) ? ret : 0;
}   
