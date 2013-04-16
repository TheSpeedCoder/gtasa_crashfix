#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "crashes.h"
#pragma warning(disable: 4244)
#include "CVector.h"
#include "StdInc.h"
#include "memory.h"
#include "log.h"

CVector vecCenterOfWorld;

static void WINAPI Load();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if ( CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)Load, NULL, 0, 0) == NULL ) {
			ExitProcess(GetLastError());
			return FALSE; 
		}
		break;
	}
	return TRUE;
}

static void WINAPI Load() {
	DWORD oldProt;
	VirtualProtect((LPVOID)0x401000, 0x4A3000, PAGE_EXECUTE_READWRITE, &oldProt);

	while(*(int*)0xB6F5F0 == 0) { 
		Sleep(100);
	}

	if(GetModuleHandle("samp.dll") != NULL) {
	
		// STOP IT TRYING TO LOAD THE SCM
		MemPut < BYTE > ( 0x468EB5, 0xEB );
		MemPut < BYTE > ( 0x468EB6, 0x32 );

		MemPutFast < int > ( 0x8a5a84, 127 );

		// DISABLE CGameLogic::Update
		//MemSet ((void *)0x442AD0, 0xC3, 1);

		MemPut < int > ( 0x00550F82, 8000 );

		MemPut < BYTE > ( 0x742685, 0x90 );
		MemPut < BYTE > ( 0x742686, 0xE9 );

		// DISABLE CProjectileInfo::RemoveAllProjectiles
		MemPut < BYTE > ( 0x7399B0, 0xC3 );

		// DISABLE CRoadBlocks::GenerateRoadblocks
		MemPut < BYTE > ( 0x4629E0, 0xC3 );

		MemPut < BYTE > ( 0x4E8410, 0xC3 );

		// DISABLE CPopulation__AddToPopulation
		MemPut < BYTE > ( 0x614720, 0x32 );
		MemPut < BYTE > ( 0x614721, 0xC0 );
		MemPut < BYTE > ( 0x614722, 0xC3 );

		MemPut < BYTE > ( 0x61EFFE, 0xEB );

		MemPut < BYTE > ( 0x441770, 0xC3 );

		// DISABLE CCrime__ReportCrime
		MemPut < BYTE > ( 0x532010, 0xC3 );

		MemSet ((void*)0x4DCF87,0x90,6);

		MemPut < BYTE > ( 0x6A436C, 0x90 );
		MemPut < BYTE > ( 0x6A436D, 0x90 );

		MemSet ( (LPVOID)0x738F3A, 0x90, 83 );


		// END 1


		// Prevent gta stopping driveby players from falling off
		MemSet ( (LPVOID)0x6B5B17, 0x90, 6 );

		MemPut < BYTE > ( 0x5B8342 + 0, 0x33 );     // xor eax, eax
		MemPut < BYTE > ( 0x5B8342 + 1, 0xC0 );
		MemPut < BYTE > ( 0x5B8342 + 2, 0xB0 );     // mov al, 0xFF
		MemPut < BYTE > ( 0x5B8342 + 3, 0xFF );
		MemPut < BYTE > ( 0x5B8342 + 4, 0x8B );     // mov edi, eax
		MemPut < BYTE > ( 0x5B8342 + 5, 0xF8 );

		MemSet ((LPVOID)0x4486F7, 0x90, 4);

		MemSet ((void *)0x559FD5, 0x90, 7 );
		MemSet ((void *)0x559FEB, 0x90, 7 );

		// DISABLE STATS MESSAGES
		MemSet ((void *)0x55B980, 0xC3, 1);

		MemSet ((void *)0x559760, 0xC3, 1);

		// DISABLE CEntryExitManager::Update (they crash when you enter anyway - not in sa-mp!)
		//MemPut < BYTE > ( 0x440D10, 0xC3 );

		// Disable MENU AFTER alt + tab
		//0053BC72   C605 7B67BA00 01 MOV BYTE PTR DS:[BA677B],1    
		MemPut < BYTE > ( 0x53BC78, 0x00 );

		MemPut < BYTE > ( 0x6F2089, 0x58 );
		MemSet ((void *)0x6F208A,0x90,4);

		MemPut < BYTE > ( 0x550FBA, 0x00 );
		MemPut < BYTE > ( 0x550FBB, 0x10 );

		MemPut < BYTE > ( 0x5E68A0, 0xEB );


		/*
		//DISABLE CPad::ReconcileTwoControllersInput
		MemPut < BYTE > ( 0x53F530, 0xC2 );
		MemPut < BYTE > ( 0x53F531, 0x0C );
		MemPut < BYTE > ( 0x53F532, 0x00 );

		MemPut < BYTE > ( 0x53EF80, 0xC3 );

		MemPut < BYTE > ( 0x541DDC, 0xEB );
		MemPut < BYTE > ( 0x541DDD, 0x60 );*/

		// DISABLE CWanted Helis (always return 0 from CWanted::NumOfHelisRequired)
		MemPut < BYTE > ( 0x561FA4, 0x90 );
		MemPut < BYTE > ( 0x561FA5, 0x90 );

		// DISABLE  CWanted__UpdateEachFrame
		MemSet ( (void*)0x53BFF6, 0x90, 5 );

		// DISABLE CWanted__Update
		MemSet ( (void*)0x60EBCC, 0x90, 5 );
		// blah

		// Make CTaskComplexSunbathe::CanSunbathe always return true
		MemPut < BYTE > ( 0x632140, 0xB0 );
		MemPut < BYTE > ( 0x632141, 0x01 );
		MemPut < BYTE > ( 0x632142, 0xC3 );
    
		// Stop CTaskSimpleCarDrive::ProcessPed from exiting passengers with CTaskComplexSequence (some timer check)
		MemPut < BYTE > ( 0x644C18, 0x90 );
		MemPut < BYTE > ( 0x644C19, 0xE9 );

		// Stop CPlayerPed::ProcessControl from calling CVisibilityPlugins::SetClumpAlpha
		MemSet ( (void*)0x5E8E84, 0x90, 5 );

		// Stop CVehicle::UpdateClumpAlpha from calling CVisibilityPlugins::SetClumpAlpha
		MemSet ( (void*)0x6D29CB, 0x90, 5 );

		// Disable CVehicle::DoDriveByShootings
		MemSet ( (void*)0x741FD0, 0x90, 3 );
		MemPut < BYTE > ( 0x741FD0, 0xC3 );

		// END 2

		// Disable CTaskSimplePlayerOnFoot::PlayIdleAnimations (ret 4)
		MemPut < BYTE > ( 0x6872C0, 0xC2 );
		MemPut < BYTE > ( 0x6872C1, 0x04 );
		MemPut < BYTE > ( 0x6872C2, 0x00 );

		// Prevent CVehicle::RecalcTrainRailPosition from changing train speed
		MemSet ((void *)0x6F701D, 0x90, 6);
		MemPut < BYTE > ( 0x6F7069, 0xEB );

		// The instanthit function for bullets ignores the first few bullets shot by
		// remote players after reloading because some flag isn't set (no bullet impact
		// graphics, no damage). Makes e.g. sawnoffs completely ineffective.
		// Remove this check so that no bullets are ignored.
		MemPut < BYTE > ( 0x73FDF9, 0xEB );

		// Avoid GTA setting vehicle first color to white after changing the paintjob
		MemSet ( (void *)0x6D65C5, 0x90, 11 );

		// Disable GTA vehicle detachment at rotation awkwardness
		MemPut < BYTE > ( 0x547441, 0xE9 );
		MemPut < BYTE > ( 0x547442, 0xFA );
		MemPut < BYTE > ( 0x547443, 0x02 );
		MemPut < BYTE > ( 0x547444, 0x00 );
		MemPut < BYTE > ( 0x547445, 0x00 );

		// Disable idle cam
		MemPut < BYTE > ( 0x522C80, 0xC3 );

		MemPut < BYTE > ( 0x53A982, 0xEB );

		MemPut < WORD > ( 0x745BC9, 0x9090 );

		// Allow all screen aspect ratios in multi-monitor dialog
		MemPut < WORD > ( 0x7459E1, 0x9090 );

		MemPut < BYTE > ( 0x4F9CCE, 0xCE );

		// Disable re-initialization of DirectInput mouse device by the game
		MemPut < BYTE > ( 0x576CCC, 0xEB );
		MemPut < BYTE > ( 0x576EBA, 0xEB );
		MemPut < BYTE > ( 0x576F8A, 0xEB );

		// Make sure DirectInput mouse device is set non-exclusive (may not be needed?)
		MemPut < DWORD > ( 0x7469A0, 0x909000B0 );

		MemSet ( (void *)0x53C127, 0x90, 10 );

		MemCpy ( (void *)0x5EFFE0, "\xC2\x18\x00\x90", 4 );

		// Stop the loading of ambient traffic models and textures
		// by skipping CStreaming::StreamVehiclesAndPeds() and CStreaming::StreamZoneModels()
		MemPut < BYTE > ( 0x40E7DF, 0xEB );

		// Disable CPopulation::ManagePed
		MemPut < BYTE > ( 0x611FC0, 0xC3 );
		// Stop CPopulation::Update after ManagePopulation call
		MemPut < BYTE > ( 0x616698, 0x5E );
		MemPut < BYTE > ( 0x616699, 0xC3 );

		// Disable CReplay::Update
		MemPut < BYTE > ( 0x460500, 0xC3 );
		// Disable CInterestingEvents::ScanForNearbyEntities
		MemPut < BYTE > ( 0x605A30, 0xC3 );
		// Disable CGangWars::Update
		MemPut < BYTE > ( 0x446610, 0xC3 );
		// Disable CConversations::Update
		MemPut < BYTE > ( 0x43C590, 0xC3 );
		// Disable CPedToPlayerConversations::Update
		MemPut < BYTE > ( 0x43B0F0, 0xC3 );
		// Disable CCarCtrl::RemoveCarsIfThePoolGetsFull
		MemPut < BYTE > ( 0x4322B0, 0xC3 );
		// Disable CStreaming::StreamVehiclesAndPeds_Always
		MemPut < BYTE > ( 0x40B650, 0xC3 );

		// Double the size of CPlaceable matrix array to fix a crash after CMatrixLinkList::AddToList1
		MemPut < int > ( 0x54F3A1, 1800 );

		// Move birds up a bit so they don't fly through solid objects quite so often
		MemPut < float > ( 0x71240e, 10.f + 10.f );
		MemPut < float > ( 0x712413, 2.f  + 10.f );
		MemPut < float > ( 0x712447, 13.f + 10.f );
		MemPut < float > ( 0x71244c, 4.f  + 10.f );

		// NOP interior music
		MemSet ( (LPVOID)0x508450, 0x90, 6 );
		MemSet ( (LPVOID)0x508817, 0x90, 6 );

		// NOP clouds
		MemPut < BYTE > ( 0x716380, 0xC3 );
		MemPut < BYTE > ( 0x713950, 0xC3 );

		MemPut < BYTE > ( 0x717180, 0x83 );
		MemPut < BYTE > ( 0x717181, 0xEC );
		MemPut < BYTE > ( 0x717182, 0x08 );

		MemSet ((void *)0x615FE3, 0xEB, 1);

		MemPut < BYTE > ( 0x040892A, 0x53 );
		MemPut < BYTE > ( 0x040892B, 0x90 );

		MemPut < BYTE > ( 0x04341C0, 0xC3 );    // Skip CCarCtrl::GenerateRandomCars

		// Prevent garages deleting vehicles
		MemPut < BYTE > ( 0x0449C50, 0xC3 );
		MemPut < BYTE > ( 0x0449D10, 0xC3 );

		MemPut < BYTE > ( 0x0706AB0, 0xC3 );
		
	}
	
	// Black roads fix
	MemPut < BYTE > ( 0x884984, 0 );

	InitHooks_CrashFixHacks ( );
}
