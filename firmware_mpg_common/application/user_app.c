/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/
/**
 Function user by yan


//
Description :
led pattern display.
squence display
**/

static void led_on_display()
{
   static u32 u32_display_timer =0;
   static u8 u8_led_num =0;
   u8 u8_counter;
   u32_display_timer++;
   if(u32_display_timer%1000==0)
   {
     for(u8_counter=0;u8_counter<=8;u8_counter++)
     {
       if(u8_counter==u8_led_num)
         LedOn(u8_counter);
       else
         LedOff(u8_counter);
     }
     if(u8_led_num<=8)
     u8_led_num++;
     else
       u8_led_num=0;
   }
}
////
/// back and forth 
static void led_on_display_pattern()
{
  static u32 u32_display_timer =0;//function clock
  static u8  u8_led_num=0;       //the number of leds
  static u8  u8_squence_timer=0;//the time of circles
 static  u8  u8_divid_clock  =0;//to divided the time
  u8  u8_counter;               //temp counter
  u32_display_timer++;
 // if(u32_display_timer%(2500/(u8_squence_timer+1))==0)
  //if(u32_display_timer%(2500/(u8_led_num+u8_squence_timer+1))==0)
  if(u32_display_timer%(2500/(u8_divid_clock+1))==0)
    {
        switch(u8_squence_timer)
        {   
        case 0://the forth
          for(u8_counter=0;u8_counter<=8;u8_counter++)
            {if(u8_counter==u8_led_num)
              LedOn(u8_counter);
             else
               LedOff(u8_counter);
            }
          break;
        case 1://back 
           for(u8_counter=0;u8_counter<=8;u8_counter++)
            {if(u8_counter==(8-u8_led_num))
              LedOn(8-u8_led_num);
            else
             LedOff(u8_counter);
          }
          break;
        case 2:
          for(u8_counter=0;u8_counter<=8;u8_counter++)
            {if(u8_counter==u8_led_num)
              LedOn(u8_counter);
             else
               LedOff(u8_counter);
            }
          break;
        case 3://back 
            for(u8_counter=0;u8_counter<=8;u8_counter++)
              {if(u8_counter==(8-u8_led_num))
              LedOn(8-u8_led_num);
              else
              LedOff(u8_counter);
              }
        break;
        }
       if(u8_led_num>9)
       {
         u8_led_num=0;
         u8_squence_timer++;
         if(u8_squence_timer==4)
           u8_squence_timer =0;
       }
        
         u8_led_num++; 
        u8_divid_clock++;
        if(u8_divid_clock>=100)
          u8_divid_clock=0;
    }
  
}
static void led_pattern_display_two()
{
  static u32 u32_display_timer =0;
  static u8  u8_led_num=0;
  u8  u8_counter;
  u32_display_timer++;
  
 
 if(u32_display_timer%(1000/(u8_led_num+1))==0)
  {
    LedOn(4+u8_led_num-1);
    LedOn(3-u8_led_num+1);
     if(u8_led_num==5)//time is important
        {
           for(u8_counter=0;u8_counter<=7;u8_counter++)
            LedOff(u8_counter);//ledo
           u8_led_num =0;
          
      }
      u8_led_num++;
  }
 if(u32_display_timer==100000)
   u32_display_timer=0;
}
/**
 Function user by yan


//
Description :
led pattern display.
squence display
**/
static void led_pattern_display()
{
   static u32 u32_display_timer=0;
   static u8  u8_led_num=0;
  u8 led_num;
  //for(led_num=0;led_num<=6;led_num++)
 //   LedOff(led_num);//ledo
  u32_display_timer++;
  if(u32_display_timer%1000==0)
  {
    LedOn(u8_led_num);
    u8_led_num++;
    if(u8_led_num==9)//time is important
    {
       for(led_num=0;led_num<=7;led_num++)
        LedOff(led_num);//ledo
       u8_led_num =0;
      
    }
   //  u8_led_num++;
  } 
}

///
/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
//Button press to implenent is changed. by yan

static void change_mession()
{
  static u8 Task_change =0;
     if(WasButtonPressed(BUTTON1))
     {
       ButtonAcknowledge(BUTTON1);
       Task_change++;
       if(Task_change>=4)
         Task_change=0;
     }
     switch(Task_change)
     {
     case 0:
          led_pattern_display();
       break;
     case 1:
          led_on_display();
       break;
     case 2:
       led_on_display_pattern();
       break;
     case 3:
       led_pattern_display_two();
       break;
     }
}



