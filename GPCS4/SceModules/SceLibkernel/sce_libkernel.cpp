#include "sce_libkernel.h"
#include "pthreads4w/pthread.h"
#include "Platform/PlatformUtils.h"
#include "Emulator/SceModuleSystem.h"
// Note:
// The codebase is generated using GenerateCode.py
// You may need to modify the code manually to fit development needs

LOG_CHANNEL(SceModules.SceLibkernel);

//////////////////////////////////////////////////////////////////////////
// library: libkernel
//////////////////////////////////////////////////////////////////////////

int* PS4API __error(void)
{
	LOG_SCE_DUMMY_IMPL();
	return  &errno;
}


int PS4API __stack_chk_fail(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API __stack_chk_guard(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API __pthread_cxa_finalize(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}

int PS4API _sceKernelSetThreadAtexitCount()
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}

int PS4API _sceKernelSetThreadAtexitReport()
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}

int PS4API sceKernelClockGettime(sce_clockid_t clk_id, struct sce_timespec * tp)
{
	return scek_clock_gettime(clk_id, tp);
}

int PS4API sceKernelGetCpumode(void)
{
	LOG_SCE_DUMMY_IMPL();
	return SCE_KERNEL_CPUMODE_7CPU_NORMAL;
}

// Is PS4 Pro
int PS4API sceKernelIsNeoMode(void)
{
	int isNeoMode = 1;
	LOG_SCE_TRACE("return %d", isNeoMode);
	return isNeoMode;
}


int PS4API sceKernelUsleep(SceKernelUseconds microseconds)
{
	//LOG_SCE_TRACE("ms %d", microseconds);
	UtilTime::MicroSleep(microseconds);
	return SCE_OK;
}


int PS4API sceKernelBatchMap(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceKernelCheckedReleaseDirectMemory(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceKernelDlsym(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceKernelGetGPI(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}



int PS4API sceKernelGettimeofday(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}



int PS4API sceKernelLoadStartModule(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceKernelGetPrtAperture(int apertureId, void **addr, size_t *len)
{
	LOG_SCE_DUMMY_IMPL();
	*addr = nullptr;
	*len = 0;
	return SCE_OK;
}


int PS4API sceKernelSetPrtAperture(int apertureId, void *addr, size_t len)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceKernelUuidCreate(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


void *PS4API sceKernelGetProcParam(uint64_t p1, uint64_t p2)
{
	LOG_DEBUG("param1: %zu, param2: %zu", p1, p2);
	auto moduleSystem = CSceModuleSystem::GetInstance();
	auto procParam    = moduleSystem->getEbootModuleInfo()->pProcParam;
	return procParam;
}


void PS4API _sceKernelRtldSetApplicationHeapAPI(void* heap_api)
{
	LOG_SCE_DUMMY_IMPL();
}


bool PS4API sceKernelGetSanitizerMallocReplaceExternal()
{
	LOG_SCE_DUMMY_IMPL();
	return false;
}


bool PS4API sceKernelGetSanitizerNewReplaceExternal()
{
	LOG_SCE_DUMMY_IMPL();
	return false;
}


int PS4API _sceKernelSetThreadDtors()
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


void PS4NORETURN PS4API sceKernelDebugRaiseException(uint32_t error_code, uint32_t param)
{
	LOG_SCE_DUMMY_IMPL();
	UtilDebug::debugBreakPoint();
	exit(-1);
}


void PS4API sceKernelDebugRaiseExceptionOnReleaseMode(uint32_t error_code, uint32_t param)
{
	LOG_FIXME("Not implemented");
}


int PS4API scek___sys_regmgr_call()
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scePthreadAttrGet(ScePthread thread, ScePthreadAttr* attr)
{
	LOG_SCE_DUMMY_IMPL();
	*attr = nullptr;
	return SCE_OK;
}


int PS4API scePthreadAttrGetaffinity(ScePthread thread, SceKernelCpumask* mask)
{
	LOG_SCE_DUMMY_IMPL();
	*mask = 0;
	return SCE_OK;
}


int PS4API sceKernelGetProcessType(int pid)
{
	LOG_SCE_DUMMY_IMPL();
	return SCE_OK;
}


//////////////////////////////////////////////////////////////////////////
// library: libSceCoredump
//////////////////////////////////////////////////////////////////////////

int PS4API sceCoredumpAttachMemoryRegion(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceCoredumpRegisterCoredumpHandler(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API sceCoredumpWriteUserData(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}



//////////////////////////////////////////////////////////////////////////
// library: libSceCoredump_debug
//////////////////////////////////////////////////////////////////////////

int PS4API sceCoredumpDebugTriggerCoredump(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}




//////////////////////////////////////////////////////////////////////////
// library: libSceOpenPsId
//////////////////////////////////////////////////////////////////////////

int PS4API sceKernelGetOpenPsId(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}



//////////////////////////////////////////////////////////////////////////
// library: libScePosix
//////////////////////////////////////////////////////////////////////////

int PS4API scek_sched_yield(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_close(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_connect(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_recv(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_select(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_sem_destroy(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_sem_init(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_sem_post(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_sem_timedwait(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_sem_wait(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_send(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_shutdown(void)
{
	LOG_FIXME("Not implemented");
	return SCE_OK;
}


int PS4API scek_getpid(void)
{
	int pid = 0x1337;
	LOG_SCE_TRACE("return %d", pid);
	return pid;
}


int PS4API scek_getppid(void)
{
	int pid = 0x1;
	LOG_SCE_TRACE("return %d", pid);
	return pid;
}



