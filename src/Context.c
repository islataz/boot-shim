#include "application.h"

#ifdef _ARM
#include <armintr.h>

void SwitchToRealModeContext(int ptr3, int ptr7)
{

	// Disable IRQ
	_disable();

	int ptr9 = *(DWORD *)(ptr3 + 44) | *(DWORD *)(ptr3 + 40);
	_MoveToCoprocessor(ptr9, CONTROL_COPROCESSPOR_CP15, 0, 2, 0, 0);
	__isb(_ARM_BARRIER_SY);
	_MoveToCoprocessor(CONTROL_COPROCESSPOR_CP15, 0, 0, 8, 7, 0);
	_MoveToCoprocessor(CONTROL_COPROCESSPOR_CP15, 0, 0, 7, 5, 6);
	__dsb(_ARM_BARRIER_SY);
	__isb(_ARM_BARRIER_SY);
	_MoveToCoprocessor(ptr9, CONTROL_COPROCESSPOR_CP15, 0, 7, 8, 0);
	__isb(_ARM_BARRIER_SY);
	_MoveFromCoprocessor(CONTROL_COPROCESSPOR_CP15, 0, 7, 4, 0);
	_MoveToCoprocessor(*(DWORD *)(ptr3 + 32), CONTROL_COPROCESSPOR_CP15, 0, 13, 0, 4);
	__dsb(_ARM_BARRIER_SY);
	_MoveToCoprocessor(*(DWORD *)(ptr3 + 16), CONTROL_COPROCESSPOR_CP15, 0, 1, 0, 0);
	_MoveToCoprocessor(CONTROL_COPROCESSPOR_CP15, 0, 0, 7, 5, 6);
	__dsb(_ARM_BARRIER_SY);
	__isb(_ARM_BARRIER_SY);
	_MoveToCoprocessor(*(DWORD *)(ptr3 + 20), CONTROL_COPROCESSPOR_CP15, 0, 12, 0, 0);
	__isb(_ARM_BARRIER_SY);

	// Restore IRQ if necessary
	if (ptr7) _enable();

}

#endif