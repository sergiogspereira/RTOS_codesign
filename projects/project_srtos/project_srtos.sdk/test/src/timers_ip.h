
#ifndef TIMERS_IP_H
#define TIMERS_IP_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xparameters.h"
#include "xstatus.h"

#define XPAR_TIMERS_IP_0_S00_AXI_BASEADDR 0x43C10000

#define TIMERS_IP_IDTASK_OFFSET 0
#define TIMERS_IP_START_OFFSET 4
#define TIMERS_IP_STOP_OFFSET 8
#define TIMERS_IP_CHANGEPERIOD_OFFSET 12
#define TIMERS_IP_ADDRESS_OFFSET 16
#define TIMERS_IP_PERIOD_OFFSET 20
#define TIMERS_IP_PERIOD_AUTORELOAD_OFFSET 24

//READ
#define TIMERS_IP_IDTASK_IN_OFFSET 0
#define TIMERS_IP_ID_IN_OFFSET 4
#define TIMERS_IP_POINTER_IN_OFFSET 8
#define TIMERS_IP_PERIOD_IN_OFFSET 12
#define TIMERS_IP_AUTORELOAD_IN_OFFSET 16

#define TIMERS_IP_TIMERID_OFFSET 20
#define TIMERS_IP_TIMERADDR_OFFSET 24
#define TIMERS_IP_EXPIRETIME_OFFSET 28

/************************** Inline Function Prototypes ****************************/

static inline u8 createTimer(u32 addrtimer, u32 period, _Bool autoreload)
{
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR) + ((autoreload)? TIMERS_IP_PERIOD_AUTORELOAD_OFFSET : TIMERS_IP_PERIOD_OFFSET), (u32)(period));
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_ADDRESS_OFFSET), (u32) (addrtimer));

	return Xil_In32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_TIMERID_OFFSET));
}

static inline void setTimerTask(u8 idtimertask)
{
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_IDTASK_OFFSET), (u32) (idtimertask));
}

static inline u32 startTimer(u8 idtimer)
{
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_START_OFFSET), (u32) (idtimer));
	return Xil_In32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_EXPIRETIME_OFFSET));
}

static inline void stopTimer(u8 idtimer)
{
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_STOP_OFFSET), (u32) (idtimer));
}

static inline void setPeriodTimer(u8 idtimer, u32 period)
{
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_PERIOD_OFFSET), (u32) (period));
	Xil_Out32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_CHANGEPERIOD_OFFSET), (u32) (idtimer));
}

#define TIMER_ACTIVE() \
	Xil_In32((XPAR_TIMERS_IP_0_S00_AXI_BASEADDR + TIMERS_IP_TIMERADDR_OFFSET))

#endif // TIMERS_IP_H