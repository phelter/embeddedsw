/*****************************************************************************/
/**
*
* @file xpm_counter.h
*
* @addtogroup a9_event_counter_apis Cortex A9 Event Counters Functions
*
* Cortex A9 event counter functions can be utilized to configure and control
* the Cortex-A9 performance monitor events.
*
* Cortex-A9 performance monitor has six event counters which can be used to
* count a variety of events described in Coretx-A9 TRM. xpm_counter.h defines
* configurations XPM_CNTRCFGx which can be used to program the event counters
* to count a set of events.
*
* @note
* It doesn't handle the Cortex-A9 cycle counter, as the cycle counter is
* being used for time keeping.
*
*
******************************************************************************/

#include "xpm_counter.h"


/************************** Function Prototypes *****************************/

/* Interface functions to access performance counters from abstraction layer */
void Xpm_SetEvents(s32 PmcrCfg)
{
    (void)PmcrCfg;
}
void Xpm_GetEventCounters(u32 *PmCtrValue)
{
    (void)PmCtrValue;
}