/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserAppInitialize(void)
{
#ifdef MPGL1
  /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  /* Backlight to white */  
  LedOn(LCD_RED);
  LedOn(LCD_GREEN);
  LedOn(LCD_BLUE);
#endif /* MPGL1 */

#ifdef MPGL2
  /* All discrete LEDs to off */
  LedOff(RED0);
  LedOff(RED1);
  LedOff(RED2);
  LedOff(RED3);
  LedOff(GREEN0);
  LedOff(GREEN1);
  LedOff(GREEN2);
  LedOff(GREEN3);
  LedOff(BLUE0);
  LedOff(BLUE1);
  LedOff(BLUE2);
  LedOff(BLUE3);
  
  /* Backlight to white */  
  LedOn(LCD_BL);
#endif /* MPGL2 */
  
  /* If good initialization, set state to Idle */
  if( 1 /* Add condition for good init */)
  {
    //UserApp_StateMachine = UserAppSM_Idle;
    UserApp_StateMachine = change_mession;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp_StateMachine = UserAppSM_FailedInit;
  }

} /* end UserAppInitialize() */



/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserAppRunActiveState(void)
{
  UserApp_StateMachine();

} /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Update counter and display on LEDs. */
static void UserAppSM_Idle(void)
{
  static u16 u16BlinkCount = 0;
  static u8 u8Counter = 0;
  static u8 u8ColorIndex = 0;
  
#ifdef MPG1
  u16BlinkCount++;
  if(u16BlinkCount == DELAY_TIME)
  {
    u16BlinkCount = 0;
    u8Counter++;
    
    /* Parse the current count to set the LEDs.  RED is bit 0, ORANGE is bit 1,
    YELLOW is bit 2, GREEN is bit 3. */
    
    if(u8Counter & 0x01)
    {
      LedOn(RED);
    }
    else
    {
      LedOff(RED);
    }

    if(u8Counter & 0x02)
    {
      LedOn(ORANGE);
    }
    else
    {
      LedOff(ORANGE);
    }

    if(u8Counter & 0x04)
    {
      LedOn(YELLOW);
    }
    else
    {
      LedOff(YELLOW);
    }

    if(u8Counter & 0x08)
    {
      LedOn(GREEN);
    }
    else
    {
      LedOff(GREEN);
    }

    /* Check if the counter should roll and update the blacklight */
    if(u8Counter == 16)
    {
      u8Counter = 0;
      
      /* Manage the backlight color */
      u8ColorIndex++;
      if(u8ColorIndex == 7)
      {
        u8ColorIndex = 0;
      }
      
      /* Set the backlight color: white (all), purple (blue + red), blue, cyan (blue + green),
      green, yellow (green + red), red */
      switch(u8ColorIndex)
      {
        case 0: /* white */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;

        case 1: /* purple */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 2: /* blue */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 3: /* cyan */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOn(LCD_BLUE);
          break;
          
        case 4: /* green */
          LedOff(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 5: /* yellow */
          LedOn(LCD_RED);
          LedOn(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        case 6: /* red */
          LedOn(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
          
        default: /* off */
          LedOff(LCD_RED);
          LedOff(LCD_GREEN);
          LedOff(LCD_BLUE);
          break;
      } /* end switch */
    } /* end if(u8Counter == 16) */
    
  } /* end if(u16BlinkCount == DELAY_TIME) */
#endif /* MPGL1 */

#ifdef MPG2
  u16BlinkCount++;
  if(u16BlinkCount == DELAY_TIME)
  {
    u16BlinkCount = 0;
    
    /* Update the counter and roll at 16 */
    u8Counter++;
    if(u8Counter == 16)
    {
      u8Counter = 0;
      
      LedOff((LedNumberType)(RED3 + (4 * u8ColorIndex)));
      LedOff((LedNumberType)(RED2 + (4 * u8ColorIndex)));
      LedOff((LedNumberType)(RED1 + (4 * u8ColorIndex)));
      LedOff((LedNumberType)(RED0 + (4 * u8ColorIndex)));
      
      u8ColorIndex++;
      if(u8ColorIndex == 3)
      {
        u8ColorIndex = 0;
      }
    } /* end if(u8Counter == 16) */
    
    /* Parse the current count to set the LEDs.  From leds.h we see the enum for red, green and blue
    are seperated by 4 so use this with u8ColorIndex to */
    
    if(u8Counter & 0x01)
    {
      LedOn((LedNumberType)(RED3 + (4 * u8ColorIndex)));
    }
    else
    {
      LedOff(RED3 + (4 * u8ColorIndex));
    }

    if(u8Counter & 0x02)
    {
      LedOn(RED2 + (4 * u8ColorIndex));
    }
    else
    {
      LedOff(RED2 + (4 * u8ColorIndex));
    }

    if(u8Counter & 0x04)
    {
      LedOn(RED1 + (4 * u8ColorIndex));
    }
    else
    {
      LedOff(RED1 + (4 * u8ColorIndex));
    }

    if(u8Counter & 0x08)
    {
      LedOn(RED0 + (4 * u8ColorIndex));
    }
    else
    {
      LedOff(RED0 + (4 * u8ColorIndex));
    }
    
  } /* end if(u16BlinkCount == DELAY_TIME) */
#endif /* MPG2 */  
  
} /* end UserAppSM_Idle() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserAppSM_Error(void)          
{
  UserApp_StateMachine = UserAppSM_Idle;
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserAppSM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
